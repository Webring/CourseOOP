#ifndef ESTIMATE_H
#define ESTIMATE_H
#include "../EmpiricDistribution/EmpiricDistribution.h"
#include "vector"
#define var 13
#define degree (2 * (var-10))

using namespace std;

class Estimate : public IObserver {
    EmpiricDistribution &emperic_distribution;
    double sigma;
    double c;
    int p;
    double mu;
    vector<vector<double>> roValues;
    vector<vector<double>> zValues;

    void estimate();

public:
    Estimate(EmpiricDistribution &e0, double sigma0, double c0, int p0 = 100): emperic_distribution(e0),
                                                                               sigma(sigma0),
                                                                               c(c0),
                                                                               p(p0) {
        estimate();
        emperic_distribution.attach(this);
    }

    ~Estimate() {
        emperic_distribution.detach(this);
    }

    double get_mu() {
        return mu;
    };

    double ro(double x);
    vector<vector<double>> get_ro() {
        return roValues;
    };
    vector<vector<double>> get_z() {
        return zValues;
    }

    double weight(double x) const; // функция для вычисления веса
    void update() override {
        estimate();
    }
};


#endif //ESTIMATE_H
