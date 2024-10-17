#include "iostream"    // Для работы с вводом/выводом
#include "menu.h"      // Заголовочный файл меню (предполагается, что он содержит функции работы с меню)
#include "fstream"     // Для работы с файлами
#include "math.h"      // Для математических операций
#include "consts.h"    // Заголовочный файл с константами (например, типы распределений)
#include "chrono"
#include "GeneralDistribution/GeneralDistribution.h"
#include "test.h"

using namespace std;

// Функция для записи массива плотностей в файл
// dataset — указатель на массив данных, dataset_len — длина массива, file_index — индекс файла для уникализации имени
void write_density_array_to_file(float *dataset, int &dataset_len, int &file_index) {
    // Проверяем, если массив данных не был передан
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }

    float *density_array_begin, *density_array_end;

    // Функция, которая возвращает массив плотностей для заданного набора данных
    // Возвращает количество интервалов плотности
    int intervals = get_density_array(dataset, dataset + dataset_len, density_array_begin, density_array_end);

    // Формируем уникальное имя файла на основе количества интервалов и индекса файла
    const string file_name = "density_by_intervals_" + to_string(intervals) + "_" + to_string(file_index) + ".data";

    // Открываем файл для записи
    ofstream file(file_name);

    // Записываем массив плотностей в файл
    for (auto i = 0; i < intervals + 2; i++) {
        file << *(density_array_begin + i) << endl;
    }

    cout << "Данные выборки записаны в файл " << file_name << endl;
    file.close(); // Закрываем файл после завершения записи
}

// Функция для записи исходных данных в файл
// dataset — указатель на массив данных, dataset_len — длина массива, file_index — индекс файла для уникализации имени
void write_dataset_to_file(float *dataset, int &dataset_len, int &file_index) {
    // Проверяем, если массив данных не был передан
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }

    // Формируем уникальное имя файла для записи данных выборки
    const string file_name = "distribution_" + to_string(file_index) + ".data";

    // Открываем файл для записи
    ofstream file(file_name);

    // Записываем данные выборки в файл
    for (int i = 0; i < dataset_len; i++) {
        file << dataset[i] << endl;
    }

    cout << "Данные выборки записаны в файл " << file_name << endl;
    file.close(); // Закрываем файл после завершения записи
}

// Функция для вывода данных выборки на экран
// dataset — указатель на массив данных, dataset_len — длина массива
void show_dataset(float *dataset, int &dataset_len) {
    // Проверяем, если массив данных не был передан
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }

    // Выводим данные выборки
    cout << "Данные выборки:" << endl;
    for (int i = 0; i < dataset_len; i++) {
        cout << dataset[i] << endl;
    }
}

// Функция для расчета статистических характеристик
// datatype — тип данных, coefs — массив коэффициентов распределения, dataset — массив данных, dataset_len — длина массива, stats — массив для хранения статистик
void calc_stats(int datatype, float *coefs, float *dataset, int &dataset_len, float *stats, GeneralDistribution distr) {
    // В зависимости от типа данных используем соответствующие методы для расчета
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            stats[0] = get_expectation_by_coefs(coefs[0], coefs[1], coefs[2]); // Математическое ожидание
            stats[1] = get_dispersion_by_coefs(coefs[0], coefs[1], coefs[2]);  // Дисперсия
            stats[2] = get_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2]);   // Коэффициент асимметрии
            stats[3] = get_excess_by_coefs(coefs[0], coefs[1], coefs[2]);      // Коэффициент эксцесса
            break;
        case CLASS_OF_GENERAL_DISTRIBUTION_DATATYPE:
            stats[0] = distr.get_expectation();
            stats[1] = distr.get_dispersion();
            stats[2] = distr.get_asymmetry();
            stats[3] = distr.get_excess();
        case MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            stats[0] = get_mix_expectation_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            stats[1] = get_mix_dispersion_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            stats[2] = get_mix_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            stats[3] = get_mix_excess_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            break;
        case EMPIRICAL_DATATYPE: // Эмпирические данные
            stats[0] = get_expectation_by_dataset(dataset, dataset + dataset_len); // Математическое ожидание
            stats[1] = get_dispersion_by_dataset(dataset, dataset + dataset_len);  // Дисперсия
            stats[2] = get_asymmetry_by_dataset(dataset, dataset + dataset_len);   // Коэффициент асимметрии
            stats[3] = get_excess_by_dataset(dataset, dataset + dataset_len);      // Коэффициент эксцесса
            break;
    }
}

// Функция для расчета плотности вероятности в точке x
// x — точка, в которой нужно рассчитать плотность, datatype — тип распределения, coefs — массив коэффициентов распределения, dataset — данные выборки, dataset_len — длина выборки
float calc_density(float x, int datatype, float *coefs, float *dataset, int &dataset_len, GeneralDistribution distr) {
    float density;
    // В зависимости от типа данных используем соответствующий метод для расчета плотности
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            density = get_density_by_coefs(x, coefs[0], coefs[1], coefs[2]);
            break;
        case CLASS_OF_GENERAL_DISTRIBUTION_DATATYPE:
            density = distr.get_density(x);
            break;
        case MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            density = get_mix_density_by_coefs(x, coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            break;
        case EMPIRICAL_DATATYPE: // Эмпирические данные
            density = get_density_by_dataset(x, dataset, dataset + dataset_len);
            break;
    }
    return density; // Возвращаем рассчитанную плотность
}

// Функция для генерации набора данных (выборки)
// datatype — тип распределения, dataset — указатель на массив данных, dataset_len — длина выборки, coefs — массив коэффициентов распределения
void generate_dataset(int &datatype, float *&dataset, int &dataset_len, float *coefs, GeneralDistribution distr) {
    dataset = new float[dataset_len]; // Выделяем память под массив данных
    // В зависимости от типа распределения генерируем выборку
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = modeling_random_x(coefs[0], coefs[1], coefs[2]); // Генерация случайного значения по параметрам распределения
            }
            break;
        case CLASS_OF_GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = distr.modeling_random_x(); // Генерация случайного значения по параметрам распределения
            }
            break;
        case MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = modeling_random_mix_x(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]); // Генерация случайного значения для смеси распределений
            }
            break;
    }
}

int main() {
    // Настройка кодировки для Windows
#if defined(_WIN32) || defined(__CYGWIN__)
    system("chcp 65001");
    system("cls");
#endif

    srand(time(0)); // Инициализация генератора случайных чисел

    int next = MAIN_MENU_PAGE; // Начальная страница
    float coefs[7];           // Массив коэффициентов распределения
    float *dataset = nullptr;  // Указатель на массив данных
    int dataset_len = 0;       // Длина выборки
    int datatype = 0;          // Тип данных (распределения)
    float stats[4];            // Массив для хранения статистик (матожидание, дисперсия, асимметрия, эксцесс)
    int output_file_index = 0; // Индекс файла для уникализации имени
    float x, density;          // Переменные для расчета плотности
    GeneralDistribution distribution;

 while (next >= 0) {
    // В зависимости от значения переменной "next" выполняется соответствующий кейс
    switch (next) {
        case MAIN_MENU_PAGE:
            // Вызываем главное меню и получаем следующий шаг (номер следующей страницы)
            next = main_menu();
            // Если пользователь выбрал завершение (возвращается 0), завершаем программу
            if (not next) {
                cout << "Завершение работы программы!" << endl;
                return 0;
            }
            // Сохраняем выбранный тип данных (распределения)
            datatype = next;
            break;

        case BASIC_DISTRIBUTION_INPUT_PAGE:
            // Вводим 3 коэффициента для базового распределения
            input_3_coefs(coefs);
            // Переходим к странице выбора операций с распределением
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            break;
        case CLASS_OF_BASIC_DISTRIBUTION_INPUT_PAGE:
            input_3_coefs_class(distribution, coefs);
            cout << "Всё збс\n";
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            break;
        case MIX_DISTRIBUTION_INPUT_PAGE:
            // Вводим 7 коэффициентов для смеси распределений
            input_7_coefs(coefs);
            // Переходим к странице выбора операций с распределением
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            break;
        case TEST:
            test();
            next = 0;
            break;

        case SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE:
            // Показ меню операций с распределением по коэффициентам
            next = coefs_operations_menu();
            // Если возвращаемся в главное меню
            if (not next) {
                next = MAIN_MENU_PAGE;
            } else {
                // Переходим на следующую страницу, смещаем указатель страницы
                next += LAYER_2_PAGE_SHIFT;
            }
            break;

        case STATS_BY_COEFS_PAGE:{
            auto start = chrono::high_resolution_clock::now();
            // Расчет статистических характеристик на основе коэффициентов распределения
            calc_stats(datatype, coefs, dataset, dataset_len, stats, distribution);
            auto end = chrono::high_resolution_clock ::now();
            std::chrono::duration<double> elapsed = end - start;
            cout << std::fixed << std::setprecision(7);
            cout << "Время выполнения: " << elapsed.count() <<" секунд" <<endl;
            std::cout << std::defaultfloat;
            // Отображаем полученные статистики
            show_stats(stats);
            // Возвращаемся к странице операций с распределением по коэффициентам
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            break;}

        case DENSITY_BY_COEFS_PAGE:{
            // Запрос точки, в которой нужно рассчитать плотность
            cout << "Введите в какой точке нужно считать плотность:" << endl;
            x = input_number(-100000.f, 100000.f);  // Ввод точки
            // Расчет плотности в заданной точке
            auto start = chrono::high_resolution_clock::now();
            density = calc_density(x, datatype, coefs, dataset, dataset_len, distribution);
            auto end = chrono::high_resolution_clock ::now();
            std::chrono::duration<double> elapsed = end - start;
            cout << std::fixed << std::setprecision(7);
            cout << "Время выполнения: " << elapsed.count() <<" секунд" <<endl;
            std::cout << std::defaultfloat;
            // Вывод плотности
            cout << "Плотность: " << density << endl;
            // Возвращаемся к странице операций с распределением по коэффициентам
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            break;}

        case GENERATE_DATASET_PAGE:{
            // Запрос размера выборки для генерации
            cout << "Введите размер выборки:" << endl;
            dataset_len = input_number(1, 100000);  // Ввод размера выборки
            // Генерация выборки на основе коэффициентов распределения
            auto start = chrono::high_resolution_clock::now();
            generate_dataset(datatype, dataset, dataset_len, coefs, distribution);
            auto end = chrono::high_resolution_clock ::now();
            std::chrono::duration<double> elapsed = end - start;
            cout << std::fixed << std::setprecision(7);
            cout << "Время выполнения: " << elapsed.count() <<" секунд" <<endl;
            std::cout << std::defaultfloat;
            // Переходим на страницу операций с сгенерированной выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        case SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE:{
            // Показ меню операций с выборкой
            next = dataset_operations_menu(datatype);
            // Если не выбрана операция, возвращаемся на страницу операций с коэффициентами
            if (not next) {
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
            } else {
                // Переходим на страницу соответствующей операции с выборкой
                next += LAYER_3_PAGE_SHIFT;
            }
            break;}

        case STATS_BY_DATASET_PAGE:{
            // Расчет статистических характеристик на основе сгенерированной выборки (эмпирические данные)
            calc_stats(EMPIRICAL_DATATYPE, coefs, dataset, dataset_len, stats, distribution);
            // Отображаем рассчитанные статистики
            show_stats(stats);
            // Возвращаемся на страницу операций с выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        case DENSITY_BY_DATASET_PAGE:{
            // Запрос точки, в которой нужно рассчитать плотность по выборке
            cout << "Введите в какой точке нужно считать плотность:" << endl;
            x = input_number(-100000.f, 100000.f);  // Ввод точки
            // Расчет плотности по выборке
            density = calc_density(x, EMPIRICAL_DATATYPE, coefs, dataset, dataset_len, distribution);
            // Вывод плотности
            cout << "Плотность: " << density << endl;
            // Запись массива плотностей в файл
            write_density_array_to_file(dataset, dataset_len, output_file_index);
            // Увеличиваем индекс файла для уникальности
            output_file_index++;
            // Возвращаемся на страницу операций с выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        case SHOW_DATASET_PAGE:{
            // Показ данных выборки на экране
            show_dataset(dataset, dataset_len);
            // Возвращаемся на страницу операций с выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        case DATASET_TO_FILE_PAGE:{
            // Запись выборки в файл
            write_dataset_to_file(dataset, dataset_len, output_file_index);
            // Увеличиваем индекс файла для уникальности
            output_file_index++;
            // Возвращаемся на страницу операций с выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        case GENERATE_DATASET_BY_DENSITY_PAGE:{
            // Генерация новой выборки на основе плотности исходной выборки
            dataset = modeling_sample_based_on_sample(dataset_len, dataset, dataset + dataset_len);
            // Возвращаемся на страницу операций с выборкой
            next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
            break;}

        default:{
            // Обработка ошибки при неверном значении next
            cout << "Произошла ошибка! Возвращаемся в основное меню" << endl;
            next = MAIN_MENU_PAGE;}
    }
}
return 0;

}
