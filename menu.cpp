#include "menu.h"

#include "iostream"

using namespace std;

int select_sample_menu(bool add_mixed_sample) {

    cout << "Выберете выборку:" << endl;
    cout << "1) Основная выборка №1" << endl;
    cout << "2) Основная выборка №2" << endl;
    if (add_mixed_sample) {
        cout << "3) Смешенная выборка" << endl;
    }

    int choice;
    do {
        cout << "Ваш выбор (номер пункта меню):" << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cin >> choice;

        if (choice <= 0 or choice > 2 + add_mixed_sample) {
            cout << "Такого пункта в меню нет! Поэтому измените ";
        }
    } while (choice <= 0 or choice > 2 + add_mixed_sample);
    cout << endl;
    return choice;
}