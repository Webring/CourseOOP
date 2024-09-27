#include "math.h"
#include "cmath"

double beta(double x, double y) {
    return std::tgamma(x) * std::tgamma(y) / std::tgamma(x + y);
}

float modeling_random_x(float nu_coef, float mu_coef, float lambda_coef) {
    float realisation_of_value_1 = get_random_from_0_to_1();
    float realisation_of_value_2 = get_random_from_0_to_1();
    return lambda_coef * sqrt(1 - pow(realisation_of_value_1, 1 / (nu_coef + 0.5))) * cos(2 * M_PI * realisation_of_value_2) + mu_coef;
}

float get_random_from_0_to_1() {
    float realisation_of_value;
    do realisation_of_value = (float) rand() / RAND_MAX; while (realisation_of_value == 0. || realisation_of_value == 1.);
    return realisation_of_value;
}

float get_density_by_coefs(float x, float nu_coef, float mu_coef, float lambda_coef) {
    return 1.0 / (2 * beta(nu_coef + 1, nu_coef + 1)) * pow((1 - pow(((x - mu_coef) / lambda_coef), 2)) / 4, nu_coef);
}

float get_expectation_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return mu_coef;
}

float get_dispersion_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return pow(lambda_coef, 2) * (1 / (2 * nu_coef + 3));
}

float get_excess_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return -6.0f / (2 * nu_coef + 5);
}

float get_asymmetry_by_coefs(float nu_coef, float mu_coef, float lambda_coef) {
    return 0;
}

float get_expectation_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += *it;
        counter++;
    }
    return sum / counter;
}

float get_dispersion_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 2);
        counter++;
    }
    return sum / counter;
}

float get_excess_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float dispersion = get_dispersion_by_dataset(dataset_begin, dataset_end);

    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 4);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 2) - 3;
}

float get_asymmetry_by_dataset(const float *dataset_begin, const float *dataset_end) {
    float expectation = get_expectation_by_dataset(dataset_begin, dataset_end);
    float dispersion = get_dispersion_by_dataset(dataset_begin, dataset_end);
    float sum = 0;
    int counter = 0;
    for (auto it = dataset_begin; it != dataset_end; ++it) {
        sum += pow(*it - expectation, 3);
        counter++;
    }
    return (sum / counter) / pow(dispersion, 1.5);
}

float get_mix_density_by_coefs(float x, float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                               float mu_coef_2, float lambda_coef_2, float p) {
    return (1 - p) * get_density_by_coefs(x, nu_coef_1, mu_coef_1, lambda_coef_1) + p * get_density_by_coefs(
            x, nu_coef_2, mu_coef_2, lambda_coef_2);
}

float get_mix_expectation_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                   float mu_coef_2, float lambda_coef_2, float p) {
    return mu_coef_1 * p + mu_coef_2 * (1 - p);
}

float get_mix_dispersion_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                  float mu_coef_2, float lambda_coef_2, float p) {
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    return (1 - p) * (pow(mu_coef_1, 2) + dispersion_1) + p * (pow(mu_coef_2, 2) + dispersion_2) - pow(expectation, 2);
}

float get_mix_excess_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                              float mu_coef_2, float lambda_coef_2, float p) {
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    float dispersion = get_mix_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                   mu_coef_2, lambda_coef_2, p);
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);

    float asymmetry_1 = get_asymmetry_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float asymmetry_2 = get_asymmetry_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);
    float excess_1 = get_excess_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float excess_2 = get_excess_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);

    float element_1 = (1 - p) * (pow(mu_coef_1 - expectation, 4) + 6 * pow(mu_coef_1 - expectation, 2) * dispersion_1 + 4 * (
                    mu_coef_1 - expectation) * pow(dispersion_1, 1.5) * asymmetry_1 + pow(dispersion_1, 2) * (excess_1 + 3));
    float element_2 = p * (pow(mu_coef_2 - expectation, 4) + 6 * pow(mu_coef_2 - expectation, 2) * dispersion_2 + 4 * (
            mu_coef_2 - expectation) * pow(dispersion_2, 1.5) * asymmetry_2 + pow(dispersion_2, 2) * (excess_2 + 3));


    return ((element_1 + element_2) / pow(dispersion, 2)) - 3;
}

float get_mix_asymmetry_by_coefs(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                                 float mu_coef_2, float lambda_coef_2, float p) {
    float expectation = get_mix_expectation_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                     mu_coef_2, lambda_coef_2, p);
    float dispersion = get_mix_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1, nu_coef_2,
                                                   mu_coef_2, lambda_coef_2, p);
    float dispersion_1 = get_dispersion_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1);
    float dispersion_2 = get_dispersion_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2);

    float sum = (1 - p) * (pow(mu_coef_1 - expectation, 3) + 3 * (mu_coef_1 - expectation) * dispersion_1 + pow(
            dispersion_1, 1.5) * get_asymmetry_by_coefs(nu_coef_1, mu_coef_1, lambda_coef_1));
    sum += p * (pow(mu_coef_2 - expectation, 3) + 3 * (mu_coef_2 - expectation) * dispersion_2 + pow(
            dispersion_2, 1.5) * get_asymmetry_by_coefs(nu_coef_2, mu_coef_2, lambda_coef_2));

    return pow(dispersion, -1.5) * sum;
}

float get_density_by_dataset(float x, float *dataset_begin, float *dataset_end) {
    int len_of_dataset = dataset_end - dataset_begin;
    float number_of_intervals;
    if (len_of_dataset >= 50) {
        number_of_intervals = int(log2(len_of_dataset)) + 1;
    } else {
        number_of_intervals = 8;
    }
    float minimum_number = *dataset_begin;
    float maximum_number = *dataset_begin;
    float *dataset_iterator = dataset_begin;

    while (dataset_iterator < dataset_end) {
        if (*dataset_iterator < minimum_number) {
            minimum_number = *dataset_iterator;
        }
        if (*dataset_iterator > maximum_number) {
            maximum_number = *dataset_iterator;
        }
        dataset_iterator++;
    }
    float range = maximum_number - minimum_number;
    float interval_width = range / number_of_intervals;
    float first_value = minimum_number - interval_width * 0.5;
    float left_border_value = first_value + floor((x - first_value) / interval_width) * interval_width;
    float right_border_value = left_border_value + interval_width;
    float number_of_occurrences = 0;
    dataset_iterator = dataset_begin;
    for (int i = 0; i < len_of_dataset; i++) {
        if (*dataset_iterator >= left_border_value and *dataset_iterator < right_border_value) {
            number_of_occurrences++;
        }
        dataset_iterator++;
    }
    return number_of_occurrences / len_of_dataset;
}

int get_density_array(float *dataset_begin, float *dataset_end, float *&number_of_occurrences_array_begin, float *&number_of_occurrences_array_end) {
    int len_of_dataset = dataset_end - dataset_begin;
    int number_of_intervals;
    if (len_of_dataset >= 50) {
        number_of_intervals = int(log2(len_of_dataset)) + 1;
    } else {
        number_of_intervals = 8;
    }
    float minimum_number = *dataset_begin;
    float maximum_number = *dataset_begin;
    float *dataset_iterator = dataset_begin;

    while (dataset_iterator < dataset_end) {
        if (*dataset_iterator < minimum_number) {
            minimum_number = *dataset_iterator;
        }
        if (*dataset_iterator > maximum_number) {
            maximum_number = *dataset_iterator;
        }
        dataset_iterator++;
    }
    float range = maximum_number - minimum_number;
    float interval_width = range / number_of_intervals;
    float first_value = minimum_number - interval_width * 0.5;
    number_of_occurrences_array_begin = new float[number_of_intervals + 2];
    float left_border_value = first_value;
    float right_border_value;
    for (int j = 0; j < number_of_intervals; j++) {
        number_of_occurrences_array_begin[j] = 0;
        right_border_value = first_value + interval_width * (j + 1);
        dataset_iterator = dataset_begin;
        for (int i = 0; i < len_of_dataset; i++) {
            if (*dataset_iterator < right_border_value and *dataset_iterator >= left_border_value) {
                number_of_occurrences_array_begin[j]++;
            }
            dataset_iterator++;
        }
        left_border_value = right_border_value;
    }
    number_of_occurrences_array_begin[number_of_intervals] = float(first_value);
    number_of_occurrences_array_begin[number_of_intervals + 1] = float(interval_width);
//    ni_begin = new float(ni_begin[0]);
    number_of_occurrences_array_end = new float(number_of_occurrences_array_begin[number_of_intervals + 1]);
    return number_of_intervals;
}

float *modeling_sample_based_on_sample(int sample_volume, float *dataset_begin, float *dataset_end) {


    float *number_of_occurrences_array_begin;
    float *number_of_occurrences_array_end;

    int number_of_intervals = get_density_array(dataset_begin, dataset_end, number_of_occurrences_array_begin, number_of_occurrences_array_end);
    number_of_occurrences_array_end = number_of_occurrences_array_begin + number_of_intervals + 1;
    float interval_width = *number_of_occurrences_array_end;
    float first_value = *(number_of_occurrences_array_end - 1);

    float *sample_based_on_sample = new float[sample_volume];

    float realisation_of_value;
    float cumulative_probability;
    float x = 0;
    float* array_iterator = NULL;
    for(int i=0;i<sample_volume;i++){
        realisation_of_value = get_random_from_0_to_1();
        cumulative_probability = 0;
        array_iterator = number_of_occurrences_array_begin;
        for(int j=0;j<number_of_intervals;j++){
            cumulative_probability += (*array_iterator*1.0) / sample_volume;
            if(realisation_of_value < cumulative_probability){
                x = (interval_width * realisation_of_value) + (j*interval_width + first_value);
                break;
            }
            array_iterator ++;
        }
        sample_based_on_sample[i] = x;
    }

    return sample_based_on_sample;
}

float modeling_random_mix_x(float nu_coef_1, float mu_coef_1, float lambda_coef_1, float nu_coef_2,
                            float mu_coef_2, float lambda_coef_2, float p) {
    float realisation_of_value = get_random_from_0_to_1();
    if (realisation_of_value <= p) {
        return modeling_random_x(nu_coef_2, mu_coef_2, lambda_coef_2);
    }
    return modeling_random_x(nu_coef_1, mu_coef_1, lambda_coef_1);
}
