#include <iostream>
#include <numeric>

class Rac {
private:
    int a;
    int b;
    int c;
public:
    Rac()
    {
        a = 0;
        b = 0;
        c = 1;
    }
    Rac(int a = 0, int b = 0, int c = 1)
    {
        if (c == 0)
        {
            std::cout << "Введено некоректное значение" << std::endl;
            a = 0;
            b = 0;
            c = 1;
        }
        else
        {
            int nod = std::gcd(b, c);
            this->b = b / nod;
            this->c = c / nod;
            this->a = a + this->b / this->c;
            this->b = (this->b % this->c);
        }
    }
    Rac operator+(const Rac& point1)
    {
        b = (b + a * c) * (point1.c) + (point1.b + point1.a * point1.c) * c;
        return Rac(0, b, point1.c * c);
    }
    Rac operator-(const Rac& point1)
    {
        b = (b + a * c) * (point1.c) - (point1.b + point1.a * point1.c) * c;
        return Rac(0, b, point1.c * c);
    }
    Rac operator*(const Rac& point1)
    {
        b = (b + a * c) * (point1.b + point1.a * point1.c);
        return Rac(0, b, point1.c * c);
    }
    Rac operator/(const Rac& point1)
    {
        b = (b + a * c) * point1.c;
        return Rac(0, b, (point1.b + point1.a * point1.c) * c);
    }
    friend std::ostream& operator<<(std::ostream& os, const Rac& racout) {
        os << racout.a << " " << racout.b << "/" << racout.c;
        return os;
    }
};

class LongLong {
private:
    int high;  
    unsigned int low;      
public:
    LongLong() {
        high = 0;
        low = 0;
    }
    LongLong(int h, unsigned int l) {
        high = h;
        low = l;
    }
    LongLong(long long value) {
        high = (int)(value >> 32);
        low = (unsigned int)(value & 0xFFFFFFFF);
    }
    LongLong operator+(const LongLong& other) const {
        LongLong result;
        result.low = low + other.low;
        int carry = 0;
        if (result.low < low) 
            carry = 1;
        result.high = high + other.high + carry;
        return result;
    }
    LongLong operator-(const LongLong& other) const {
        LongLong result;
        result.low = low - other.low;
        int borrow = 0;
        if (low < other.low)
            borrow = 1;
        result.high = high - other.high - borrow;
        return result;
    }
    LongLong operator*(const LongLong& other) const {
        return LongLong(toLongLong()*other.toLongLong());
    }
    LongLong operator/(const LongLong& other) const {
        if (other.toLongLong()==0) {
            std::cout << "Ошибка: деление на 0\n"<<std::endl;
            return LongLong();
        }
        return LongLong(toLongLong()/other.toLongLong());
    }
    LongLong operator%(const LongLong& other) const {
        if (other.toLongLong() == 0) {
            std::cout << "Ошибка: деление на 0\n"<<std::endl;
            return LongLong();
        }
        return LongLong(toLongLong() % other.toLongLong());
    }
    long long toLongLong() const {
        return ((long long)high << 32) | low;
    }
    friend std::ostream& operator<<(std::ostream& os, const LongLong& longnumber) {
        os << longnumber.toLongLong();
        return os;
    }
};

class Time {
private:
    int hour;
    int minute;
    int sec;
public:
    Time() {
        hour = 0;
        minute = 0;
        sec = 0;
    }
    Time(int h , int m , int s ) {
        s =s + m * 60 + h * 3600;
        s %= 86400;
        this->hour = s / 3600;
        this->minute = (s % 3600) / 60;
        this->sec = (s % 3600) % 60;
    }
    void set(int h = 0, int m = 0, int s = 0) {
        s = s + m * 60 + h * 3600;
        s %= 86400;
        this->hour = s / 3600;
        this->minute = (s % 3600) / 60;
        this->sec = (s % 3600) % 60;
    }
    void output() {
        std::cout << "hours: " << hour << " minute: " << minute << " sec: " << sec << std::endl;
    }
    Time time(const Time& t) {
        return Time(abs(hour - t.hour), abs(minute - t.minute), abs(sec - t.sec));
    }
    void shift(int h, int m, int s, bool up)
    {
       int s1 = hour * 3600 + minute * 60 + sec;
       int s2 = h * 3600 + m * 60 + s;
        if (up) this->set(0, 0, s1 + s2);
        else this->set(0, 0,s1 - s2+86400);
    }
};

class Length {
    private:
        int leng;
    public:
        Length()
        {
            leng = 0;
        }
        Length(int l)
        {
            leng = l;
        }
        void set(int l) {
            leng = l;
        }
        void output(int mode=0) {
            if (mode==0) std::cout << "Длина в метрах: " << leng << std::endl;
            else if (mode == 1) std::cout << "Длина в cm: " << leng*100 << std::endl;
            else if (mode == 2) std::cout << "Длина в mm: " << leng * 1000 << std::endl;
            else if (mode == 3) std::cout << "Длина в милях: " << leng *0.000621 << std::endl;
            else if (mode == 4) std::cout << "Длина в ярдах: " << leng *1.093613 << std::endl;
            else if (mode == 5) std::cout << "Длина в дюймах: " << leng*39.37 << std::endl;
            else if (mode == 6) std::cout << "Длина в футах: " << leng *3.28084 << std::endl;
            else if (mode == 7) std::cout << "Длина в Km: " << leng / 1000.0f << std::endl;
        }
};

class Weight {
    private:
        int weg;
    public:
        Weight()
        {
            weg = 0;
        }
        Weight(int w)
        {
            weg = w;
        }
        void set(int w) {
            weg = w;
        }
        void output(int mode = 0) {
            if (mode == 0) std::cout << "Вес в кг: " << weg << std::endl;
            else if (mode == 1) std::cout << "Вес в г: " << weg * 1000 << std::endl;
            else if (mode == 2) std::cout << "Вес в центнерах: " << weg / 100 << std::endl;
            else if (mode == 3) std::cout << "Вес в фунтах: " << weg * 2.2046 << std::endl;
            else if (mode == 4) std::cout << "Вес в унциях: " << weg * 35.273962 << std::endl;
            else if (mode == 5) std::cout << "Вес в каратах: " << weg * 5000 << std::endl;
            else if (mode == 6) std::cout << "Вес в пудах: " << weg * 0.061 << std::endl;
            else if (mode == 7) std::cout << "Вес в тоннах: " << weg / 1000.0f << std::endl;
        }
};

class Temperature {
private:
    int temp;
public:
    Temperature()
    {
        temp = 0;
    }
    Temperature(int t)
    {
        temp = t;
    }
    void set(int t) {
        temp= t;
    }
    void output(int mode = 0) {
        if (mode == 0) std::cout << "Температура в Цельсия: " << temp << std::endl;
        else if (mode == 1) std::cout << "Температура в Фаренгейта: " << temp *33.8 << std::endl;
        else if (mode == 2) std::cout << "Температура в Кельвина: " << temp * 274.15 << std::endl;
        else if (mode == 3) std::cout << "Температура в Ранкина: " << temp * 493.47 << std::endl;
        else if (mode == 4) std::cout << "Температура в Реомюра: " << temp * 0.8 << std::endl;
        
    }
};
void main()
{
    setlocale(LC_ALL, "Russian");
}