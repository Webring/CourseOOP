#include "menu.h"

#include "iostream"

using namespace std;

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

    return select_menu_item(3);
}

void params_show(const float *params_begin, const float *params_end){
    for ( auto it = params_begin; it != params_end; ++it )
    {
        cout << *it << std::endl;
    }
}

int generate_method_menu(){
    cout << "Меню генерации:" << endl;
    cout << "1) Генерация по функции" << endl;
    cout << "2) Смесь" << endl;
    cout << "3) Ввод с клавиатуры" << endl;
    return select_menu_item(3);
}