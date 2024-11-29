#ifndef ESTIMATE_H
#define ESTIMATE_H
#include "../EmpiricDistribution/EmpiricDistribution.h"



class Estimate : public IObserver {
    EmpiricDistribution &e;
    double sigma;
    double c;
    int p;
    double mu;

    void estimate();
public:
    Estimate(EmpiricDistribution &e0, double sigma0, double c0, int p0 = 100): e(e0), sigma(sigma0), c(c0), p(p0) {
        estimate();
        e.attach(this);
    }

    ~Estimate() { e.detach(this); }

    double weigh(double x); // функция для вычисления веса
    void update() override {
        estimate();
    }

};


#endif //ESTIMATE_H
