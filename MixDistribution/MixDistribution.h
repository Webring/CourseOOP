#ifndef OOP_MIXDISTRIBUTION_H
#define OOP_MIXDISTRIBUTION_H
#include "../GeneralDistribution/GeneralDistribution.h"


class MixDistribution {
    GeneralDistribution first;
    GeneralDistribution second;
    float p;

public:
    MixDistribution(float nu1, float mu1, float lambda1, float nu2, float mu2, float lambda2, float propose);

    float get_density(float &x);

    float get_expectation();

    float get_dispersion();

    float get_excess();

    float get_asymmetry();

    float get_random_from_0_to_1();

    float random_value();

    float first_get_nu();

    float first_get_mu();

    float first_get_lambda();

    float second_get_nu();

    float second_get_mu();

    float second_get_lambda();

    void first_set_nu(float &value);

    void first_set_mu(float &value);

    void first_set_lambda(float &value);

    void second_set_nu(float &value);

    void second_set_mu(float &value);

    void second_set_lambda(float &value);

    void set_p(const float &value);

    void save_to_file(const string &filename) const;

    void load_from_file(const string &filename);
};

#endif //OOP_MIXDISTRIBUTION_H
