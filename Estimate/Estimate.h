#ifndef ESTIMATE_H
#define ESTIMATE_H
#include "../EmpiricDistribution/EmpiricDistribution.h"
#include "vector"
#include "iostream"
#define var 12
#define degree (2 * (var-10))

using namespace std;

class Estimate : public IObserver {
    EmpiricDistribution &emperic_distribution;
    double sigma;
    double c;
    int p;
    double mu;
    vector<double> weightValues;

    void estimate();

public:
    Estimate(EmpiricDistribution &e0, double sigma0, double c0, int p0 = 100): emperic_distribution(e0),
                                                                               sigma(sigma0),
                                                                               c(c0),
                                                                               p(p0) {
        emperic_distribution.attach(this);
    }

    ~Estimate() {
        emperic_distribution.detach(this);
    }

    double get_mu() {
        return mu;
    };

    vector<double> get_weight() {
        return weightValues;
    };
    double get_sigma(){
        return sigma;
    };
    double get_c(){
        return c;
    };
    int pet_p(){
        return p;
    };

    void set_sigma(double &sigma){
        this->sigma = sigma;
    };
    void set_c(double &c){
        this->c = c;
    };
    void set_p(int &p){
        this->p = p;
    };



    double weight(double x) const;
    void update() override {
        estimate();
    }
};


#endif //ESTIMATE_H
