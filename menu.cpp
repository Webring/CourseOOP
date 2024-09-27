#include <limits>
#include "menu.h"

#include "iostream"

using namespace std;

bool is_int_number(const string& str) {
    // Проверяем, что строка не пуста и все символы в строке - цифры (или знак)
    if (str.empty()) {
        return false;
    }

    size_t i = 0;

    // Проверяем первый символ, если это знак числа
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) {
            return false; // строка не может состоять только из знака
        }
        i = 1; // Начинаем проверять цифры со второго символа
    }

    // Проверяем, что оставшиеся символы - цифры
    for (; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

bool is_float_number(const string& str) {
    if (str.empty()) {
        return false;
    }

    bool decimal_point_found = false;
    size_t i = 0;

    // Проверяем первый символ, если это знак числа
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) {
            return false; // строка не может состоять только из знака
        }
        i = 1; // Начинаем проверять цифры и точку со второго символа
    }

    // Проходим по остальным символам строки
    for (; i < str.length(); ++i) {
        if (str[i] == '.') {
            // Если точка уже встречалась, возвращаем false
            if (decimal_point_found) {
                return false;
            }
            decimal_point_found = true;
        } else if (!isdigit(str[i])) {
            return false; // Если символ не цифра и не точка, возвращаем false
        }
    }

    return true;
}

int input_number(int from, int to) {
    string input;
    int num;

    // Если to < from, устанавливаем верхний предел в максимально возможное значение для int
    if (to < from) {
        to = numeric_limits<int>::max();
    }

    do {
        cout << "Значение должно быть целым числом от " << from << " до " << to << ": " << endl;
        cin >> input;

        if (is_int_number(input)) {
            try {
                num = stoi(input); // Преобразуем строку в число

                if (num < from || num > to) {
                    cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
                }
            } catch (out_of_range&) {
                cout << "Ошибка: число слишком велико. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            }
        } else {
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
            num = from - 1; // Обеспечиваем продолжение цикла
        }

    } while (num < from || num > to);

    return num;
}

float input_number(float from, float to) {
    string input;
    float num;

    // Если to < from, устанавливаем верхний предел в максимально возможное значение для float
    if (to < from) {
        to = numeric_limits<float>::max();
    }

    do {
        cout << "Значение должно быть числом с плавающей точкой от " << from << " до " << to << ": " << endl;
        cin >> input;

        if (is_float_number(input)) {
            try {
                num = stof(input); // Преобразуем строку в float

                if (num < from || num > to) {
                    cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
                }
            } catch (out_of_range&) {
                cout << "Ошибка: число слишком велико. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            }catch (invalid_argument&) {
                cout << "Ошибка: это не число. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            }
        } else {
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
            num = from - 1; // Обеспечиваем продолжение цикла
        }

    } while (num < from || num > to);

    return num;
}
int select_menu_item(int max_items, bool add_back_button){
    cout << "Выберете пункт меню:" << endl;
    return input_number(not add_back_button, max_items);
}

int main_menu(){
    cout << "Меню основное:" << endl;
    cout << "1) Основное распределение" << endl;
    cout << "2) Смесь распределений" << endl;
    cout << "0) Выход" << endl;

    return select_menu_item(2, true);
}

int coefs_operations_menu(){
    cout << "Меню для работы с теоритической частью:" << endl;
    cout << "1) Найти мат. ожидание, дисперсия, коэфиценты эксцесса и асимметрии" << endl;
    cout << "2) Найти плотность" << endl;
    cout << "3) Сгенерировать данные" << endl;
    cout << "0) Назад" << endl;

    return select_menu_item(3, true);
}

int dataset_operations_menu(int datatype){
    cout << "Меню для работы с практической частью:" << endl;
    cout << "1) Найти мат. ожидание, дисперсия, коэфиценты эксцесса и асимметрии" << endl;
    cout << "2) Найти плотность" << endl;
    cout << "3) Вывести выборку на экран" << endl;
    cout << "4) Записать выборку в файл" << endl;
    if (datatype != 2) {
        cout << "5) Построить выборку по выборке" << endl;
    }

    cout << "0) Назад" << endl;

    return select_menu_item(4 + (datatype != 2), true);
}

void show_stats(const float *stats){
    cout << "Мат. ожидание: " << *stats << endl;
    cout << "Дисперсия: " << *(stats + 1) << endl;
    cout << "Коэфицент асимметрии: " << *(stats + 2) << endl;
    cout << "Коэфицент эксцесса: " << *(stats + 3) << endl;
}

void input_4_coefs(float *coefs) {
    for (int i = 3; i < 7; i++) {
        coefs[i] = 0;
    }
    cout << "Введите значение nu (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);
    cout << "Введите значение mu (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda (параметр маштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
}
void input_7_coefs(float *coefs) {
    cout << "Введите значение nu_1 (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_1 (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_1 (параметр маштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение nu_2 (параметр формы)" << endl;
    coefs[3] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_2 (сдвиг по x)" << endl;
    coefs[4] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_2 (парметр маштаба)" << endl;
    coefs[5] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение p (Вероятность)" << endl;
    coefs[6] = input_number(0.f, 1.f);
}
