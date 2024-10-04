#include "GeneralDistribution.h"

float GeneralDistribution::get_nu() const {
    return nu;
}

float GeneralDistribution::get_mu() const {
    return mu;
}

float GeneralDistribution::get_lambda() const {
    return lambda;
}

void GeneralDistribution::set_nu(float nu_coef) {
    nu = nu_coef;
}

void GeneralDistribution::set_mu(float mu_coef) {
    mu = mu_coef;
}

void GeneralDistribution::set_lambda(float lambda_coef) {
    lambda = lambda_coef;
}

float GeneralDistribution::modeling_random_x() {
    float realisation_of_value_1 = get_random_from_0_to_1();
    float realisation_of_value_2 = get_random_from_0_to_1();
    return lambda * sqrt(1 - pow(realisation_of_value_1, 1 / (nu + 0.5))) * cos(2 * M_PI * realisation_of_value_2) + mu;
}

float GeneralDistribution::get_density(float x) {
    return 1.0 / (lambda * 2 * beta(nu + 1, nu + 1)) * pow((1 - pow(((x - mu) / lambda), 2)) / 4, nu);
}

float GeneralDistribution::get_expectation() {
    return mu;
}

float GeneralDistribution::get_dispersion() {
    return pow(lambda, 2) * (1 / (2 * nu + 3));
}

float GeneralDistribution::get_excess() {
    return -6.0f / (2 * nu + 5);
}

float GeneralDistribution::get_asymmetry() {
    return 0;
}

void GeneralDistribution::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << nu << " " << mu << " " << lambda;
        file.close();
    } else {
        throw runtime_error("Ошибка открытия файла для записи!");
    }
}

void GeneralDistribution::load_from_file(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> nu >> mu >> lambda;
        file.close();
    } else {
        throw runtime_error("Ошибка открытия файла для чтения!");

    }
}