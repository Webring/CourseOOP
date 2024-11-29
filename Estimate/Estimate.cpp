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

    for (int k = 0; k < p; k++) {
        for (int i = 0; i < emperic_distribution.getDatasetLen(); i++) {
            // Это сигма
            x = emperic_distribution.getDataset()[i];
            current_w = weight((x - mu) / sigma);
            numerator += current_w * x;
            denominator += current_w;
        }
        mu = numerator / denominator;
    }
}
