#ifndef INTERFACES_H
#define INTERFACES_H

#include "forward_list"

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


struct IObserver {
    virtual void update() =0;
};


struct IObserverable {
    std::forward_list<IObserver *> observers;

    void attach(IObserver *obs) {
        observers.push_front(obs);
    }

    void detach(IObserver *obs) {
        observers.remove(obs);
    }

    void notify() {
        for (auto &elem: observers) {
            elem->update();
        };
    }
};
#endif
