#include <iostream>
#include <cstdlib>
using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

class Rational {
private:
    int num;   
    int den;   

    void reduce() {
        if (den == 0) {
            cout << "Îøèáêà" << endl;
            exit(1);
        }
        if (den < 0) {
            num = -num;
            den = -den;
        }
        int d = gcd(num, den);
        num /= d;
        den /= d;
    }
public:
    Rational() {
        num = 0;
        den = 1;
    }
    Rational(int n) {
        num = n;
        den = 1;
    }
    Rational(int n, int d) {
        num = n;
        den = d;
        reduce();
    }
    Rational(const Rational& r) {
        num = r.num;
        den = r.den;
    }
    Rational operator+(const Rational& r) const {
        int new_num = num * r.den + r.num * den;
        int new_den = den * r.den;
        return Rational(new_num, new_den);
    }
    Rational operator-(const Rational& r) const {
        int new_num = num * r.den - r.num * den;
        int new_den = den * r.den;
        return Rational(new_num, new_den);
    }
    Rational operator*(const Rational& r) const {
        int new_num = num * r.num;
        int new_den = den * r.den;
        return Rational(new_num, new_den);
    }
    Rational operator/(const Rational& r) const {
        if (r.num == 0) {
            cout << "Îøèáêà" << endl;
            exit(1);
        }
        int new_num = num * r.den;
        int new_den = den * r.num;
        return Rational(new_num, new_den);
    }
    void print() const {
        if (den == 1)
            cout << num;
        else
            cout << num << "/" << den;
    }
};

int main() {
    Rational a(1, 2);
    Rational b(2, 3);
    Rational c(4);
    Rational d;

    cout << "a = "; a.print(); cout << endl;
    cout << "b = "; b.print(); cout << endl;
    cout << "c = "; c.print(); cout << endl;
    cout << "d = "; d.print(); cout << endl;

    Rational oper1 = a + b;
    cout << "a + b = "; oper1.print(); cout << endl;
    Rational oper2 = a - b;
    cout << "a - b = "; oper2.print(); cout << endl;
    Rational oper3 = a * b;
    cout << "a * b = "; oper3.print(); cout << endl;
    Rational oper4 = a / b;
    cout << "a / b = "; oper4.print(); cout << endl;
    return 0;
}