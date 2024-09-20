#include "iostream"
#include "menu.h"
#include "math.h"
#include "time.h"

#define GENERATE_PAGE_SHIFT 4
#define MAIN_MENU_PAGE 0

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    srand(time(0));

    int next = 0;
    float coefs[7];
    float *dataset = nullptr;
    int dataset_len = 0;
    int datatype = 0;

    while (next >= 0) {
        switch (next) {
            case MAIN_MENU_PAGE:
                next = main_menu();
                break;
            case 1:
                float values[4];
                switch (datatype) {
                    case 1:
                        values[0] = get_expectation_by_coefs(coefs[0], coefs[1], coefs[2]);
                        values[1] = get_dispersion_by_coefs(coefs[0], coefs[1], coefs[2]);
                        values[2] = get_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2]);
                        values[3] = get_excess_by_coefs(coefs[0], coefs[1], coefs[2]);
                        break;
                    case 2:
                        values[0] = get_mix_expectation_by_coefs(coefs[0], coefs[1], coefs[2],
                                                                 coefs[3], coefs[4], coefs[5],
                                                                 coefs[6]);
                        values[1] = get_mix_dispersion_by_coefs(coefs[0], coefs[1], coefs[2],
                                                                coefs[3], coefs[4],
                                                                coefs[5],
                                                                coefs[6]);
                        values[2] = get_mix_asymmetry_by_coefs(coefs[0], coefs[1], coefs[2],
                                                               coefs[3], coefs[4], coefs[5],
                                                               coefs[6]);
                        values[3] = get_mix_excess_by_coefs(coefs[0], coefs[1], coefs[2],
                                                            coefs[3], coefs[4], coefs[5],
                                                            coefs[6]);
                        break;
                    case 3:
                        values[0] = get_expectation_by_dataset(dataset, dataset + dataset_len);
                        values[1] = get_dispersion_by_dataset(dataset, dataset + dataset_len);
                        values[2] = get_asymmetry_by_dataset(dataset, dataset + dataset_len);
                        values[3] = get_excess_by_dataset(dataset, dataset + dataset_len);
                        break;
                }
                params_show(begin(values), end(values));
                next = 0;
                break;
            case 2:
                next = 0;
                if (not datatype) {
                    cout << "Не заданы данные!" << endl;
                    break;
                }
                cout << "Введите в какой точке нужно считать плотность:" << endl;
                float x, density;
                x = input_number(-100000.f, 100000.f);
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
                cout << "Плотность: " << density << endl;
                break;
            case 3:
                datatype = generate_method_menu();
                next = datatype + GENERATE_PAGE_SHIFT;
                break;
            case 4:
                next = 0;
                if (not datatype) {
                    cout << "Не заданы данные!" << endl;
                    break;
                }
                cout << "Данные выборки: " << endl;
                for (int i = 0; i < dataset_len; i++) {
                    cout << dataset[i] << endl;
                }
                break;
            case 5:
                for (int i = 3; i < 7; i++) {
                    coefs[i] = 0;
                }
                cout << "Введите значение nu (параметр распределения)" << endl;
                coefs[0] = input_number(0.f, 100000.f);
                cout << "Введите значение mu (сдвиг по x)" << endl;
                coefs[1] = input_number(-100000.f, 100000.f);
                cout << "Введите значение lambda (параметр маштаба)" << endl;
                coefs[2] = input_number(0.f, 100000.f);
                cout << "Введите количство чисел в выборке: " << endl;
                dataset_len = input_number(1, 1000000);
                dataset = new float[dataset_len];
                for (int i = 0; i < dataset_len; i++) {
                    dataset[i] = modeling_random_x(coefs[0], coefs[1], coefs[2]);
                }
                cout << "Данные успешно заданы" << endl;
                next = 0;
                break;
            case 6:
                cout << "Введите значение nu_1 (параметр в распределении)" << endl;
                coefs[0] = input_number(0.f, 100000.f);
                cout << "Введите значение mu_1 (сдвиг по x)" << endl;
                coefs[1] = input_number(-100000.f, 100000.f);
                cout << "Введите значение lambda_1 (параметр маштаба)" << endl;
                coefs[2] = input_number(0.f, 100000.f);
                cout << "Введите значение nu_2 (параметр в распределении)" << endl;
                coefs[3] = input_number(0.f, 100000.f);
                cout << "Введите значение mu_2 (сдвиг по x)" << endl;
                coefs[4] = input_number(-100000.f, 100000.f);
                cout << "Введите значение lambda_2 (парметр маштаба)" << endl;
                coefs[5] = input_number(0.f, 100000.f);
                cout << "Введите значение p (Вероятность)" << endl;
                coefs[6] = input_number(0.f, 1.f);
                cout << "Введите количство чисел в выборке: " << endl;
                dataset_len = input_number(1, 1000000);
                dataset = new float[dataset_len];
                for (int i = 0; i < dataset_len; i++) {
                    dataset[i] = modeling_random_mix_x(coefs[0], coefs[1], coefs[2],
                                                       coefs[3], coefs[4], coefs[5],
                                                       coefs[6]);
                }
                cout << "Данные успешно заданы" << endl;
                next = 0;
                break;
            case 7:
                cout << "Введите количство чисел. " << endl;
                dataset_len = input_number(1, 1000000);
                dataset = new float[dataset_len];
                for (int i = 0; i < dataset_len; i++) {
                    dataset[i] = input_number(-100000.f, 100000.f);
                }
                cout << "Данные успешно заданы" << endl;
                next = 0;
                break;
            default:
                cout << "Произошла ошибка! Возвращаемся в основное меню" << endl;
                next = 0;
        }
    }
    return 0;
}
