#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    int a[20];
    int n;
public:
    Vector() { n = 1; a[0] = 0; }

    Vector(int m) {
        if (m < 1) m = 1;
        if (m > 20) m = 20;
        n = m;
        for (int i = 0; i < n; i++) a[i] = 0;
    }

    Vector(const Vector& v) {
        n = v.n;
        for (int i = 0; i < n; i++) {
            a[i] = v.a[i];
        }
    }

    ~Vector() {}

    void setN(int m) {
        if (m >= 1 && m <= 20)
            n = m;
    }

    int getN() {
        return n;
    }

    void set(int i, int x) {
        if (i >= 0 && i < n) {
            a[i] = x;
        }
    }

    int get(int i) {
        if (i >= 0 && i < n) {
            return a[i];
        }
        return 0;
    }

    double len() {
        double s = 0;
        for (int i = 0; i < n; i++) s += a[i] * a[i];
        return sqrt(s);
    }

    int scal(Vector v) {
        int s = 0;
        if (n != v.n) {
            return 0;
        }
        for (int i = 0; i < n; i++)
            s += a[i] * v.a[i];
        return s;
    }

    Vector sum(Vector v) {
        Vector res(n);
        if (n != v.n) {
            return res;
        }
        for (int i = 0; i < n; i++)
            res.a[i] = a[i] + v.a[i];
        return res;
    }

    void print() {
        cout << "(";
        for (int i = 0; i < n; i++) {
            cout << a[i];
            if (i < n - 1) cout << " ";
        }
        cout << ")\n";
    }
};

int main() {
    setlocale(0, "");
    Vector v1, v2;
    int m, x, i, k;

    cout << "размер 1: ";
    cin >> m;
    v1.setN(m);
    cout << "¬ведите значени€:\n";  
    for (i = 0; i < m; i++) {
        cin >> x;
        v1.set(i, x);
    }

    cout << "размер 2: ";
    cin >> m;
    v2.setN(m);
    cout << "¬ведите значени€:\n"; 
    for (i = 0; i < m; i++) {
        cin >> x;
        v2.set(i, x);
    }

    do {
        cout << "\n 1-показать\n 2-размер\n 3-изменить\n 4-длина\n 5-скал€р\n 6-сумма\n 7-элемент\n 0-выход:\n ";
        cin >> k;

        if (k == 1) {
            v1.print();
            v2.print();
        }

        if (k == 2)
            cout << v1.getN() << " " << v2.getN() << "\n";

        if (k == 3) {
            cout << "вектор(1/2) номер значение: ";
            cin >> i >> m >> x;
            if (i == 1)
                v1.set(m, x);
            else
                v2.set(m, x);
        }

        if (k == 4) {
            cout << "вектор(1/2): ";
            cin >> i;
            if (i == 1)
                cout << v1.len() << "\n";
            else
                cout << v2.len() << "\n";
        }

        if (k == 5)
            cout << v1.scal(v2) << "\n";

        if (k == 6) {
            v1.sum(v2).print();
        }

        if (k == 7) {
            cout << "вектор(1/2) номер: ";
            cin >> i >> m;
            if (i == 1)
                cout << v1.get(m - 1) << "\n";
            else
                cout << v2.get(m - 1) << "\n";
        }

    } while (k != 0);

    return 0;
}




