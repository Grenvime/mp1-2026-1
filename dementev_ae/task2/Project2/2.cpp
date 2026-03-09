#include <iostream>
#include <cmath>
#include <limits>
#include <locale.h>
using namespace std;

class Polynomial {
private:
    static const int mdegree = 12;
    int degree;
    double coeff[mdegree + 1];

public:
    Polynomial() {
        degree = 0;
        for (int i = 0; i <= mdegree; i++) {
            coeff[i] = 0;
        }
    }

    Polynomial(int deg) {
        if (deg < 0 || deg > mdegree) {
            cout << "Ошибка: степень должна быть от 0 до 12. Установлена степень 0.\n";
            deg = 0;
        }
        degree = deg;
        for (int i = 0; i <= mdegree; i++) {
            coeff[i] = 0;
        }
    }

    Polynomial(const Polynomial& other) {
        degree = other.degree;
        for (int i = 0; i <= mdegree; i++) {
            coeff[i] = other.coeff[i];
        }
    }

    void meny1(int deg) {
        if (deg >= 0 && deg <= mdegree) {
            degree = deg;
            cout << "Степень установлена. Теперь введите коэффициенты.\n";
            for (int i = 0; i <= degree; i++) {
                cout << "Коэффициент при x^" << i << ": ";
                cin >> coeff[i];
            }
            for (int i = degree + 1; i <= mdegree; i++) {
                coeff[i] = 0;
            }
        }
        else {
            cout << "Ошибка: степень должна быть от 0 до 12\n";
        }
    }

    void meny2() {
        cout << "Введите коэффициенты для степени " << degree << ":\n";
        for (int i = 0; i <= degree; i++) {
            cout << "Коэффициент при x^" << i << ": ";
            cin >> coeff[i];
        }
    }

    int meny3() {
        return degree;
    }

    void meny4() {
        int n;
        cout << "Введите номер коэффициента (0-" << mdegree << "): ";
        cin >> n;

        if (n >= 0 && n <= mdegree) {
            if (n <= degree) {
                cout << "Коэффициент при x^" << n << " = " << coeff[n] << endl;
            }
            else {
                cout << "Коэффициент при x^" << n << " = 0 (степень полинома " << degree << ")\n";
            }
        }
        else {
            cout << "Ошибка: неверный номер коэффициента\n";
        }
    }

    void meny5() {
        double x;
        cout << "Введите значение x: ";
        cin >> x;

        double result = 0;
        double power = 1;

        for (int i = 0; i <= degree; i++) {
            result += coeff[i] * power;
            power *= x;
        }

        cout << "P(" << x << ") = " << result << endl;
    }

    Polynomial meny6() {
        Polynomial result;

        if (degree > 0) {
            result.degree = degree - 1;
            for (int i = 1; i <= degree; i++) {
                result.coeff[i - 1] = coeff[i] * i;
            }
        }

        return result;
    }

    void print() {
        cout << "Полином: ";
        bool first = true;
        for (int i = degree; i >= 0; i--) {
            if (coeff[i] != 0) {
                if (!first && coeff[i] > 0) {
                    cout << "+";
                }
                if (i == 0) {
                    cout << coeff[i];
                }
                else if (i == 1) {
                    cout << coeff[i] << "x";
                }
                else {
                    cout << coeff[i] << "x^" << i;
                }
                first = false;
            }
        }
        if (first) {
            cout << "0";
        }
        cout << endl;
    }
};

void menu() {
    cout << "1. Задать степень многочлена\n";
    cout << "2. Задать коэффициенты мономов\n";
    cout << "3. Узнать степень многочлена\n";
    cout << "4. Узнать значение коэффициента по номеру\n";
    cout << "5. Вычислить значение многочлена в точке x\n";
    cout << "6. Найти производную многочлена\n";
    cout << "7. Показать текущий полином\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Polynomial poly;
    int choice;
    bool running = true;

    while (running) {
        menu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << endl;
            int deg;
            cout << "Введите степень многочлена (0-12): ";
            cin >> deg;
            poly.meny1(deg);
            cout << endl;
            break;
        }

        case 2: {
            cout << endl;
            poly.meny2();
            cout << endl;
            break;
        }

        case 3: {
            cout << endl;
            cout << "Степень многочлена: " << poly.meny3() << endl;
            cout << endl;
            break;
        }

        case 4: {
            cout << endl;
            poly.meny4();
            cout << endl;
            break;
        }

        case 5: {
            cout << endl;
            poly.meny5();
            cout << endl;
            break;
        }

        case 6: {
            cout << endl;
            Polynomial deriv = poly.meny6();
            cout << "Производная: ";
            deriv.print();
            cout << endl;
            break;
        }

        case 7: {
            cout << endl;
            poly.print();
            cout << endl;
            break;
        }

        case 0: {
            running = false;
            break;
        }
        }
    }
    return 0;
}