#include "menu.h"

#include "iostream"

using namespace std;

int select_sample_menu(bool add_mixed_sample) {

    cout << "�������� �������:" << endl;
    cout << "1) �������� ������� �1" << endl;
    cout << "2) �������� ������� �2" << endl;
    if (add_mixed_sample) {
        cout << "3) ��������� �������" << endl;
    }

    int choice;
    do {
        cout << "��� ����� (����� ������ ����):" << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cin >> choice;

        if (choice <= 0 or choice > 2 + add_mixed_sample) {
            cout << "������ ������ � ���� ���! ������� �������� ";
        }
    } while (choice <= 0 or choice > 2 + add_mixed_sample);
    cout << endl;
    return choice;
}