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
        cout << "�������� ������ ���� ����� ������ �� " << from << " �� " << to << ": " << endl;
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // �������� ������ �����
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �������� �����
            cout << "������: ��� �� �����. ���������� �����." << endl;
        } else if (num < from || num > to) {
            cout << "������: ����� ��� ���������. ���������� �����." << endl;
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
        cout << "�������� ������ ���� ������� ������ �� " << from << " �� " << to << ": " << endl;
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // �������� ������ �����
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �������� �����
            cout << "������: ��� �� �����. ���������� �����." << endl;
        } else if (num < from || num > to) {
            cout << "������: ����� ��� ���������. ���������� �����." << endl;
        }
    } while (num < from || num > to);
    return num;
}

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
    cout << "4) ������� ������" << endl;

    return select_menu_item(4);
}

void params_show(const float *params_begin, const float *params_end){
    cout << "���. ��������: " << *params_begin << endl;
    cout << "��������� " << *(params_begin + 1) << endl;
    cout << "��������� ����������: " << *(params_begin + 2) << endl;
    cout << "��������� ��������: " << *(params_begin + 3) << endl;
}

int generate_method_menu(){
    cout << "���� ���������:" << endl;
    cout << "1) ��������� �� �������" << endl;
    cout << "2) �����" << endl;
    cout << "3) ���� � ����������" << endl;
    return select_menu_item(3);
}