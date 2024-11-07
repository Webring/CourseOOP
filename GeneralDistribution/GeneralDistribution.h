#ifndef GENERALDISTRIBUTION_H
#define GENERALDISTRIBUTION_H

#include <string>
#include "fstream"
#include "cmath"
#include "../interfaces.h"

using namespace std;

class GeneralDistribution : public IDistribution, public IPersistent {
    float nu = 1;
    float mu = 0;
    float lambda = 1;

public:
    GeneralDistribution(float nu_coef, float mu_coef, float lambda_coef) {
        nu = nu_coef;
        mu = mu_coef;
        lambda = lambda_coef;
    }

    GeneralDistribution() {
    };

    float get_random_from_0_to_1();

    double beta(double x, double y);

    float get_nu() const;

    float get_mu() const;

    float get_lambda() const;

    void set_nu(float nu_coef);

    void set_mu(float mu_coef);

    void set_lambda(float lambda_coef);

    float modeling_random_x() override;

    float get_density(float x) override;

    float get_expectation() override;

    float get_dispersion() override;

    float get_excess() override;

    float get_asymmetry() override;

    void save_to_file(const std::string &filename) const override;

    void load_from_file(const std::string &filename) override;
};


#endif
