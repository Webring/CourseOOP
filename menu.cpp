#include "menu.h"

#include "iostream"

using namespace std;

int select_menu_item(int max_items){
    int choice;
    do {
        cout << "��� ����� (����� ������ ����):" << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cin >> choice;

        if (choice <= 0 or choice > max_items) {
            cout << "������ ������ � ���� ���! ������� �������� ";
        }
    } while (choice <= 0 or choice > max_items);
    return choice;
}

int main_menu(){
    cout << "���� ��������:" << endl;
    cout << "1) ����� ���. ��������, ���������, ���������� �������� � ���������" << endl;
    cout << "2) ����� ���������" << endl;
    cout << "3) ��������� ������" << endl;

    return select_menu_item(3);
}

void params_show(const float *params_begin, const float *params_end){
    for ( auto it = params_begin; it != params_end; ++it )
    {
        cout << *it << std::endl;
    }
}

int generate_method_menu(){
    cout << "���� ���������:" << endl;
    cout << "1) ��������� �� �������" << endl;
    cout << "2) �����" << endl;
    cout << "3) ���� � ����������" << endl;
    return select_menu_item(3);
}