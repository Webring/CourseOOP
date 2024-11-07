#ifndef OOP_MIXDISTRIBUTION_H
#define OOP_MIXDISTRIBUTION_H
#include "../GeneralDistribution/GeneralDistribution.h"

template<class Distribution1, class Distribution2>
class MixDistribution : public IDistribution, public IPersistent {
    Distribution1 first;
    Distribution2 second;
    float p;

public:
    MixDistribution(float nu1, float mu1, float lambda1, float nu2, float mu2, float lambda2, float propose);

    float get_density(float x) override;
    float get_expectation() override;
    float get_dispersion() override;
    float get_excess() override;
    float get_asymmetry() override;

    float get_random_from_0_to_1();
    float modeling_random_x() override;

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

    void save_to_file(const string &filename) const override;
    void load_from_file(const string &filename) override;
};

#include "MixDistribution.tpp"
#endif //OOP_MIXDISTRIBUTION_H
