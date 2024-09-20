#include <limits>
#include "menu.h"

#include "iostream"

using namespace std;

int input_number(int from, int to) {
    int num;
    if (to < from){
        to = numeric_limits<int>::max();
    }
    do {
        cout << "Значение должно быть целым числом от " << from << " до " << to << ": " << endl;
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // Сбросить ошибку ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистить буфер
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
        } else if (num < from || num > to) {
            cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
        }
    } while (num < from || num > to);
    return num;
}

float input_number(float from, float to) {
    float num;
    if (to < from){
        to = numeric_limits<float>::max();
    }
    do {
        cout << "Значение должно быть дробным числом от " << from << " до " << to << ": " << endl;
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // Сбросить ошибку ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистить буфер
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
        } else if (num < from || num > to) {
            cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
        }
    } while (num < from || num > to);
    return num;
}

int select_menu_item(int max_items){
    int choice;
    do {
        cout << "Ваш выбор (номер пункта меню):" << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cin >> choice;

        if (choice <= 0 or choice > max_items) {
            cout << "Такого пункта в меню нет! Поэтому измените ";
        }
    } while (choice <= 0 or choice > max_items);
    return choice;
}

int main_menu(){
    cout << "Меню основное:" << endl;
    cout << "1) найти мат. ожидание, дисперсия, коэфиценты эксцесса и асиметрии" << endl;
    cout << "2) Найти плотность" << endl;
    cout << "3) Генерация данных" << endl;
    cout << "4) Вывести данные" << endl;
    cout << "5) " << endl;

    return select_menu_item(5);
}

void params_show(const float *params_begin, const float *params_end){
    cout << "Мат. ожидание: " << *params_begin << endl;
    cout << "Дисперсия " << *(params_begin + 1) << endl;
    cout << "Коэфицент ассиметрии: " << *(params_begin + 2) << endl;
    cout << "Коэфицент эксцесса: " << *(params_begin + 3) << endl;
}

int generate_method_menu(){
    cout << "Меню генерации:" << endl;
    cout << "1) Генерация по функции" << endl;
    cout << "2) Смесь" << endl;
    cout << "3) Ввод с клавиатуры" << endl;
    return select_menu_item(3);
}