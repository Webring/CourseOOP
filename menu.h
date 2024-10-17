#ifndef OOP_MENU_H
#define OOP_MENU_H


#include "iostream"
#include "GeneralDistribution/GeneralDistribution.h"

using namespace std;

float input_number(float from, float to);
int input_number(int from, int to);

int main_menu();
int coefs_operations_menu();
int dataset_operations_menu(int datatype);

void show_stats(const float *stats);

void input_3_coefs(float *coefs);
void input_3_coefs_class(GeneralDistribution distribution,float *coefs);
void input_7_coefs(float *coefs);

#endif //OOP_MENU_H
