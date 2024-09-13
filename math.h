//
// Created by webri on 13.09.2024.
//

#ifndef OOP_MATH_H
#define OOP_MATH_H

#include <cmath>

using namespace std;

float get_random_from_0_to_1();

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef);

//int get_density_by_coefs(float x, float nu_coef, float mu_coef, float lambda_coef) {
//    return 1 / (2 * beta(nu_coef + 1, nu_coef + 1)) * pow((1 - pow(((x - mu_coef) / lambda_coef), 2)) / 4, nu_coef);
//}
//
//float get_expectation_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
//    return 0;
//}
//
//float get_dispersion_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
//    return pow(lambda_coef, 4) * (1 / (2 * nu_coef + 3));
//}
//
//float get_excess_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
//    return -6 / (1 * nu_coef + 5);
//}

#endif //OOP_MATH_H
