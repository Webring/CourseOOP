#include "GeneralDistribution/GeneralDistribution.h"
#include "MixDistribution/MixDistribution.h"
#include "EmpiricDistribution/EmpiricDistribution.h"
#include "interfaces.h"
#include "test.h"
#include "cmath"
#include "math.h"
#include <cassert>

#include "Estimate/Estimate.h"

void test() {
    IDistribution *IDistr;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ТЕСТИРОВАНИЕ КЛАССА ОСНОВНОГО РАСПРЕДЕЛЕНИЯ" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    GeneralDistribution GD;
    float array_nu[]{1, 0, 2, 3, 4.5};
    float array_mu[]{0, 1, 2, -3, -1};
    float array_lambda[]{1, 2, 4.2, 5, 2};

    // ToDo Delete
    auto g1 = GeneralDistribution(1, 10, 1);
    auto g2 = GeneralDistribution(0.5, 6, 4);
    auto m = MixDistribution<GeneralDistribution, GeneralDistribution>(1, 10, 1, 0.5, 6, 4, 0.3);
    auto e = EmpiricDistribution(m, 134);
    auto est = Estimate(e, sqrt(g1.get_dispersion()), 2.926, 500);
    e.notify();
    cout << g1.get_expectation() << endl;
    cout << est.get_mu() << endl;
    // ToDo Delete


    for (int i = 0; i < 5; i++) {
        try {
            GD.set_nu(array_nu[i]);
            GD.set_mu(array_mu[i]);
            GD.set_lambda(array_lambda[i]);
            IDistr = &GD;
            double expectation_general = get_expectation_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double density_general = get_density_by_coefs(array_mu[i], array_nu[i], array_mu[i], array_lambda[i]);
            double assym_general = get_asymmetry_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double excess_general = get_excess_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double dispersion_general = get_dispersion_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double expectation_class = IDistr->get_expectation();
            double density_class = IDistr->get_density(array_mu[i]);
            double assym_class = IDistr->get_asymmetry();
            double excess_class = IDistr->get_excess();
            double dispersion_class = IDistr->get_dispersion();

            assert(abs(expectation_general - expectation_class) <= 0.01);
            assert(abs(density_general - density_class) <= 0.01);
            assert(abs(assym_general - assym_class) <= 0.01);
            assert(abs(excess_general - excess_class) <= 0.01);
            assert(abs(dispersion_general - dispersion_class) <= 0.01);

            cout << "Тест №" << i + 1 << endl;
            cout << "Мат ожидание: " << expectation_general << '\t' << expectation_class << endl;
            cout << "Плотность в мат ожидании: " << density_general << "\t" << density_class << endl;
            cout << "Коэффициент асимметрии: " << assym_general << "\t" << assym_class << endl;
            cout << "Коэффициент эксцесса: " << excess_general << "\t" << excess_class << endl;
            cout << "Дисперсия: " << dispersion_general << "\t" << dispersion_class << endl << endl;
        } catch (...) {
            std::cout << "Ошибка при параметрах: nu - " << GD.get_nu() << " mu - " << GD.get_mu() << " lambda - "
                    << GD.get_lambda() << std::endl;
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ТЕСТИРОВАНИЕ КЛАССА СМЕСИ РАСПРЕДЕЛЕНИЙ" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    MixDistribution<GeneralDistribution, GeneralDistribution> MD(1, 0, 1, 1, 0, 1, 0.5);
    float array_nu1[]{1, 6, 4};
    float array_mu1[]{0, 0, -1};
    float array_lambda1[]{1, 1, 6};
    float array_nu2[]{1, 1, 2};
    float array_mu2[]{0, 2, 0};
    float array_lambda2[]{1, 5, 5};
    float array_proba[]{0.5, 0.5, 0.3};

    for (int i = 0; i < 3; i++) {
        try {
            MD.first_set_nu(array_nu1[i]);
            MD.first_set_mu(array_mu1[i]);
            MD.first_set_lambda(array_lambda1[i]);
            MD.second_set_nu(array_nu2[i]);
            MD.second_set_mu(array_mu2[i]);
            MD.second_set_lambda(array_lambda2[i]);
            MD.set_p(array_proba[i]);
            IDistr = &MD;
            float mu = IDistr->get_expectation();

            double expectation_mixed = get_mix_expectation_by_coefs(array_nu1[i], array_mu1[i], array_lambda1[i],
                                                                    array_nu2[i], array_mu2[i], array_lambda2[i],
                                                                    array_proba[i]);
            double density_mixed = get_mix_density_by_coefs(expectation_mixed, array_nu1[i], array_mu1[i],
                                                            array_lambda1[i], array_nu2[i], array_mu2[i],
                                                            array_lambda2[i], array_proba[i]);
            double assym_mixed = get_mix_asymmetry_by_coefs(array_nu1[i], array_mu1[i], array_lambda1[i], array_nu2[i],
                                                            array_mu2[i], array_lambda2[i], array_proba[i]);
            double excess_mixed = get_mix_excess_by_coefs(array_nu1[i], array_mu1[i], array_lambda1[i], array_nu2[i],
                                                          array_mu2[i], array_lambda2[i], array_proba[i]);
            double dispersion_mixed = get_mix_dispersion_by_coefs(array_nu1[i], array_mu1[i], array_lambda1[i],
                                                                  array_nu2[i], array_mu2[i], array_lambda2[i],
                                                                  array_proba[i]);
            double expectation_class = IDistr->get_expectation();
            double density_class = IDistr->get_density(mu);
            double assym_class = IDistr->get_asymmetry();
            double excess_class = IDistr->get_excess();
            double dispersion_class = IDistr->get_dispersion();

            assert(abs(expectation_mixed - expectation_class) <= 0.01);
            assert(abs(density_mixed - density_class) <= 0.01);
            assert(abs(assym_mixed - assym_class) <= 0.01);
            assert(abs(excess_mixed - excess_class) <= 0.01);
            assert(abs(dispersion_mixed - dispersion_class) <= 0.01);

            cout << "Тест №" << i + 1 << endl;
            cout << "Мат ожидание: " << expectation_mixed << '\t' << expectation_class << endl;
            cout << "Плотность в мат ожидании: " << density_mixed << "\t" << density_class << endl;
            cout << "Коэффициент асимметрии: " << assym_mixed << "\t" << assym_class << endl;
            cout << "Коэффициент эксцесса: " << excess_mixed << "\t" << excess_class << endl;
            cout << "Дисперсия: " << dispersion_mixed << "\t" << dispersion_class << endl << endl;
        } catch (...) {
            std::cout << "Ошибка при параметрах: \nnu1 - " << MD.first_get_nu() << " mu1 - " << MD.first_get_mu()
                    << " lambda1 - " << MD.first_get_lambda() << endl;
            std::cout << "nu2 - " << MD.second_get_nu() << " mu2 - " << MD.second_get_mu() << " lambda2 - "
                    << MD.second_get_lambda() << endl;
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ТЕСТИРОВАНИЕ КЛАССА ЭМПИРИЕСКОГО РАСПРЕДЕЛНИЯ ИЗ ФАЙЛА" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    EmpiricDistribution *ED;
    int dataset_len;
    float *dataset;
    ifstream file("distribution_test.txt");

    if (not file.is_open()) {
        throw range_error("File not found");
    }

    file >> dataset_len;
    if (dataset_len <= 0) {
        throw runtime_error("Dataset length is not positive");
    }

    // Выделяем память под новый массив данных
    dataset = new float[dataset_len];

    // Читаем данные из файла в массив
    for (int i = 0; i < dataset_len; i++) {
        file >> dataset[i];
    }

    file.close();
    try {
        ED = new EmpiricDistribution("distribution_test.txt");
        IDistr = ED;
        double expectation_dataset = get_expectation_by_dataset(dataset, dataset + dataset_len);
        double density_dataset = get_density_by_dataset(expectation_dataset, dataset, dataset + dataset_len);
        double assym_dataset = get_asymmetry_by_dataset(dataset, dataset + dataset_len);
        double excess_dataset = get_excess_by_dataset(dataset, dataset + dataset_len);
        double dispersion_dataset = get_dispersion_by_dataset(dataset, dataset + dataset_len);
        double expectation_class = IDistr->get_expectation();
        double density_class = IDistr->get_density(expectation_class);
        double assym_class = IDistr->get_asymmetry();
        double excess_class = IDistr->get_excess();
        double dispersion_class = IDistr->get_dispersion();

        assert(abs(expectation_dataset - expectation_class) <= 0.01);
        assert(abs(density_dataset - density_class) <= 0.01);
        assert(abs(assym_dataset - assym_class) <= 0.01);
        assert(abs(excess_dataset - excess_class) <= 0.01);
        assert(abs(dispersion_dataset - dispersion_class) <= 0.01);

        cout << "Тест №" << 1 << endl;
        cout << "Мат ожидание: " << expectation_dataset << '\t' << expectation_class << endl;
        cout << "Плотность в мат ожидании: " << density_dataset << "\t" << density_class << endl;
        cout << "Коэффициент асимметрии: " << assym_dataset << "\t" << assym_class << endl;
        cout << "Коэффициент эксцесса: " << excess_dataset << "\t" << excess_class << endl;
        cout << "Дисперсия: " << dispersion_dataset << "\t" << dispersion_class << endl << endl;
    } catch (...) {
        std::cout << "Ошибка при Тестировании файла: " << "distribution_test.data" << endl;
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ТЕСТИРОВАНИЕ КЛАССА ЭМПИРИЧЕСКОГО РАСПРЕДЕЛЕНИЯ ПО ОСНОВНОМУ РАСПРЕДЕЛЕНИЮ" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    int array_dataset_len[]{3000, 5000, 10000};
    for (int i = 0; i < 3; i++) {
        try {
            GD.set_nu(array_nu[i]);
            GD.set_mu(array_mu[i]);
            GD.set_lambda(array_lambda[i]);
            IDistr = &GD;
            dataset = new float[array_dataset_len[i]];
            for (int j = 0; j < array_dataset_len[i]; j++) {
                dataset[j] = IDistr->modeling_random_x();
            }
            ED = new EmpiricDistribution(*IDistr, array_dataset_len[i]);
            IDistr = ED;

            double expectation_dataset = get_expectation_by_dataset(dataset, dataset + array_dataset_len[i]);
            double density_dataset = get_density_by_dataset(array_mu[i], dataset, dataset + array_dataset_len[i]);
            double assym_dataset = get_asymmetry_by_dataset(dataset, dataset + array_dataset_len[i]);
            double excess_dataset = get_excess_by_dataset(dataset, dataset + array_dataset_len[i]);
            double dispersion_dataset = get_dispersion_by_dataset(dataset, dataset + array_dataset_len[i]);
            double expectation_class = IDistr->get_expectation();
            double density_class = IDistr->get_density(array_mu[i]);
            double assym_class = IDistr->get_asymmetry();
            double excess_class = IDistr->get_excess();
            double dispersion_class = IDistr->get_dispersion();

            assert(abs(expectation_dataset - expectation_class) <= 0.1);
            assert(abs(density_dataset - density_class) <= 0.1);
            assert(abs(assym_dataset - assym_class) <= 0.1);
            assert(abs(excess_dataset - excess_class) <= 0.1);
            assert(abs(dispersion_dataset - dispersion_class) <= 0.1);

            cout << "Тест №" << i + 1 << endl;
            cout << "Мат ожидание: " << expectation_dataset << '\t' << expectation_class << endl;
            cout << "Плотность в мат ожидании: " << density_dataset << "\t" << density_class << endl;
            cout << "Коэффициент асимметрии: " << assym_dataset << "\t" << assym_class << endl;
            cout << "Коэффициент эксцесса: " << excess_dataset << "\t" << excess_class << endl;
            cout << "Дисперсия: " << dispersion_dataset << "\t" << dispersion_class << endl << endl;
        } catch (...) {
            std::cout << "Ошибка при параметрах: nu - " << GD.get_nu() << " mu - " << GD.get_mu() << " lambda - "
                    << GD.get_lambda() << std::endl;
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ТЕСТИРОВАНИЕ КЛАССА ЭМПИРИЧЕСКОГО РАСПРЕДЕЛЕНИЯ ПО СМЕСИ РАСПРЕДЕЛЕНИй" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 3; i++) {
        try {
            MD.first_set_nu(array_nu1[i]);
            MD.first_set_mu(array_mu1[i]);
            MD.first_set_lambda(array_lambda1[i]);
            MD.second_set_nu(array_nu2[i]);
            MD.second_set_mu(array_mu2[i]);
            MD.second_set_lambda(array_lambda2[i]);
            MD.set_p(array_proba[i]);
            IDistr = &MD;
            dataset = new float[array_dataset_len[i]];
            for (int j = 0; j < array_dataset_len[i]; j++) {
                dataset[j] = IDistr->modeling_random_x();
            }
            float mu = IDistr->get_expectation();

            ED = new EmpiricDistribution(MD, array_dataset_len[i]);
            IDistr = ED;
            double expectation_dataset = get_expectation_by_dataset(dataset, dataset + array_dataset_len[i]);
            double density_dataset = get_density_by_dataset(mu, dataset, dataset + array_dataset_len[i]);
            double assym_dataset = get_asymmetry_by_dataset(dataset, dataset + array_dataset_len[i]);
            double excess_dataset = get_excess_by_dataset(dataset, dataset + array_dataset_len[i]);
            double dispersion_dataset = get_dispersion_by_dataset(dataset, dataset + array_dataset_len[i]);
            double expectation_class = IDistr->get_expectation();
            double density_class = IDistr->get_density(mu);
            double assym_class = IDistr->get_asymmetry();
            double excess_class = IDistr->get_excess();
            double dispersion_class = IDistr->get_dispersion();

            assert(abs(expectation_dataset - expectation_class) <= 5.0);
            assert(abs(density_dataset - density_class) <= 5.0);
            assert(abs(assym_dataset - assym_class) <= 5.0);
            assert(abs(excess_dataset - excess_class) <= 5.0);
            assert(abs(dispersion_dataset - dispersion_class) <= 5.0);

            cout << "Тест №" << i + 1 << endl;
            cout << "Мат ожидание: " << expectation_dataset << '\t' << expectation_class << endl;
            cout << "Плотность в мат ожидании: " << density_dataset << "\t" << density_class << endl;
            cout << "Коэффициент асимметрии: " << assym_dataset << "\t" << assym_class << endl;
            cout << "Коэффициент эксцесса: " << excess_dataset << "\t" << excess_class << endl;
            cout << "Дисперсия: " << dispersion_dataset << "\t" << dispersion_class << endl << endl;
        } catch (...) {
            std::cout << "Ошибка при параметрах: \nnu1 - " << MD.first_get_nu() << " mu1 - " << MD.first_get_mu()
                    << " lambda1 - " << MD.first_get_lambda() << endl;
            std::cout << "nu2 - " << MD.second_get_nu() << " mu2 - " << MD.second_get_mu() << " lambda2 - "
                    << MD.second_get_lambda() << endl;
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;
}
