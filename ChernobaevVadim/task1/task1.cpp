#include<iostream>
#include<iomanip>
#include <locale.h>
class Time {
    int hours, minutes, seconds;
    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }
    }
public:
    Time(int h = 0, int m = 0, int s = 0)
        :hours(h), minutes(m), seconds(s) {
        normalize();
    }
    void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
        normalize();
    }
    void getTime(int& h, int& m, int& s) const {
        h = hours;
        m = minutes;
        s = seconds;
    }
    Time timeDifference(const Time& other) const {
        int total1 = hours * 3600 + minutes * 60 + seconds;
        int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;

        int diff = total1 - total2;
        if (diff < 0) diff += 24 * 3600;  // учитываем переход через полночь

        int diff_hours = diff / 3600;
        int diff_minutes = (diff % 3600) / 60;
        int diff_seconds = diff % 60;

        return Time(diff_hours, diff_minutes, diff_seconds);
    }
    void timeShift(int s_shift, int m_shift, int h_shift) {
        hours += h_shift;
        minutes += m_shift;
        seconds += s_shift;
        normalize();
    }
    void printTime() const {
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds << std::endl;;
    }
};
//пример испозьзования
int main() {
    setlocale(LC_ALL, "Russian");

    Time t1(10, 45, 30);
    Time t2(12, 15, 25);

    std::cout << "Первое Время: " << std::endl;
    t1.printTime();
    std::cout << "Второе Время: " << std::endl;
    t2.printTime();

    std::cout << "Разница между первым временем и вторым временем: " << std::endl;
    Time diff1 = t1.timeDifference(t2);
    diff1.printTime();

    std::cout << "Разница между вторым временем и первым: " << std::endl;
    Time diff2 = t2.timeDifference(t1);
    diff2.printTime();

    std::cout << "Сдвиг первого времени на (3,10,4): " << std::endl;
    t1.timeShift(3, 10, 4);
    t1.printTime();

    Time t_normalize(22, 59, 60);
    std::cout << "Демонстрация нормализации на (22, 59, 60): " << std::endl;
    t_normalize.printTime();
}

