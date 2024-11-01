#include <limits>  // Для использования числовых пределов (например, для максимального значения int)
#include "menu.h"  // Заголовочный файл, который, видимо, содержит прототипы функций
#include "iostream" // Для работы с вводом/выводом
#include "GeneralDistribution/GeneralDistribution.h"
#include "MixDistribution/MixDistribution.h"

using namespace std; // Позволяет использовать стандартное пространство имен для упрощения синтаксиса

// Функция для проверки, является ли строка целым числом
bool is_int_number(const string& str) {
    // Если строка пуста, возвращаем false
    if (str.empty()) {
        return false;
    }

    size_t i = 0;

    // Проверяем, является ли первый символ знаком числа ('-' или '+')
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) {
            return false; // Строка не может состоять только из знака
        }
        i = 1; // Если знак есть, начинаем проверку с 1-го символа
    }

    // Проверяем, что все остальные символы строки - цифры
    for (; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false; // Если найден символ, не являющийся цифрой, возвращаем false
        }
    }

    return true; // Все символы - цифры, значит это целое число
}

// Функция для проверки, является ли строка числом с плавающей точкой
bool is_float_number(const string& str) {
    if (str.empty()) {
        return false; // Пустая строка не может быть числом
    }

    bool decimal_point_found = false; // Флаг для отслеживания наличия десятичной точки
    size_t i = 0;

    // Проверяем, является ли первый символ знаком числа ('-' или '+')
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) {
            return false; // Строка не может состоять только из знака
        }
        i = 1; // Начинаем проверку со второго символа
    }

    // Проходим по всем символам строки
    for (; i < str.length(); ++i) {
        if (str[i] == '.') {
            // Если точка уже была найдена, возвращаем false (число может содержать только одну точку)
            if (decimal_point_found) {
                return false;
            }
            decimal_point_found = true; // Устанавливаем флаг наличия десятичной точки
        } else if (!isdigit(str[i])) {
            return false; // Если найден не цифровой символ, возвращаем false
        }
    }

    return true; // Все символы корректны, это число с плавающей точкой
}

// Функция для ввода целого числа с проверкой на диапазон
int input_number(int from, int to) {
    string input; // Строка для хранения введенного значения
    int num;      // Переменная для хранения преобразованного числа

    // Если верхняя граница диапазона меньше нижней, устанавливаем максимальное значение для int
    if (to < from) {
        to = numeric_limits<int>::max();
    }

    // Цикл, который продолжает запрашивать ввод до тех пор, пока не будет введено корректное число
    do {
        cout << "Значение должно быть целым числом от " << from << " до " << to << ": " << endl;
        cin >> input; // Читаем строку

        // Проверяем, является ли введенная строка целым числом
        if (is_int_number(input)) {
            try {
                num = stoi(input); // Преобразуем строку в целое число

                // Проверяем, находится ли число в заданном диапазоне
                if (num < from || num > to) {
                    cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
                }
            } catch (out_of_range&) {
                // Обрабатываем случай, когда число слишком большое для типа int
                cout << "Ошибка: число слишком велико. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            }
        } else {
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
            num = from - 1; // Обеспечиваем продолжение цикла
        }

    } while (num < from || num > to); // Цикл продолжается, пока введенное число не в диапазоне

    return num; // Возвращаем корректное число
}

// Функция для ввода числа с плавающей точкой с проверкой на диапазон
float input_number(float from, float to) {
    string input; // Строка для хранения введенного значения
    float num;    // Переменная для хранения преобразованного числа

    // Если верхняя граница диапазона меньше нижней, устанавливаем максимальное значение для float
    if (to < from) {
        to = numeric_limits<float>::max();
    }

    // Цикл, который продолжает запрашивать ввод до тех пор, пока не будет введено корректное число
    do {
        cout << "Значение должно быть числом с плавающей точкой от " << from << " до " << to << ": " << endl;
        cin >> input; // Читаем строку

        // Проверяем, является ли введенная строка числом с плавающей точкой
        if (is_float_number(input)) {
            try {
                num = stof(input); // Преобразуем строку в число с плавающей точкой

                // Проверяем, находится ли число в заданном диапазоне
                if (num < from || num > to) {
                    cout << "Ошибка: число вне диапазона. Попробуйте снова." << endl;
                }
            } catch (out_of_range&) {
                // Обрабатываем случай, когда число слишком большое для типа float
                cout << "Ошибка: число слишком велико. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            } catch (invalid_argument&) {
                // Обрабатываем случай некорректного преобразования
                cout << "Ошибка: это не число. Попробуйте снова." << endl;
                num = from - 1; // Обеспечиваем продолжение цикла
            }
        } else {
            cout << "Ошибка: это не число. Попробуйте снова." << endl;
            num = from - 1; // Обеспечиваем продолжение цикла
        }

    } while (num < from || num > to); // Цикл продолжается, пока введенное число не в диапазоне

    return num; // Возвращаем корректное число
}

// Функция для выбора пункта меню
int select_menu_item(int max_items, bool add_back_button) {
    cout << "Выберите пункт меню:" << endl;
    return input_number(not add_back_button, max_items); // Используем input_number для выбора номера
}

// Главное меню программы
int main_menu() {
    cout << "Меню основное:" << endl;
    cout << "1) Основное распределение" << endl;
    cout << "2) Смесь распределений" << endl;
    cout << "3) Unit-test" << endl;
    cout << "0) Выход" << endl;

    return select_menu_item(3, true); // В меню 2 основных пункта и "назад" (выход)
}

// Меню операций с теоретической частью
int coefs_operations_menu() {
    cout << "Меню для работы с теоритической частью:" << endl;
    cout << "1) Найти мат. ожидание, дисперсия, коэффициенты эксцесса и асимметрии" << endl;
    cout << "2) Найти плотность" << endl;
    cout << "3) Сгенерировать данные" << endl;
    cout << "0) Назад" << endl;

    return select_menu_item(3, true); // В меню 3 основных пункта и "назад"
}

// Меню операций с данными (практическая часть)
int dataset_operations_menu(int datatype) {
    cout << "Меню для работы с практической частью:" << endl;
    cout << "1) Найти мат. ожидание, дисперсия, коэффициенты эксцесса и асимметрии" << endl;
    cout << "2) Найти плотность" << endl;
    cout << "3) Вывести выборку на экран" << endl;
    cout << "4) Записать выборку в файл" << endl;
    
    // Если тип данных не равен 2, добавляем пункт "Построить выборку по выборке"
    if (datatype != 2) {
        cout << "5) Построить выборку по выборке" << endl;
    }

    cout << "0) Назад" << endl;

    return select_menu_item(4 + (datatype != 2), true); // Количество пунктов зависит от типа данных
}

// Функция для отображения статистики (например, мат. ожидание и дисперсия)
void show_stats(const float *stats) {
    cout << "Мат. ожидание: " << *stats << endl;
    cout << "Дисперсия: " << *(stats + 1) << endl;
    cout << "Коэффициент асимметрии: " << *(stats + 2) << endl;
    cout << "Коэффициент эксцесса: " << *(stats + 3) << endl;
}

// Функция для ввода 3 параметров для распределения
void input_3_coefs(float *coefs) {
    for (int i = 3; i < 7; i++) {
        coefs[i] = 0; // Инициализируем параметры с индексом от 3 до 6 нулями
    }
    cout << "Введите значение nu (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);
    cout << "Введите значение mu (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda (параметр масштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
}
void input_3_coefs_class(GeneralDistribution &distribution,float *coefs){
    for (int i = 3; i < 7; i++) {
        coefs[i] = 0; // Инициализируем параметры с индексом от 3 до 6 нулями
    }
    cout << "Введите значение nu (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);

    cout << "Введите значение mu (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);

    cout << "Введите значение lambda (параметр масштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
    distribution.set_nu(coefs[0]);
    distribution.set_mu(coefs[1]);
    distribution.set_lambda(coefs[2]);
    distribution.save_to_file("persistent.txt");
}
// Функция для ввода 7 параметров для смеси распределений
void input_7_coefs(float *coefs) {
    cout << "Введите значение nu_1 (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_1 (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_1 (параметр масштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение nu_2 (параметр формы)" << endl;
    coefs[3] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_2 (сдвиг по x)" << endl;
    coefs[4] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_2 (параметр масштаба)" << endl;
    coefs[5] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение p (Вероятность)" << endl;
    coefs[6] = input_number(0.f, 1.f);
}
void input_7_coefs_class(MixDistribution *&mix_distribution,float *coefs) {
    cout << "Введите значение nu_1 (параметр формы)" << endl;
    coefs[0] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_1 (сдвиг по x)" << endl;
    coefs[1] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_1 (параметр масштаба)" << endl;
    coefs[2] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение nu_2 (параметр формы)" << endl;
    coefs[3] = input_number(0.f, 100000.f);
    cout << "Введите значение mu_2 (сдвиг по x)" << endl;
    coefs[4] = input_number(-100000.f, 100000.f);
    cout << "Введите значение lambda_2 (параметр масштаба)" << endl;
    coefs[5] = input_number(0.0000001f, 100000.f);
    cout << "Введите значение p (Вероятность)" << endl;
    coefs[6] = input_number(0.f, 1.f);
    mix_distribution = new MixDistribution(coefs[0],coefs[1],coefs[2],coefs[3],coefs[4],coefs[5],coefs[6]);
    mix_distribution->save_to_file("persistent_mix.txt");
}
