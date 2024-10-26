//
// Created by Viktor Serov on 22.10.2024.
//

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
        min_value = min(min_value, dataset[i]);
        max_value = min(max_value, dataset[i]);
        file >> dataset[i];
    }

    file.close(); // Закрываем файл после завершения чтения
}


float EmpiricDistribution::get_density(float x) {
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
