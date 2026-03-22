#include <iostream>
using namespace std;

class LongNumber {
    unsigned int low;
    int high;

public:
    LongNumber(long long val = 0) {
        low = val;
        high = val >> 32;
    }

    long long toLL() const {
        return ((long long)high << 32) | low;
    }

    // Методы для ввода/вывода (заменяют friend-функции)
    void print(ostream& os) const {
        os << toLL();
    }

    void read(istream& is) {
        long long val;
        is >> val;
        *this = LongNumber(val);
    }

    LongNumber operator+(const LongNumber& other) const {
        return LongNumber(toLL() + other.toLL());
    }
    LongNumber operator-(const LongNumber& other) const {
        return LongNumber(toLL() - other.toLL());
    }
    LongNumber operator*(const LongNumber& other) const {
        return LongNumber(toLL() * other.toLL());
    }
    LongNumber operator/(const LongNumber& other) const {
        return LongNumber(toLL() / other.toLL());
    }
    LongNumber operator%(const LongNumber& other) const {
        return LongNumber(toLL() % other.toLL());
    }
};

ostream& operator<<(ostream& os, const LongNumber& num) {
    num.print(os);
    return os;
}

istream& operator>>(istream& is, LongNumber& num) {
    num.read(is);
    return is;
}

int main() {
    setlocale(LC_ALL, "Russian");
    LongNumber a, b;
    int choice;

    cout << "=== КАЛЬКУЛЯТОР ДЛИННЫХ ЧИСЕЛ ===\n";
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;

    do {
        cout << "\nМеню:\n";
        cout << "1 - Сумма\n";
        cout << "2 - Разность\n";
        cout << "3 - Произведение\n";
        cout << "4 - Частное\n";
        cout << "5 - Остаток от деления\n";
        cout << "0 - Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Результат: " << a << " + " << b << " = " << a + b << endl;
            break;
        case 2:
            cout << "Результат: " << a << " - " << b << " = " << a - b << endl;
            break;
        case 3:
            cout << "Результат: " << a << " * " << b << " = " << a * b << endl;
            break;
        case 4:
            if (b.toLL() != 0)
                cout << "Результат: " << a << " / " << b << " = " << a / b << endl;
            else
                cout << "Ошибка: деление на ноль!\n";
            break;
        case 5:
            if (b.toLL() != 0)
                cout << "Результат: " << a << " % " << b << " = " << a % b << endl;
            else
                cout << "Ошибка: деление на ноль!\n";
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}