#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

struct date {
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

struct event {
    string title;
    date date_;
};

class Calendar {
    event events[30];
    uint32_t count = 0;

    bool leap(uint16_t year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 4 != 0);
    }

    int dim(int m, int y) {
        if (m == 2) return 28 + leap(y);
        return (m == 4 || m == 6 || m == 9 || m == 11) ? 30 : 31;
    }

    long long dayNum(int d, int m, int y) {
        long long r = 0;
        for (int i = 1; i < y; ++i) r += 365 + leap(i);
        for (int i = 1; i < m; ++i) r += dim(i, y);
        return r + d;
    }

    void fromNum(long long n, int& d, int& m, int& y) {
        y = 1;
        while (n > (365 + leap(y))) n -= 365 + leap(y), ++y;
        m = 1;
        while (n > dim(m, y)) n -= dim(m, y), ++m;
        d = n;
    }

    bool valid(int d, int m, int y) {
        return y > 0 && y < 2027 && m > 0 && m < 13 && d > 0 && d <= dim(m, y);
    }

public:
    Events() = default;
    Events(const Events& o) : cnt(o.cnt) { for (int i = 0; i < cnt; ++i) e[i] = o.e[i]; }
    ~Events() = default;
    Events& operator=(const Events& o) {
        if (this != &o) { cnt = o.cnt; for (int i = 0; i < cnt; ++i) e[i] = o.e[i]; }
        return *this;
    }

    bool set(int d, int m, int y, string s) {
        if (!valid(d, m, y) || cnt == 30) return false;
        long long dd = dayNum(d, m, y);
        for (int i = 0; i < cnt; ++i) if (e[i].d == dd) return false;
        e[cnt++] = { dd, s };
        return true;
    }

    string get(int d, int m, int y) {
        long long dd = dayNum(d, m, y);
        for (int i = 0; i < cnt; ++i) if (e[i].d == dd) return e[i].n;
        return "";
    }

    bool diff(int d, int m, int y, int idx, int& q, int& mo, int& da) {
        if (idx < 0 || idx >= cnt) return false;
        long long df = dayNum(d, m, y) - e[idx].d;
        long long ad = (df > 0) ? df : -df;
        mo = ad / 30;
        da = ad % 30;
        q = mo / 3;
        mo %= 3;
        if (df < 0) { q = -q; mo = -mo; da = -da; }
        return true;
    }

    bool shift(int idx, int q, int mo, int da, string s) {
        if (idx < 0 || idx >= count || count == 30) return false;
        long long nd = events[idx].d + q * 90L + mo * 30L + da;
        if (nd < dayNum(1, 1, 1) || nd > dayNum(31, 12, 2026)) return false;
        for (int i = 0; i < count; ++i) if (events[i].d == nd) return false;
        e[cnt++] = { nd, s };
        return true;
    }

    friend ostream& operator<<(ostream& os, const Calendar& ev) {
        for (int i = 0; i < ev.cnt; ++i) {
            int d, m, y;
            fromNum(ev.e[i].d, d, m, y);
            os << d << '.' << m << '.' << y << ": " << ev.e[i].n << '\n';
        }
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Ru");
    Calendar cal;
    cal.set(1, 1, 2026, "Событие 1");
    cal.set(17, 3, 2026, "Событие 2");
    cout << cal;

    cout << "\nСобытие на 17.3.2026: " << cal.get(17, 3, 2026) << endl;

    int q, m, d;
    if (cal.diff(1, 1, 2026, 0, q, m, d))
        cout << "Разница между 1.1.2026 и Событие 1: " << q << " кв., " << m << " мес., " << d << " дн.\n";

    cal.shift(1, 0, -1, 5, "Сдвинутое событие");
    cout << "\nПосле сдвига:\n" << cal;

    cout << "\nНажмите Enter для выхода...";
    cin.get();
    return 0;
}