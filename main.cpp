#include "iostream"    // Для работы с вводом/выводом
#include "menu.h"      // Заголовочный файл меню (предполагается, что он содержит функции работы с меню)
#include "fstream"     // Для работы с файлами
#include "math.h"      // Для математических операций
#include "consts.h"    // Заголовочный файл с константами (например, типы распределений)
#include "chrono"
#include <iomanip>
#include "GeneralDistribution/GeneralDistribution.h"
#include "EmpiricDistribution/EmpiricDistribution.h"
#include "MixDistribution/MixDistribution.h"
#include "test.h"

using namespace std;

// Функция для расчета статистических характеристик
// datatype — тип данных, coefs — массив коэффициентов распределения, dataset — массив данных, dataset_len — длина массива, stats — массив для хранения статистик
void calc_stats(int datatype, float *coefs, float *stats, GeneralDistribution distr, MixDistribution *&mix_distr,
                EmpiricDistribution *empiric_distribution) {
    // В зависимости от типа данных используем соответствующие методы для расчета
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            stats[0] = get_expectation_by_coefs(coefs[0], coefs[1], coefs[2]); // Математическое ожидание
            stats[1] = get_dispersion_by_coefs(coefs[0], coefs[1], coefs[2]); // Дисперсия
            stats[2] = get_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2]); // Коэффициент асимметрии
            stats[3] = get_excess_by_coefs(coefs[0], coefs[1], coefs[2]); // Коэффициент эксцесса
            break;
        case CLASS_OF_GENERAL_DISTRIBUTION_DATATYPE:
            distr.load_from_file("persistent.txt");
            stats[0] = distr.get_expectation();
            stats[1] = distr.get_dispersion();
            stats[2] = distr.get_asymmetry();
            stats[3] = distr.get_excess();
            break;
        case MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            stats[0] = get_mix_expectation_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5],
                                                    coefs[6]);
            stats[1] = get_mix_dispersion_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5],
                                                   coefs[6]);
            stats[2] = get_mix_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            stats[3] = get_mix_excess_by_coefs(coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            break;
        case CLASS_OF_MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            mix_distr->load_from_file("persistent_mix.txt");
            stats[0] = mix_distr->get_expectation();
            stats[1] = mix_distr->get_dispersion();
            stats[2] = mix_distr->get_asymmetry();
            stats[3] = mix_distr->get_excess();
            break;
        case EMPIRICAL_DATATYPE: // Эмпирические данные
            stats[0] = empiric_distribution->get_expectation();
            stats[1] = empiric_distribution->get_dispersion();
            stats[2] = empiric_distribution->get_asymmetry();
            stats[3] = empiric_distribution->get_excess();
            break;
    }
}

void print_exec_time(chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now()) {
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << fixed << setprecision(7);
    cout << "Время выполнения: " << elapsed.count() << " секунд" << endl;
    cout << defaultfloat;
}

// Функция для расчета плотности вероятности в точке x
// x — точка, в которой нужно рассчитать плотность, datatype — тип распределения, coefs — массив коэффициентов распределения, dataset — данные выборки, dataset_len — длина выборки
float calc_density(float x, int datatype, float *coefs, GeneralDistribution distr,
                   MixDistribution *&mix_distr, EmpiricDistribution *empiric_distribution) {
    float density;
    // В зависимости от типа данных используем соответствующий метод для расчета плотности
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE: // Общий тип распределения
            density = get_density_by_coefs(x, coefs[0], coefs[1], coefs[2]);
            break;
        case CLASS_OF_GENERAL_DISTRIBUTION_DATATYPE:
            distr.load_from_file("persistent.txt");
            density = distr.get_density(x);
            break;
        case MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            density = get_mix_density_by_coefs(x, coefs[0], coefs[1], coefs[2], coefs[3], coefs[4], coefs[5], coefs[6]);
            break;
        case CLASS_OF_MIX_DISTRIBUTION_DATATYPE: // Смесь распределений
            mix_distr->load_from_file("persistent_mix.txt");
            density = mix_distr->get_density(x);
            break;
        case EMPIRICAL_DATATYPE: // Эмпирические данные
            density = empiric_distribution->get_density(x);
            break;
    }
    return density; // Возвращаем рассчитанную плотность
}


int main() {
    // Настройка кодировки для Windows
#if defined(_WIN32) || defined(__CYGWIN__)
    system("chcp 65001");
    system("cls");
#endif

    srand(time(0)); // Инициализация генератора случайных чисел

    int next = MAIN_MENU_PAGE; // Начальная страница
    float coefs[7]; // Массив коэффициентов распределения
    int dataset_len = 0; // Длина выборки
    int datatype = 0; // Тип данных (распределения)
    float stats[4]; // Массив для хранения статистик (матожидание, дисперсия, асимметрия, эксцесс)
    int output_file_index = 0; // Индекс файла для уникализации имени
    float x, density; // Переменные для расчета плотности
    GeneralDistribution distribution;
    MixDistribution *mix_distribution = nullptr;
    EmpiricDistribution *empiric_distribution = nullptr;

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
                distribution = GeneralDistribution(coefs[0], coefs[1], coefs[2]);
            // Переходим к странице выбора операций с распределением
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case MIX_DISTRIBUTION_INPUT_PAGE:
                // Вводим 7 коэффициентов для смеси распределений
                input_7_coefs(coefs);
                mix_distribution = new MixDistribution(coefs[0],
                                                   coefs[1],
                                                   coefs[2],
                                                   coefs[3],
                                                   coefs[4],
                                                   coefs[5],
                                                   coefs[6]);
            // Переходим к странице выбора операций с распределением
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case UNIT_TEST_PAGE:
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

            case STATS_BY_COEFS_PAGE: {
                auto start = chrono::high_resolution_clock::now();
                // Расчет статистических характеристик на основе коэффициентов распределения
                calc_stats(datatype, coefs, stats, distribution, mix_distribution, empiric_distribution);
                print_exec_time(start);
                // Отображаем полученные статистики
                show_stats(stats);
                // Возвращаемся к странице операций с распределением по коэффициентам
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            }

            case DENSITY_BY_COEFS_PAGE: {
                // Запрос точки, в которой нужно рассчитать плотность
                cout << "Введите в какой точке нужно считать плотность:" << endl;
                x = input_number(-100000.f, 100000.f); // Ввод точки
                // Расчет плотности в заданной точке
                auto start = chrono::high_resolution_clock::now();
                density = calc_density(x, datatype, coefs, distribution, mix_distribution, empiric_distribution);
                print_exec_time(start);
                // Вывод плотности
                cout << "Плотность: " << density << endl;
                // Возвращаемся к странице операций с распределением по коэффициентам
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            }

            case GENERATE_DATASET_PAGE: {
                // Запрос размера выборки для генерации
                cout << "Введите размер выборки:" << endl;
                dataset_len = input_number(1, 100000); // Ввод размера выборки
                // Генерация выборки на основе коэффициентов распределения
                auto start = chrono::high_resolution_clock::now();
                if (datatype == GENERAL_DISTRIBUTION_DATATYPE) {
                    empiric_distribution = new EmpiricDistribution(distribution, dataset_len);
                } else {
                    empiric_distribution = new EmpiricDistribution(*mix_distribution, dataset_len);
                }
                print_exec_time(start);
                // Переходим на страницу операций с сгенерированной выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            case SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE: {
                // Показ меню операций с выборкой
                next = dataset_operations_menu(datatype);
                // Если не выбрана операция, возвращаемся на страницу операций с коэффициентами
                if (not next) {
                    next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                } else {
                    // Переходим на страницу соответствующей операции с выборкой
                    next += LAYER_3_PAGE_SHIFT;
                }
                break;
            }

            case STATS_BY_DATASET_PAGE: {
                auto start = chrono::high_resolution_clock::now();
                // Расчет статистических характеристик на основе коэффициентов распределения
                // Расчет статистических характеристик на основе сгенерированной выборки (эмпирические данные)
                calc_stats(EMPIRICAL_DATATYPE, coefs, stats, distribution, mix_distribution, empiric_distribution);
                print_exec_time(start);
                // Отображаем рассчитанные статистики
                show_stats(stats);
                // Возвращаемся на страницу операций с выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            case DENSITY_BY_DATASET_PAGE: {
                // Запрос точки, в которой нужно рассчитать плотность по выборке
                cout << "Введите в какой точке нужно считать плотность:" << endl;
                x = input_number(-100000.f, 100000.f); // Ввод точки
                auto start = chrono::high_resolution_clock::now();
                // Расчет плотности по выборке
                density = calc_density(x, EMPIRICAL_DATATYPE, coefs, distribution,
                                       mix_distribution, empiric_distribution);
                print_exec_time(start);
                // Вывод плотности
                cout << "Плотность: " << density << endl;
                // Запись массива плотностей в файл
                empiric_distribution->density_to_file("dataset_density.txt");
                // write_density_array_to_file(dataset, dataset_len, output_file_index);
                // Увеличиваем индекс файла для уникальности
                output_file_index++;
                // Возвращаемся на страницу операций с выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            case SHOW_DATASET_PAGE: {
                // Показ данных выборки на экране
                empiric_distribution->show_dataset();
                // show_dataset(dataset, dataset_len);
                // Возвращаемся на страницу операций с выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            case DATASET_TO_FILE_PAGE: {
                // Запись выборки в файл
                //write_dataset_to_file(dataset, dataset_len, output_file_index);
                empiric_distribution->save_to_file("empiric_distribution.txt");
                // Увеличиваем индекс файла для уникальности
                output_file_index++;
                // Возвращаемся на страницу операций с выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            case GENERATE_DATASET_BY_DENSITY_PAGE: {
                // Генерация новой выборки на основе плотности исходной выборки
                auto start = chrono::high_resolution_clock::now();
                // Todo
                // dataset = modeling_sample_based_on_sample(dataset_len, dataset, dataset + dataset_len);
                print_exec_time(start);
                // Возвращаемся на страницу операций с выборкой
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            }

            default: {
                // Обработка ошибки при неверном значении next
                cout << "Произошла ошибка! Возвращаемся в основное меню" << endl;
                next = MAIN_MENU_PAGE;
            }
        }
    }
    return 0;
}
