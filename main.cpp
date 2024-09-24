#include "iostream"
#include "menu.h"
#include "fstream"
#include "math.h"
#include "time.h"

#define GENERATE_PAGE_SHIFT 6

#define LAYER_2_PAGE_SHIFT 3
#define LAYER_3_PAGE_SHIFT 7

#define MAIN_MENU_PAGE 0
#define BASIC_DISTRIBUTION_INPUT_PAGE 1
#define MIX_DISTRIBUTION_INPUT_PAGE 2
#define SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE 3
#define STATS_BY_COEFS_PAGE 4
#define DENSITY_BY_COEFS_PAGE 5
#define GENERATE_DATASET_PAGE 6
#define SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE 7
#define STATS_BY_DATASET_PAGE 8
#define DENSITY_BY_DATASET_PAGE 9
#define SHOW_DATASET_PAGE 10
#define DATASET_TO_FILE_PAGE 11
#define GENERATE_DATASET_BY_DENSITY_PAGE 12


using namespace std;

void write_dataset_to_file(float *dataset, int &dataset_len) {
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }
    cout << "Данные выборки записаны в файл output.data" << endl;
    ofstream file("output.data");
    for (int i = 0; i < dataset_len; i++) {
        file << dataset[i] << endl;
    }
    file.close();
}

void show_dataset(float *dataset, int &dataset_len) {
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }
    cout << "Данные выборки:" << endl;
    for (int i = 0; i < dataset_len; i++) {
        cout << dataset[i] << endl;
    }
}

void calc_stats(int datatype, float *coefs, float *dataset, int &dataset_len, float *stats) {
    switch (datatype) {
        case 1:
            stats[0] = get_expectation_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[1] = get_dispersion_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[2] = get_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[3] = get_excess_by_coefs(coefs[0], coefs[1], coefs[2]);
            break;
        case 2:
            stats[0] = get_mix_expectation_by_coefs(coefs[0], coefs[1], coefs[2],
                                                    coefs[3], coefs[4], coefs[5],
                                                    coefs[6]);
            stats[1] = get_mix_dispersion_by_coefs(coefs[0], coefs[1], coefs[2],
                                                   coefs[3], coefs[4],
                                                   coefs[5],
                                                   coefs[6]);
            stats[2] = get_mix_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2],
                                                  coefs[3], coefs[4], coefs[5],
                                                  coefs[6]);
            stats[3] = get_mix_excess_by_coefs(coefs[0], coefs[1], coefs[2],
                                               coefs[3], coefs[4], coefs[5],
                                               coefs[6]);
            break;
        case 3:
            stats[0] = get_expectation_by_dataset(dataset, dataset + dataset_len);
            stats[1] = get_dispersion_by_dataset(dataset, dataset + dataset_len);
            stats[2] = get_asymmetry_by_dataset(dataset, dataset + dataset_len);
            stats[3] = get_excess_by_dataset(dataset, dataset + dataset_len);
            break;
    }
}

float calc_density(float x, int datatype, float *coefs, float *dataset, int &dataset_len) {
    float density;
    switch (datatype) {
        case 1:
            density = get_density_by_coefs(x, coefs[0], coefs[1], coefs[2]);
            break;
        case 2:
            density = get_mix_density_by_coefs(x, coefs[0], coefs[1], coefs[2],
                                               coefs[3], coefs[4], coefs[5],
                                               coefs[6]);
            break;
        case 3:
            density = get_density_by_dataset(x, dataset, dataset + dataset_len);
            break;
    }
    return density;
}

void generate_dataset(int &datatype, float *&dataset, int &dataset_len, float *coefs) {
    dataset = new float[dataset_len];
    switch (datatype) {
        case 1:
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = modeling_random_x(coefs[0], coefs[1], coefs[2]);
            }
            break;
        case 2:
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = modeling_random_mix_x(coefs[0], coefs[1], coefs[2],
                                                   coefs[3], coefs[4], coefs[5],
                                                   coefs[6]);
            }
            break;
    }
}

int main() {
#if defined(_WIN32) || defined(__CYGWIN__)
    system("chcp 65001");
#endif

    srand(time(0));

    int next = MAIN_MENU_PAGE;
    float coefs[7];
    float *dataset = nullptr;
    int dataset_len = 0;
    int datatype = 0;
    float stats[4];
    float x, density;
    /*
     * datatype
     * 0 - Данные не заданы
     * 1 - Основная выборка
     * 2 - Смесь
     * 3 - По датасету
     */

    while (next >= 0) {
        switch (next) {
            case MAIN_MENU_PAGE:
                next = main_menu();
                if (not next) {
                    cout << "Завершение работы программы!" << endl;
                    return 0;
                }
                datatype = next;
                break;
            case BASIC_DISTRIBUTION_INPUT_PAGE:
                input_4_coefs(coefs);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case MIX_DISTRIBUTION_INPUT_PAGE:
                input_7_coefs(coefs);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE:
                next = coefs_operations_menu();
                if (not next) {
                    next = MAIN_MENU_PAGE;
                } else {
                    next += LAYER_2_PAGE_SHIFT;
                }
                break;
            case STATS_BY_COEFS_PAGE:

                calc_stats(datatype, coefs, dataset, dataset_len, stats);
                show_stats(stats);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case DENSITY_BY_COEFS_PAGE:
                cout << "Введите в какой точке нужно считать плотность:" << endl;

                x = input_number(-100000.f, 100000.f);
                density = calc_density(x, datatype, coefs, dataset, dataset_len);
                cout << "Плотность: " << density << endl;
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                break;
            case GENERATE_DATASET_PAGE:
                cout << "Введите размер выборки:" << endl;
                dataset_len = input_number(1, 100000);
                generate_dataset(datatype, dataset, dataset_len, coefs);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE:
                next = dataset_operations_menu(datatype);
                if (not next) {
                    next = SELECT_OPERATION_FOR_DISTIBUTION_BY_COEFS_PAGE;
                } else {
                    next += LAYER_3_PAGE_SHIFT;
                }
                break;
            case STATS_BY_DATASET_PAGE:
                calc_stats(3, coefs, dataset, dataset_len, stats);
                show_stats(stats);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case DENSITY_BY_DATASET_PAGE:
                cout << "Введите в какой точке нужно считать плотность:" << endl;
                x = input_number(-100000.f, 100000.f);
                density = calc_density(x, 3, coefs, dataset, dataset_len);
                cout << "Плотность: " << density << endl;
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case SHOW_DATASET_PAGE:
                show_dataset(dataset, dataset_len);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case DATASET_TO_FILE_PAGE:
                write_dataset_to_file(dataset, dataset_len);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case GENERATE_DATASET_BY_DENSITY_PAGE:
                dataset = modeling_sample_based_on_sample(dataset_len, dataset, dataset + dataset_len);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            default:
                cout << "Произошла ошибка! Возвращаемся в основное меню" << endl;
                next = MAIN_MENU_PAGE;
        }
    }
    return 0;
}
