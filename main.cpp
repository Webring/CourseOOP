#include "iostream"
#include "menu.h"
#include "fstream"
#include "math.h"
#include "consts.h"

using namespace std;

void write_density_array_to_file(float *dataset, int &dataset_len, int &file_index) {
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }

    float *density_array_begin, *density_array_end;

    int intervals = get_density_array(dataset, dataset + dataset_len, density_array_begin, density_array_end);

    const string file_name = "density_by_intervals_" + to_string(intervals) + "_" + to_string(file_index) + ".data";

    ofstream file(file_name);
    for (auto i = 0; i < intervals; i++) {
        file << *(density_array_begin + i) << endl;
    }
    cout << "Данные выборки записаны в файл " << file_name << endl;
    file.close();
}

void write_dataset_to_file(float *dataset, int &dataset_len, int &file_index) {
    if (dataset == nullptr) {
        cout << "Не заданы данные!" << endl;
        return;
    }

    const string file_name = "distribution_" + to_string(file_index) + ".data";
    ofstream file(file_name);
    for (int i = 0; i < dataset_len; i++) {
        file << dataset[i] << endl;
    }
    cout << "Данные выборки записаны в файл " << file_name << endl;
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
        case GENERAL_DISTRIBUTION_DATATYPE:
            stats[0] = get_expectation_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[1] = get_dispersion_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[2] = get_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2]);
            stats[3] = get_excess_by_coefs(coefs[0], coefs[1], coefs[2]);
            break;
        case MIX_DISTRIBUTION_DATATYPE:
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
        case EMPIRICAL_DATATYPE:
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
        case GENERAL_DISTRIBUTION_DATATYPE:
            density = get_density_by_coefs(x, coefs[0], coefs[1], coefs[2]);
            break;
        case MIX_DISTRIBUTION_DATATYPE:
            density = get_mix_density_by_coefs(x, coefs[0], coefs[1], coefs[2],
                                               coefs[3], coefs[4], coefs[5],
                                               coefs[6]);
            break;
        case EMPIRICAL_DATATYPE:
            density = get_density_by_dataset(x, dataset, dataset + dataset_len);
            break;
    }
    return density;
}

void generate_dataset(int &datatype, float *&dataset, int &dataset_len, float *coefs) {
    dataset = new float[dataset_len];
    switch (datatype) {
        case GENERAL_DISTRIBUTION_DATATYPE:
            for (int i = 0; i < dataset_len; i++) {
                dataset[i] = modeling_random_x(coefs[0], coefs[1], coefs[2]);
            }
            break;
        case MIX_DISTRIBUTION_DATATYPE:
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
    system("cls");
#endif

    srand(time(0));

    int next = MAIN_MENU_PAGE;
    float coefs[7];
    float *dataset = nullptr;
    int dataset_len = 0;
    int datatype = 0;
    float stats[4];
    int output_file_index = 0;
    float x, density;

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
                calc_stats(EMPIRICAL_DATATYPE, coefs, dataset, dataset_len, stats);
                show_stats(stats);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case DENSITY_BY_DATASET_PAGE:
                cout << "Введите в какой точке нужно считать плотность:" << endl;
                x = input_number(-100000.f, 100000.f);
                density = calc_density(x, EMPIRICAL_DATATYPE, coefs, dataset, dataset_len);
                cout << "Плотность: " << density << endl;
                write_density_array_to_file(dataset, dataset_len, output_file_index);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case SHOW_DATASET_PAGE:
                show_dataset(dataset, dataset_len);
                next = SELECT_OPERATION_FOR_DISTIBUTION_BY_DATASET_PAGE;
                break;
            case DATASET_TO_FILE_PAGE:
                write_dataset_to_file(dataset, dataset_len, output_file_index);
                output_file_index++;
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
