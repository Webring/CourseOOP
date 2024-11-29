#ifndef ESTIMATE_H
#define ESTIMATE_H
#include "../EmpiricDistribution/EmpiricDistribution.h"
#define var 13
#define degree (2 * (var-10))

class Estimate : public IObserver {
    EmpiricDistribution &emperic_distribution;
    double sigma;
    double c;
    int p;
    double mu;

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

    double weight(double x) const; // функция для вычисления веса
    void update() override {
        estimate();
    }
};


#endif //ESTIMATE_H
