#ifndef OOP_EMPIRICDISTRIBUTION_H
#define OOP_EMPIRICDISTRIBUTION_H

#include "string"
#include <limits>
#include "../GeneralDistribution/GeneralDistribution.h"


using namespace std;

class EmpiricDistribution : public IDistribution, public IPersistent, public IObserverable{
    float *dataset = nullptr;
    float *density = nullptr;
    int dataset_len = 0;
    int density_array_len = 0;
    float max_value = numeric_limits<float>::lowest(); // Минимальное возможное значение для float
    float min_value = numeric_limits<float>::max(); // Максимальное возможное значение для float


public:
    EmpiricDistribution(const std::string &filename);

    EmpiricDistribution(IDistribution &distribution, int new_dataset_len);

    EmpiricDistribution(const EmpiricDistribution &other);

    EmpiricDistribution &operator=(const EmpiricDistribution &other);

    float get_density(float x) override;

    float get_expectation() override;

    float get_dispersion() override;

    float get_excess() override;

    float get_asymmetry() override;

    void save_to_file(const std::string &filename) const override;

    void load_from_file(const std::string &filename) override;

    void show_dataset();

    float modeling_random_x() override;

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
