#ifndef OOP_MATH_H
#define OOP_MATH_H

#include <cmath>
#include "iostream"

using namespace std;

float get_random_from_0_to_1();

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef);

int get_density_by_coefs(float x, float nu_coef, float mu_coef, float lambda_coef);

float get_expectation_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_dispersion_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_excess_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_expectation_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_dispersion_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_excess_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_asymmetry_by_dataset(const float *dataset_begin, const float *dataset_end);

#endif
