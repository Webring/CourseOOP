#ifndef OOP_MATH_H
#define OOP_MATH_H

#include <cmath>
#include "iostream"

using namespace std;
float get_random_from_0_to_1();
double beta(double x, double y);

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef);
float modeling_random_mix_x(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                            float mu_coef_2, float lambda_coef_2, float p);

float get_density_by_coefs(float x, float nu_coef, float mu_coef, float lambda_coef);

float get_mix_density_by_coefs(float x, float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                               float mu_coef_2, float lambda_coef_2, float p);

float get_mix_expectation_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                   float mu_coef_2, float lambda_coef_2, float p);

float get_mix_dispersion_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                  float mu_coef_2, float lambda_coef_2, float p);

float get_mix_excess_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                              float mu_coef_2, float lambda_coef_2, float p);

float get_mix_asymmetry_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                 float mu_coef_2, float lambda_coef_2, float p);

float get_expectation_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_dispersion_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_excess_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

float get_expectation_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_dispersion_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_excess_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_asymmetry_by_dataset(const float *dataset_begin, const float *dataset_end);

float get_density_by_dataset(float x, float *dataset_begin, float *dataset_end);

float get_asymmetry_by_coefs(float nu_coef, float mu_coef, float lambda_coef);

int get_density_array(float *dataset_begin, float *dataset_end, float *&number_of_occurrences_array_begin, float *&number_of_occurrences_array_end);

float* modeling_sample_based_on_sample(int sample_volume, float *dataset_begin, float *dataset_end);

#endif
