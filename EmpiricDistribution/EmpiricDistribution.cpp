#include "EmpiricDistribution.h"

void EmpiricDistribution::save_to_file(const std::string &filename) const {
    // Проверяем, если массив данных не был передан
    if (dataset == nullptr) {
        return;
    }

    // Открываем файл для записи
    ofstream file(filename);

    file << dataset_len << endl;

    // Записываем данные выборки в файл
    for (int i = 0; i < dataset_len; i++) {
        file << dataset[i] << endl;
    }

    file.close(); // Закрываем файл после завершения записи
}

void EmpiricDistribution::load_from_file(const std::string &filename) {
    // Открываем файл для чтения
    ifstream file(filename);

    if (not file.is_open()) {
        throw range_error("File not found");
    }

    file >> dataset_len;


    // Выделяем память под новый массив данных
    dataset = new float[dataset_len];

    // Читаем данные из файла в массив
    for (int i = 0; i < dataset_len; i++) {
        file >> dataset[i];
        min_value = min(min_value, dataset[i]);
        max_value = min(max_value, dataset[i]);
    }

    file.close(); // Закрываем файл после завершения чтения
}

EmpiricDistribution::EmpiricDistribution(const std::string &filename) {
    EmpiricDistribution::load_from_file(filename);
}

EmpiricDistribution::EmpiricDistribution(GeneralDistribution &distribution) {
    dataset = new float(dataset_len);
    for (int i = 0; i < dataset_len; i++) {
        dataset[i] = distribution.modeling_random_x();
    }
}

EmpiricDistribution::EmpiricDistribution(MixDistribution &distribution) {
    dataset = new float(dataset_len);
    for (int i = 0; i < dataset_len; i++) {
        dataset[i] = distribution.random_value();
    }
}

EmpiricDistribution::EmpiricDistribution(const EmpiricDistribution &other): dataset_len(other.dataset_len),
                                                                            density_array_len(other.density_array_len),
                                                                            max_value(other.max_value),
                                                                            min_value(other.min_value) {
    if (other.dataset_len > 0) {
        dataset = new float[other.dataset_len];
        for (int i = 0; i < other.dataset_len; ++i) {
            dataset[i] = other.dataset[i];
        }
    }

    if (other.density_array_len > 0) {
        density = new float[other.density_array_len];
        for (int i = 0; i < other.density_array_len; ++i) {
            density[i] = other.density[i];
        }
    }
}


EmpiricDistribution &EmpiricDistribution::operator=(const EmpiricDistribution &other) {
    if (this == &other) {
        return *this; // Защита от самоприсваивания
    }

    // Освобождаем старую память
    delete[] dataset;
    delete[] density;

    // Копируем новые значения
    dataset_len = other.dataset_len;
    density_array_len = other.density_array_len;
    max_value = other.max_value;
    min_value = other.min_value;

    // Копируем массив dataset
    if (other.dataset_len > 0) {
        dataset = new float[other.dataset_len];
        for (int i = 0; i < other.dataset_len; ++i) {
            dataset[i] = other.dataset[i];
        }
    } else {
        dataset = nullptr;
    }

    // Копируем массив density
    if (other.density_array_len > 0) {
        density = new float[other.density_array_len];
        for (int i = 0; i < other.density_array_len; ++i) {
            density[i] = other.density[i];
        }
    } else {
        density = nullptr;
    }

    return *this;
}

float EmpiricDistribution::get_density(float x) {
    // Вычисление длины выборки
    //    int len_of_dataset = dataset_end - dataset_begin;
    float number_of_intervals;
    // Вычисление количества интервалов
    if (dataset_len >= 50) {
        number_of_intervals = int(log2(dataset_len)) + 1;
    } else {
        number_of_intervals = 8;
    }
    // Задание минимума и максимума выборки
    float minimum_number = *dataset;
    float maximum_number = *dataset;
    float *dataset_iterator = dataset;
    // Поиск минимума и максимума
    while (dataset_iterator < dataset + dataset_len) {
        if (*dataset_iterator < minimum_number) {
            minimum_number = *dataset_iterator;
        }
        if (*dataset_iterator > maximum_number) {
            maximum_number = *dataset_iterator;
        }
        dataset_iterator++;
    }
    // Вычисление размаха, ширины, первого значения интервала
    float range = maximum_number - minimum_number;
    float interval_width = range / number_of_intervals;
    float first_value = minimum_number - interval_width * 0.5;
    // Определение левой и правой границ интервала
    float left_border_value = first_value + floor((x - first_value) / interval_width) * interval_width;
    float right_border_value = left_border_value + interval_width;
    float number_of_occurrences = 0;
    dataset_iterator = dataset;
    for (int i = 0; i < dataset_len; i++) {
        if (*dataset_iterator >= left_border_value and *dataset_iterator < right_border_value) {
            number_of_occurrences++;
        }
        dataset_iterator++;
    }
    // Возвращение вероятности (функции плотности) в точке
    return number_of_occurrences / (dataset_len * interval_width);
}

float EmpiricDistribution::get_expectation() {
    float sum = 0;
    int counter = 0;
    for (auto it = dataset; it != dataset + dataset_len; ++it) {
        sum += *it;
        counter++;
    }
    return sum / counter;
}

float EmpiricDistribution::get_dispersion() {
    float expectation = get_expectation();
    float sum = 0;
    int counter = 0;
    for (auto it = dataset; it != dataset + dataset_len; ++it) {
        sum += pow(*it - expectation, 2);
        counter++;
    }
    return sum / counter;
}

float EmpiricDistribution::get_excess() {
    float expectation = get_expectation();
    float dispersion = get_dispersion();

    float sum = 0;
    int counter = 0;
    for (auto it = dataset; it != dataset + dataset_len; ++it) {
        sum += pow(*it - expectation, 4);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 2) - 3;
}

float EmpiricDistribution::get_asymmetry() {
    float expectation = get_expectation();
    float dispersion = get_dispersion();
    float sum = 0;
    int counter = 0;
    for (auto it = dataset; it != dataset + dataset_len; ++it) {
        sum += pow(*it - expectation, 3);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 1.5);
}


float *EmpiricDistribution::getDataset() const {
    return dataset;
}

float *EmpiricDistribution::getDensity() const {
    return density;
}

int EmpiricDistribution::getDatasetLen() const {
    return dataset_len;
}

int EmpiricDistribution::getDensityArrayLen() const {
    return density_array_len;
}

float EmpiricDistribution::getMaxValue() const {
    return max_value;
}

float EmpiricDistribution::getMinValue() const {
    return min_value;
}

void EmpiricDistribution::setDataset(const float *data, int length) {
    dataset_len = length;
    dataset = new float[dataset_len];

    // Читаем данные из файла в массив
    for (int i = 0; i < dataset_len; i++) {
        dataset[i] = data[i];
        min_value = min(min_value, dataset[i]);
        max_value = min(max_value, dataset[i]);
    }
}
