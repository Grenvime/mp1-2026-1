#include <iostream>
#include <cmath>
#include <locale.h>

using namespace std;

typedef double (*Function)(double);

class IntegralCalculator {
private:
    Function func;
    double lowerLimit;
    double upperLimit;
    int segments;
    int method;

public:
    IntegralCalculator() {
        func = nullptr;
        lowerLimit = 0;
        upperLimit = 1;
        segments = 100;
        method = 1;
    }

    ~IntegralCalculator() {
    }

    void setFunction(Function f) {
        func = f;
    }

    void setLimits(double lower, double upper) {
        lowerLimit = lower;
        upperLimit = upper;
    }

    void getLimits(double& lower, double& upper) {
        lower = lowerLimit;
        upper = upperLimit;
    }

    void setSegments(int n) {
        if (n > 0) {
            segments = n;
        }
    }

    void setMethod(int m) {
        if (m >= 1 && m <= 3) {
            method = m;
        }
    }

    double calculate() {
        double h = (upperLimit - lowerLimit) / segments;
        double sum = 0;
        double x;

        if (method == 1) {
            for (int i = 0; i < segments; i++) {
                x = lowerLimit + i * h;
                sum = sum + func(x);
            }
        }
        else if (method == 2) {
            for (int i = 1; i <= segments; i++) {
                x = lowerLimit + i * h;
                sum = sum + func(x);
            }
        }
        else if (method == 3) {
            for (int i = 0; i < segments; i++) {
                x = lowerLimit + (i + 0.5) * h;
                sum = sum + func(x);
            }
        }

        return sum * h;
    }

    void printResult() {
        double integral = calculate();
        cout << "Интеграл = " << integral << endl;
        cout << "Отрезков: " << segments << endl;

        if (method == 1) {
            cout << "Метод: левые" << endl;
        }
        else if (method == 2) {
            cout << "Метод: правые" << endl;
        }
        else if (method == 3) {
            cout << "Метод: средние" << endl;
        }
    }
};

double f1(double x) {
    return x * x;
}

double f2(double x) {
    return sin(x);
}

int main() {
    IntegralCalculator calc;
    double a, b;
    setlocale(LC_ALL, "Russian");

    calc.setFunction(f1);
    calc.setLimits(0, 2);
    calc.setSegments(1000);

    calc.getLimits(a, b);
    cout << "Пределы: " << a << " " << b << endl;

    calc.setMethod(1);
    calc.printResult();

    calc.setMethod(2);
    calc.printResult();

    calc.setMethod(3);
    calc.printResult();

    cout << endl;

    calc.setFunction(f2);
    calc.setLimits(0, 3.14);
    calc.setSegments(1000);
    calc.setMethod(3);
    calc.printResult();

    return 0;
}