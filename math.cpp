//
// Created by webri on 13.09.2024.
//

#include "math.h"
#include "cmath"

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef) {
    float r1 = get_random_from_0_to_1();
    float r2 = get_random_from_0_to_1();
    return lambda_coef * sqrt(1 - pow(r1, 1 / (nu_coef + 0.5))) * cos(2 * M_PI * r2) + mu_coef;
}

float get_random_from_0_to_1() {
    float r;
    do r = (float) rand() / RAND_MAX; while (r == 0. || r == 1.);
    return r;
}