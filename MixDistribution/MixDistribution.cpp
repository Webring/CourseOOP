#include "MixDistribution.h"
#include "../GeneralDistribution/GeneralDistribution.h"


MixDistribution::MixDistribution(float nu1, float mu1, float lambda1, float nu2, float mu2, float lambda2, float propose){
    first.set_mu(mu1);
    first.set_nu(nu1);
    first.set_lambda(lambda1);
    second.set_mu(mu2);
    second.set_nu(nu2);
    second.set_lambda(lambda2);
    set_p(propose);
}

float MixDistribution::get_density(float &x)
{
    return p * first.get_density(x) + (1 - p) * second.get_density(x);
}

float MixDistribution::get_expectation(){
    return first.get_mu() * p + second.get_mu() * (1 - p);
}
float MixDistribution::get_dispersion() {
    return (1 - p) * (pow(first.get_mu(), 2) + first.get_dispersion()) + p * (pow(second.get_mu(), 2) + second.get_dispersion()) - pow(get_expectation(), 2);
}

float MixDistribution::get_excess() {
    float element_1 = (1 - p) * (pow(first.get_mu() -get_expectation(), 4) + 6 * pow(first.get_mu() -get_expectation(), 2) * first.get_dispersion() + 4 * (
            first.get_mu() -get_expectation()) * pow(first.get_dispersion(), 1.5) * first.get_asymmetry() + pow(first.get_dispersion(), 2) * (first.get_excess() + 3));
    float element_2 = p * (pow(second.get_expectation() -get_expectation(), 4) + 6 * pow(second.get_expectation() -get_expectation(), 2) * second.get_dispersion() + 4 * (
            second.get_expectation() -get_expectation()) * pow(second.get_dispersion(), 1.5) * second.get_asymmetry() + pow(second.get_dispersion(), 2) * (second.get_excess() + 3));


    return ((element_1 + element_2) / pow(get_dispersion(), 2)) - 3;
}

float MixDistribution::get_asymmetry() {
    float sum = (1 - p) * (pow(first.get_expectation() -get_expectation(), 3) + 3 * (first.get_expectation() -get_expectation()) * first.get_dispersion() + pow(
            first.get_dispersion(), 1.5) * first.get_asymmetry());
    sum += p * (pow(second.get_expectation() -get_expectation(), 3) + 3 * (second.get_expectation() -get_expectation()) * second.get_dispersion() + pow(
            second.get_dispersion(), 1.5) * second.get_asymmetry());

    return pow(get_dispersion(), -1.5) * sum;
}
float MixDistribution::get_random_from_0_to_1() {
    float realisation_of_value;
    do realisation_of_value = (float) rand() / RAND_MAX; while (realisation_of_value == 0. || realisation_of_value == 1.);
    return realisation_of_value;
}


float MixDistribution::random_value()
{
    float realisation_of_value = get_random_from_0_to_1();
    if (realisation_of_value <= p) {
        return second.modeling_random_x();
    }
    return first.modeling_random_x();
}
float MixDistribution::first_get_nu(){
    return first.get_nu();
};
float MixDistribution::first_get_mu(){
    return first.get_mu();
};
float MixDistribution::first_get_lambda(){
    return first.get_lambda();
};
float MixDistribution::second_get_nu(){
    return second.get_nu();
};
float MixDistribution::second_get_mu(){
    return second.get_nu();
};
float MixDistribution::second_get_lambda(){
    return second.get_nu();
};

void MixDistribution::first_set_nu(float &value){
    first.set_nu(value);
}

void MixDistribution::first_set_mu(float &value){
    first.set_mu(value);
}

void MixDistribution::first_set_lambda(float &value){
    first.set_lambda(value);
}

void MixDistribution::second_set_nu(float &value){
    second.set_nu(value);
}

void MixDistribution::second_set_mu(float &values){
    second.set_mu(values);
}

void MixDistribution::second_set_lambda(float &value){
    second.set_lambda(value);
}

void MixDistribution::set_p(const float &value){
    if (p < 0 or p > 1) throw range_error("P must be in range [0, 1]");
    p = value;
}

void MixDistribution::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << first.get_nu() << " " << first.get_mu() << " " << first.get_lambda() << " "
             << second.get_nu() << " " << second.get_mu() << " " << second.get_lambda() << " " << p;
        file.close();
    } else {
        throw runtime_error("Ошибка открытия файла для записи!");
    }
}
void MixDistribution::load_from_file(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        float nu;
        float mu;
        float lambda;
        file >> nu >> mu >> lambda;
        first_set_nu(nu);
        first_set_mu(mu);
        first_set_lambda(lambda);
        file >> nu >> mu >> lambda;
        second_set_nu(nu);
        second_set_mu(mu);
        second_set_lambda(lambda);
        file >> p;
        file.close();
    } else {
        throw runtime_error("Ошибка открытия файла для чтения!");

    }
}
