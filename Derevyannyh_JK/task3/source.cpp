#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Menu {
private:
    string nazv[20];
    int kol;
    int last;

public:
    Menu() {
        kol = 0;
        last = 0;
    }

    void setKol(int n) {
        if (n >= 1 && n <= 20) {
            kol = n;
        }
    }

    int getKol() {
        return kol;
    }

    void setNazv(int num, string txt) {
        if (num >= 0 && num <= kol) {
            nazv[num - 1] = txt;
        }
    }

    void show(int x, int y) {
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        cout << "---меню---\n";
        for (int i = 0; i < kol; i++) {          
            cout << i + 1 << " - " << nazv[i] << "\n";  
        }
        cout << "-----------\n";
    }

    int choose() {
        int ch;
        cout << "выберите: ";
        cin >> ch;

        while (ch < 1 || ch > kol) {   
            cout << "ошибка! выберите снова: ";
            cin >> ch;
        }

        last = ch;
        return ch;
    }

    int getLast() {
        return last;
    }
};

int main() {
    setlocale(0, "");

    Menu m;

    m.setKol(5);

    m.setNazv(1, "сложение");
    m.setNazv(2, "вычитание");
    m.setNazv(3, "умножение");
    m.setNazv(4, "деление");
    m.setNazv(5, "выход");

    int vib;
    double a, b;

    do {
        system("cls");

        m.show(0, 0);
        vib = m.choose();

        if (vib == 5) {
            cout << "\nДо свидания!\n";
            break;
        }

        cout << "\nВведите a: ";
        cin >> a;
        cout << "Введите b: ";
        cin >> b;

        cout << "\n";

        if (vib == 1) {
            cout << a << " + " << b << " = " << a + b << "\n";
        }
        if (vib == 2) {
            cout << a << " - " << b << " = " << a - b << "\n";
        }
        if (vib == 3) {
            cout << a << " * " << b << " = " << a * b << "\n";
        }
        if (vib == 4) {
            if (b != 0) {
                cout << a << " / " << b << " = " << a / b << "\n";
            }
            else {
                cout << "Ошибка! Деление на ноль!\n";
            }
        }

        cout << "\nНажмите Enter...";
        cin.ignore();
        cin.get();

    } while (true);

    return 0;
}