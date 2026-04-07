#include <iostream>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

struct Date {
    int d, m, y;
    Date(int d = 1, int m = 1, int y = 2026) :d(d), m(m), y(y) {}
    bool operator<(const Date& o)const {
        if (y != o.y)return y < o.y;
        if (m != o.m)return m < o.m;
        return d < o.d;
    }
};

struct Time { int h; Time(int h = 0) :h(h) {} bool operator<(const Time& o)const { return h < o.h; } };

class Thermometer {
    map<Date, map<Time, double>> d;
    Date sd; Time st;
public:
    Thermometer() :sd(1, 1, 2026), st(0) {}
    void setStart(Date a, Time b) { sd = a; st = b; }
    void getStart(Date& a, Time& b) { a = sd; b = st; }
    void setObs(Date a, Time b, double t) { d[a][b] = t; }
    double getTemp(Date a, Time b) { return d.count(a) && d[a].count(b) ? d[a][b] : -999; }
    void setSeries(Date a, vector<double> v) { for (int i = 0; i < 24; i++)d[a][Time(i)] = v[i]; }
    double avgDate(Date a) {
        double s = 0; int c = 0;
        for (auto& p : d[a])s += p.second, c++;
        return c ? s / c : 0;
    }
    double avgMonth(int m) {
        double s = 0; int c = 0;
        for (auto& a : d)if (a.first.m == m)for (auto& b : a.second)s += b.second, c++;
        return c ? s / c : 0;
    }
    double avgAll() {
        double s = 0; int c = 0;
        for (auto& a : d)for (auto& b : a.second)s += b.second, c++;
        return c ? s / c : 0;
    }
    double avgDayNight(int m, bool day) {
        double s = 0; int c = 0;
        for (auto& a : d)if (a.first.m == m)
            for (auto& b : a.second) {
                int h = b.first.h;
                if ((day && h >= 6 && h <= 18) || (!day && (h >= 19 || h <= 5)))s += b.second, c++;
            }
        return c ? s / c : 0;
    }
    void save(string f) {
        ofstream o(f);
        o << sd.d << " " << sd.m << " " << sd.y << " " << st.h << endl;
        for (auto& a : d)for (auto& b : a.second)
            o << a.first.d << " " << a.first.m << " " << a.first.y << " " << b.first.h << " " << b.second << endl;
    }
    void load(string f) {
        ifstream i(f);
        d.clear();
        i >> sd.d >> sd.m >> sd.y >> st.h;
        int dd, mm, yy, hh; double t;
        while (i >> dd >> mm >> yy >> hh >> t)d[Date(dd, mm, yy)][Time(hh)] = t;
    }
};

int main() {
    Thermometer t;
    t.setObs(Date(15, 6, 2026), Time(12), 26.5);
    t.setObs(Date(15, 6, 2026), Time(18), 23);
    cout << t.getTemp(Date(15, 6, 2026), Time(12)) << endl;
    cout << t.avgMonth(6) << endl;
    t.save("w.txt");
}