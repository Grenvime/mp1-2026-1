#include<iostream>
#include<locale.h>
#include<functional>
#include<array>
#include<cmath>
#include<vector>
#include <iomanip>
#include<fstream>
std::ofstream out;
class tabulator {
    std::function<double(double)> currentFunction;
    int kol_toch = 0;
    double start = 0;
    double end = 0;
    std::vector<double> vec_y;
    std::vector<double> vec_x;

public:
    ~tabulator() {}
    void set_func(std::function<double(double)> func) {
        currentFunction = func;
    }
    void tochki(int n) {
        kol_toch = n;
    }
    int vern_tochki() {
        return kol_toch;
    }
    void set_promezutok(double a, double b) {
        start = a;
        end = b;
    }
    std::array<double, 2> vern_promezutok() {
        return { start, end };
    }
    void tabulir() {
        if (!currentFunction) {
            std::cout << "Ошибка: функция не задана\n";
            return;
        }
        if (kol_toch <= 0) {
            std::cout << "Ошибка: не задано количество точек\n";
            return;
        }
        if (start >= end) {
            std::cout << "Ошибка: не задан отрезок\n";
            return;
        }
        vec_x.clear();
        vec_y.clear();
        double step = (end - start) / (kol_toch - 1);
        for (int i = 0; i < kol_toch; i++) {
            double x = start + i * step;
            double y = currentFunction(x);

            vec_x.push_back(x);
            vec_y.push_back(y);
        }

        std::cout << "Табулирование выполнено\n";
    }

    std::array<std::vector<double>, 2> return_res() {
        std::array<std::vector<double>, 2> res = { vec_x, vec_y };
        return res;
    }
    void save() {
        std::ofstream file("Результаты.txt");
        file << "Результаты табулирования\n";
        file << "x\t\ty\n";
        file << "--------------------\n";
        for (size_t i = 0; i < vec_x.size(); i++) {
            file << vec_x[i] << "\t\t" << vec_y[i] << "\n";
        }
        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    int nomer = -1;
    tabulator t;

    while (nomer != 0) {
        std::cout << "\nВведите команду\n"
            << "1 - Задать функцию\n"
            << "2 - Задать число точек табулирования\n"
            << "3 - Получить текущее число точек\n"
            << "4 - Задать отрезок табулирования\n"
            << "5 - Получить отрезок табулирования\n"
            << "6 - Выполнить табулирование функции\n"
            << "7 - Выдать результаты табулирования\n"
            << "8 - Сохранить результаты в файл\n"
            << "0 - Выйти\n";
        std::cin >> nomer;

        if (nomer == 1) {
            std::cout << "Выберите функцию:\n";
            std::cout << "1 - sin(x)\n";
            std::cout << "2 - cos(x)\n";
            std::cout << "3 - x^2\n";
            std::cout << "4 - x^3\n";
            std::cout << "5 - e^x\n";
            std::cout << "7 - ln(x)\n";
            std::cout << "8 - tg(x)\n";
            std::cout << "9 - sqrt(x)\n";
            int a;
            std::cin >> a;
            switch (a) {
            case 1:
                t.set_func([](double x) { return sin(x); });
                std::cout << "Функция sin(x) задана\n";
                break;
            case 2:
                t.set_func([](double x) { return cos(x); });
                std::cout << "Функция cos(x) задана\n";
                break;
            case 3:
                t.set_func([](double x) { return x * x; });
                std::cout << "Функция x^2 задана\n";
                break;
            case 4:
                t.set_func([](double x) { return x * x * x; });
                std::cout << "Функция x^3 задана\n";
                break;
            case 5:
                t.set_func([](double x) { return exp(x); });
                std::cout << "Функция e^x задана\n";
                break;
            case 7:
                t.set_func([](double x) { return log(x); });
                std::cout << "Функция ln(x) задана (x > 0)\n";
                break;
            case 8:
                t.set_func([](double x) { return tan(x); });
                std::cout << "Функция tg(x) задана\n";
                break;
            case 9:
                t.set_func([](double x) { return sqrt(x); });
                std::cout << "Функция sqrt(x) задана (x >= 0)\n";
                break;
            }
        }
        else if (nomer == 2) {
            int n;
            std::cout << "Введите количество точек: ";
            std::cin >> n;
            t.tochki(n);
            std::cout << "Установлено " << n << " точек\n";
        }
        else if (nomer == 3) {
            std::cout << "Точек табулирования: " << t.vern_tochki() << "\n";
        }
        else if (nomer == 4) {
            double a, b;
            while (true) {
                std::cout << "Введите начало отрезка: ";
                std::cin >> a;
                std::cout << "Введите конец отрезка: ";
                std::cin >> b;

                if (a >= b) {
                    std::cout << "Ошибка: начало должно быть меньше конца\n";
                }
                else {
                    t.set_promezutok(a, b);
                    std::cout << "Отрезок [" << a << ", " << b << "] установлен\n";
                    break;
                }
            }
        }
        else if (nomer == 5) {
            auto promez = t.vern_promezutok();
            std::cout << "Отрезок: [" << promez[0] << ", " << promez[1] << "]\n";
        }
        else if (nomer == 6) {
            t.tabulir();
        }
        else if (nomer == 7) {
            auto res = t.return_res();

            if (res[0].size() == 0) {
                std::cout << "Нет результатов, cначала выполните табулирование\n";
            }
            else {
                std::cout << "\nРезультаты табулирования:\n";
                std::cout << "          x\t\ty\n";
                std::cout << "--------------------------------\n";
                std::cout << std::fixed << std::setprecision(4);
                for (int i = 0; i < res[0].size(); i++) {
                    std::cout<< std::setw(14) << res[0][i]
                         << "  " << std::setw(14) << res[1][i] << "\n";
                }
            }
        }
        else if (nomer == 8) {
            t.save();
            std::cout << "\nСохранено в файле\n";
            
        }
    }

    system("pause");
    return 0;
}