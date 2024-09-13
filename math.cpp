//
// Created by webri on 13.09.2024.
//

#include "math.h"

float get_random_from_0_to_1() {
    float r;
    do r = (float) rand() / RAND_MAX; while (r == 0. || r == 1.);
    return r;
}