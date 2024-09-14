#include "math.h"

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef) {
    float r1 = get_random_from_0_to_1();
    float r2 = get_random_from_0_to_1();
    return lambda_coef * sqrt(1 - pow(r1, 1 / (nu_coef + 0.5))) * cos(2 * M_PI * r2) + mu_coef;
}

float get_random_from_0_to_1() {
    float r;
    do r = (float) rand() / RAND_MAX; while (r == 0. || r == 1.);
    return r;
}

int get_density_by_coefs(float x, float nu_coef, float mu_coef, float lambda_coef) {
    return 1 / (2 * beta(nu_coef + 1, nu_coef + 1)) * pow((1 - pow(((x - mu_coef) / lambda_coef), 2)) / 4, nu_coef);
}

float get_expectation_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return mu_coef;
}

float get_dispersion_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return pow(lambda_coef, 4) * (1 / (2 * nu_coef + 3));
}

float get_excess_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return -6 / (1 * nu_coef + 5);
}

float get_asymmetry_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return pow(get_dispersion_by_coefs(nu_coef, mu_coef, lambda_coef), -1.5) * (
               mu_coef - 3 * mu_coef * mu_coef + 2 * mu_coef * mu_coef * mu_coef);
}


float get_expectation_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += *it;
        counter++;
    }
    return sum / counter;
}

float get_dispersion_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 2);
        counter++;
    }
    return sum / counter;
}

float get_excess_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float dispersion = get_dispersion_by_dataset(dataset_begin, dataset_end);

    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 4);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 2) - 3;
}

float get_asymmetry_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float dispersion = get_dispersion_by_dataset(dataset_begin, dataset_end);
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 3);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 1.5);
}

int get_mix_density_by_coefs(float x, float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                             float mu_coef_2, float lambda_coef_2, float p) {
    return (1 - p) * get_density_by_coefs(x, nu_coef_1, mu_coef_1, lambda_coef_1) + p * get_density_by_coefs(
               x, nu_coef_2, mu_coef_2, lambda_coef_2);
}

float get_mix_expectation_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                   float mu_coef_2, float lambda_coef_2, float p) {
    return mu_coef_1 * p + mu_coef_2 * (1 - p);
}

float get_mix_dispersion_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                  float mu_coef_2, float lambda_coef_2, float p) {
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    return p * (pow(mu_coef_1, 2) + dispersion_1) + (1 - p) * (pow(mu_coef_2, 2) + dispersion_2) - pow(expectation, 2);
}

float get_mix_excess_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                              float mu_coef_2, float lambda_coef_2, float p) {
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    float dispersion = get_mix_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                   mu_coef_2, lambda_coef_2, p);
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);

    float asymmetry_1 = get_asymmetry_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float asymmetry_2 = get_asymmetry_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);
    float excess_1 = get_excess_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float excess_2 = get_excess_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);


    return (((p * (pow(mu_coef_1 - expectation, 4) + 6 * pow(mu_coef_1 - expectation, 2) * dispersion_1 + 4 * (
                       mu_coef_1 - expectation) * pow(dispersion_1, 1.5) * asymmetry_1 + pow(dispersion_1, 2) * (
                       excess_1 + 3))) + ((1 - p) * (pow(mu_coef_2 - expectation, 4) + 6 * pow(
                                                         mu_coef_2 - expectation, 2) * dispersion_2 + 4 * (
                                                         mu_coef_2 - expectation) * pow(dispersion_2, 1.5) * asymmetry_2
                                                     + pow(dispersion_2, 2) * (
                                                         excess_2 + 3)))) / pow(dispersion, 2)) - 3;
}

float get_mix_asymmetry_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                 float mu_coef_2, float lambda_coef_2, float p) {
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    float dispersion = get_mix_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                   mu_coef_2, lambda_coef_2, p);
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);

    float sum = p * (pow(mu_coef_1 - expectation, 3) + 3 * (mu_coef_1 - expectation) * dispersion_1 + pow(
                         dispersion_1, 1.5) + get_asymmetry_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1));
    sum += (1 - p) * (pow(mu_coef_2 - expectation, 3) + 3 * (mu_coef_2 - expectation) * dispersion_2 + pow(
                          dispersion_2, 1.5) + get_asymmetry_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2));

    return pow(dispersion, -1.5) * sum;
}


float get_density_by_dataset(float *dataset) {

}
