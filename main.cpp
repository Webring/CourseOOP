#include "iostream"
#include "menu.h"
#include "math.h"
#include "time.h"

#define GENERATE_PAGE_SHIFT 3
#define MAIN_MENU_PAGE 0

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    srand((unsigned)time(0));

    int next = 0;
    int coefs[7];
    int *dataset;

    while (next >= 0) {
        switch (next) {
            case MAIN_MENU_PAGE:
                next = main_menu();
                break;
            case 1:
                float values[4];
                params_show(begin(values), end(values));
                next = 0;
                break;
            case 2:
                cout << "kjkdj" << endl;
                next = 0;
                break;
            case 3:
                next = generate_method_menu() + GENERATE_PAGE_SHIFT;
                break;
            case 4:
                
                for (int i = 0; i< 100; i++){
                    cout << modeling_random_x(1, 0,0) << endl;
                }
                next = 0;
                break;
            case 5:
                next = 0;
                break;
            case 6:
                next = 0;
                break;
            default:
                cout << "Произошла ошибка! Возвращаемся в основное меню" << endl;
                next = 0;
        }
    }
    return 0;
}