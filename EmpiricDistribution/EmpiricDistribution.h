//
// Created by Viktor Serov on 22.10.2024.
//

#ifndef OOP_EMPIRICDISTRIBUTION_H
#define OOP_EMPIRICDISTRIBUTION_H

#include "string"
#include <limits>
#include "../GeneralDistribution/GeneralDistribution.h"
#include "../MixDistribution/MixDistribution.h"


using namespace std;

class EmpiricDistribution {
    float *dataset = nullptr;
    float *density = nullptr;
    int dataset_len = 0;
    int density_array_len = 0;
    float max_value = numeric_limits<float>::lowest(); // Минимальное возможное значение для float
    float min_value = numeric_limits<float>::max(); // Максимальное возможное значение для float


public:
    EmpiricDistribution(const std::string &filename);
    EmpiricDistribution(const GeneralDistribution &distribution);
    EmpiricDistribution(const MixDistribution &distribution);

    EmpiricDistribution(const EmpiricDistribution &other);

    float get_density(float x);

    float get_expectation();

    float get_dispersion();

    float get_excess();

    float get_asymmetry();

    void save_to_file(const std::string &filename) const;

    void load_from_file(const std::string &filename);
};


#endif //OOP_EMPIRICDISTRIBUTION_H
