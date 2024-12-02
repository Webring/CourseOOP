#include "Estimate.h"

double Estimate::weight(double z) const {
    if (abs(z) < c) {
        return pow(1 - pow(z / c, degree), 2);
    }
    return 0;
}


void Estimate::estimate() {
    mu = emperic_distribution.get_expectation();

    double numerator = 0, denominator = 0, x = 0, current_w = 0;
    double z;
    for (int k = 0; k < p; k++) {
        for (int i = 0; i < emperic_distribution.getDatasetLen(); i++) {
            x = emperic_distribution.getDataset()[i];
            z = (x - mu) / sigma;
            current_w = weight(z);
            numerator += current_w * x;
            denominator += current_w;
            if(k == p-1){
                weightValues.push_back(current_w);
            }
        }
        mu = numerator / denominator;
    }
}

