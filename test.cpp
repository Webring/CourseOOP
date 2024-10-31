//
// Created by Viktor Serov on 17.10.2024.
//
#include "GeneralDistribution/GeneralDistribution.h"
#include "MixDistribution/MixDistribution.h"
#include "EmpiricDistribution/EmpiricDistribution.h"
#include "test.h"
#include "cmath"
#include "math.h"
#include <cassert>

void test(){
    GeneralDistribution GD;
    float array_nu[]{1, 0, 2, 3, 4.5};
    float array_mu[]{0, 1, 2, -3, -1};
    float array_lambda[]{1, 2, 4.2, 5, 2};

    for (int i = 0; i < 5;i++){
        try{
            GD.set_nu(array_nu[i]);
            GD.set_mu(array_mu[i]);
            GD.set_lambda(array_lambda[i]);
            double expectation_general = get_expectation_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double density_general = get_density_by_coefs(array_mu[i], array_nu[i], array_mu[i], array_lambda[i]);
            double assym_general = get_asymmetry_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double excess_general = get_excess_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double dispersion_general = get_dispersion_by_coefs(array_nu[i], array_mu[i], array_lambda[i]);
            double expectation_class = GD.get_expectation();
            double density_class = GD.get_density(array_mu[i]);
            double assym_class = GD.get_asymmetry();
            double excess_class = GD.get_excess();
            double dispersion_class = GD.get_dispersion();

            assert(abs(expectation_general - expectation_class) <= 0.01);
            assert(abs( density_general - density_class) <= 0.01);
            assert(abs(assym_general - assym_class) <= 0.01);
            assert(abs(excess_general - excess_class) <= 0.01);
            assert(abs(dispersion_general - dispersion_class) <= 0.01);

            cout<<"Тест №"<< i+1 << endl;
            cout<<"Мат ожидание: "<< expectation_general <<'\t'<< expectation_class<<endl;
            cout<<"Плотность в мат ожидании: "<< density_general << "\t" << density_class<<endl;
            cout<<"Коэффициент асимметрии: "<< assym_general << "\t" << assym_class<<endl;
            cout<<"Коэффициент эксцесса: "<< excess_general << "\t" << excess_class<<endl;
            cout<<"Дисперсия: "<< dispersion_general << "\t" << dispersion_class<<endl<< endl;
        }
        catch (...){
            std::cout << "Ошибка при параметрах: nu - " << GD.get_nu() << " mu - " << GD.get_mu() << " lambda - " << GD.get_lambda() << std::endl;
        }

    }
    MixDistribution MD(1,0,1,1,0,1,0.5);
    float array_nu1[]{1, 6, 4};
    float array_mu1[]{0, 0, -1};
    float array_lambda1[]{1, 1, 6};
    float array_nu2[]{1, 1, 2};
    float array_mu2[]{0, 2, 0};
    float array_lambda2[]{1, 5};
    float array_proba[]{0.5, 0.5,0.3};

    for(int i = 0; i < 3;i++){
        try{
            MD.first_set_nu(array_nu1[i]);
            MD.first_set_mu(array_mu1[i]);
            MD.first_set_lambda(array_lambda1[i]);
            MD.second_set_nu(array_nu2[i]);
            MD.second_set_mu(array_mu2[i]);
            MD.second_set_lambda(array_lambda2[i]);
            MD.set_p(array_proba[i]);
            float mu = MD.get_expectation();

            double expectation_mixed = get_mix_expectation_by_coefs(array_nu1[i],array_mu1[i],array_lambda1[i],array_nu2[i],array_mu2[i],array_lambda2[i],array_proba[i]);
            double density_mixed = get_mix_density_by_coefs(mu,array_nu1[i],array_mu1[i],array_lambda1[i],array_nu2[i],array_mu2[i],array_lambda2[i],array_proba[i]);
            double assym_mixed = get_mix_asymmetry_by_coefs(array_nu1[i],array_mu1[i],array_lambda1[i],array_nu2[i],array_mu2[i],array_lambda2[i],array_proba[i]);
            double excess_mixed = get_mix_excess_by_coefs(array_nu1[i],array_mu1[i],array_lambda1[i],array_nu2[i],array_mu2[i],array_lambda2[i],array_proba[i]);
            double dispersion_mixed = get_mix_dispersion_by_coefs(array_nu1[i],array_mu1[i],array_lambda1[i],array_nu2[i],array_mu2[i],array_lambda2[i],array_proba[i]);
            double expectation_class = MD.get_expectation();
            double density_class = MD.get_density(mu);
            double assym_class = MD.get_asymmetry();
            double excess_class = MD.get_excess();
            double dispersion_class = MD.get_dispersion();

            assert(abs(expectation_mixed - expectation_class) <= 0.01);
            assert(abs( density_mixed - density_class) <= 0.01);
            assert(abs(assym_mixed - assym_class) <= 0.01);
            assert(abs(excess_mixed - excess_class) <= 0.01);
            assert(abs(dispersion_mixed - dispersion_class) <= 0.01);

            cout<<"Тест №"<< i+1 << endl;
            cout<<"Мат ожидание: "<< expectation_mixed <<'\t'<< expectation_class<<endl;
            cout<<"Плотность в мат ожидании: "<< density_mixed << "\t" << density_class<<endl;
            cout<<"Коэффициент асимметрии: "<< assym_mixed << "\t" << assym_class<<endl;
            cout<<"Коэффициент эксцесса: "<< excess_mixed << "\t" << excess_class<<endl;
            cout<<"Дисперсия: "<< dispersion_mixed << "\t" << dispersion_class<<endl<< endl;
        }
        catch (...){
            std::cout << "Ошибка при параметрах: \nnu1 - " << MD.first_get_nu() << " mu1 - " << MD.first_get_mu() << " lambda1 - " << MD.first_get_lambda() << endl;
            std::cout << "nu2 - "<< MD.second_get_nu() << " mu2 - " << MD.second_get_mu() << " lambda2 - " << MD.second_get_lambda() << endl;
        }
    }

    return;
}
