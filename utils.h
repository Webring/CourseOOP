#ifndef UTILS_H
#define UTILS_H
// Генерация реализации (случайное значение от 0 до 1)
float get_random_from_0_to_1() {
    float realisation_of_value;
    do realisation_of_value = (float) rand() / RAND_MAX; while (realisation_of_value == 0. || realisation_of_value == 1.);
    return realisation_of_value;
}

double beta(double x, double y) {
    return tgamma(x) * tgamma(y) / tgamma(x + y);
}
#endif //UTILS_H
