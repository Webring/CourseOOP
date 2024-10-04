#ifndef GENERALDISTRIBUTION_H
#define GENERALDISTRIBUTION_H

#include <string>
#include "fstream"
#include "../utils.h"
#include "cmath"

using namespace std;

class GeneralDistribution {
    float nu, mu, lambda;
public:
    GeneralDistribution(float nu_coef, float mu_coef, float lambda_coef) {
        nu = nu_coef;
        mu= mu_coef;
        lambda = lambda_coef;
    }
    float get_nu() const;
    float get_mu() const;
    float get_lambda() const;

    void set_nu(float nu_coef);
    void set_mu(float mu_coef);
    void set_lambda(float lambda_coef);

    float modeling_random_x();
    float get_density(float x);
    float get_expectation();
    float get_dispersion();
    float get_excess();
    float get_asymmetry();

    void save_to_file(const std::string& filename) const;
    void load_from_file(const std::string& filename);
};


#endif //GENERALDISTRIBUTION_H
