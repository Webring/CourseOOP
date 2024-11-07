#ifndef INTERFACES_H
#define INTERFACES_H

struct IDistribution {
    virtual float modeling_random_x() = 0;

    virtual float get_density(float x) = 0;

    virtual float get_expectation() = 0;

    virtual float get_dispersion() = 0;

    virtual float get_excess() = 0;

    virtual float get_asymmetry() = 0;
};

struct IPersistent {
    virtual void save_to_file(const std::string &filename) const = 0;

    virtual void load_from_file(const std::string &filename) = 0;
};
#endif