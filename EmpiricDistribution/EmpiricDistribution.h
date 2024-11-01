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

    EmpiricDistribution(GeneralDistribution &distribution, int new_dataset_len);

    EmpiricDistribution(MixDistribution &distribution, int new_dataset_len);

    EmpiricDistribution(const EmpiricDistribution &other);

    EmpiricDistribution &operator=(const EmpiricDistribution &other);

    float get_density(float x);

    float get_expectation();

    float get_dispersion();

    float get_excess();

    float get_asymmetry();

    void save_to_file(const std::string &filename);

    void load_from_file(const std::string &filename);

    void show_dataset();

    void density_to_file(const string &filename);

    void fill_density_array();

    EmpiricDistribution modeling_sample_by_sample();

    float *getDataset() const;

    float *getDensity() const;

    int getDatasetLen() const;

    int getDensityArrayLen() const;

    float getMaxValue() const;

    float getMinValue() const;

    void setDataset(const float *data, int length);
};


#endif //OOP_EMPIRICDISTRIBUTION_H
