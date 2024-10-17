//
// Created by Viktor Serov on 17.10.2024.
//
#include "GeneralDistribution/GeneralDistribution.h"
#include "test.h"
#include "cmath"
#include "math.h"
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

            if (abs(expectation_general - expectation_class) > 0.01){
                throw 0;
            }
            if (abs( density_general - density_class) > 0.01){
                throw 0;
            }
            if (abs(assym_general - assym_class) > 0.01){
                throw 0;
            }
            if (abs(excess_general - excess_class) > 0.01){
                throw 0;
            }
            if (abs(dispersion_general - dispersion_class) > 0.01){
                throw 0;
            }
            cout<<"Тест №"<< i+1 << endl;
            cout<<"Мат ожидание: "<< expectation_general <<'\t'<< expectation_class<<endl;
            cout<<"Плотность в мат ожидании: "<< density_general << "\t" << density_class<<endl;
            cout<<"Коэффициент асимметрии: "<< assym_general << "\t" << assym_class<<endl;
            cout<<"Коэффициент эксцесса: "<< excess_general << "\t" << excess_class<<endl;
            cout<<"Дисперсия: "<< dispersion_general << "\t" << dispersion_class<<endl;
        }
        catch (int error){
            if(error == 0){
                std::cout << "Ошибка при параметрах: nu - " << GD.get_nu() << " mu - " << GD.get_mu() << " lambda - " << GD.get_lambda() << std::endl;
            }
        }

    }
    return;
}
