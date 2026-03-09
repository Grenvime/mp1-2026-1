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
        Rac(int cel , int ch , int z )
        {
            if (c == 0)
            {
                std::cout << "Ââåäåíî íåêîðåêòíîå çíà÷åíèå" << std::endl;
                a = 0;
                b = 0;
                c = 1;
            }
            else
            {
                int nod = std::gcd(ch, z);
                b = ch / nod;
                c = z / nod;
                a = cel + b / c;
                b = (b % c);
            }
        }
        Rac operator+(const Rac& point1)
        {
            return Rac(0, (b + a * c) * (point1.c) + (point1.b + point1.a * point1.c) * c, point1.c * c);
        }
        Rac operator-(const Rac& point1)
        {
            return Rac(0, (b + a * c) * (point1.c) - (point1.b + point1.a * point1.c) * c, point1.c * c);
        }
        Rac operator*(const Rac& point1)
        {
            return Rac(0, (b + a * c) * (point1.b + point1.a * point1.c), point1.c * c);
        }
        Rac operator/(const Rac& point1)
        {
            return Rac(0, (b + a * c) * point1.c, (point1.b + point1.a * point1.c) * c);
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
            if (4294967295-low < other.low)
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
                std::cout << "Îøèáêà: äåëåíèå íà 0\n"<<std::endl;
                return LongLong();
            }
            return LongLong(toLongLong()/other.toLongLong());
        }
        LongLong operator%(const LongLong& other) const {
            if (other.toLongLong() == 0) {
                std::cout << "Îøèáêà: äåëåíèå íà 0\n"<<std::endl;
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
            hour = s / 3600;
            minute = (s % 3600) / 60;
            sec = (s % 3600) % 60;
        }
        void output(int& h, int& m, int& s) {
            h = hour;
            m = minute;
            s = sec;
        }
        Time time(const Time& t) {
            return Time(abs(hour - t.hour), abs(minute - t.minute), abs(sec - t.sec));
        }
        void shift(int h, int m, int s, bool up)
        {
           int s1 = hour * 3600 + minute * 60 + sec;
           int s2 = h * 3600 + m * 60 + s;
            if (up) set(0, 0, s1 + s2);
            else set(0, 0,s1 - s2+86400);
        }
        friend std::ostream& operator<<(std::ostream& os, const Time& time) {
            os << "hours: " << time.hour << " minute: " << time.minute << " sec: " << time.sec;
            return os;
        }
};
class Length {
    private:
        double leng;
    public:
        Length()
        {
            leng = 0;
        }
        Length(double l)
        {
            leng = l;
        }
        void set(double l) {
            leng = l;
        }
        void output(double& l,int mode=0) {
            if (mode==0) l=leng;
            else if (mode == 1) l=leng*100;//cm
            else if (mode == 2) l=leng * 1000;//mm
            else if (mode == 3) l=leng *0.000621;//mili
            else if (mode == 4) l=leng *1.093613;//ÿðäû
            else if (mode == 5) l=leng*39.37;//äþéì
            else if (mode == 6) l=leng *3.28084 ;//ôóò
            else if (mode == 7) l=leng / 1000.0f;//km
        }
        friend std::ostream& operator<<(std::ostream& os, const Length& L) {
            os << "Äëèíà â ìåòðàõ: " << L.leng ;
            return os;
        }
};
class Weight {
    private:
        double weg;
    public:
        Weight()
        {
            weg = 0;
        }
        Weight(double w)
        {
            weg = w;
        }
        void set(double w) {
            weg = w;
        }
        void output(double& w,int mode = 0) {
            if (mode == 0) w=weg;
            else if (mode == 1) w=weg * 1000;//g
            else if (mode == 2) w=weg / 100;//öåíòíåð
            else if (mode == 3) w=weg * 2.2046;//ôóíò
            else if (mode == 4) w=weg * 35.273962;//óíöèÿ
            else if (mode == 5) w=weg * 5000;//êàðàò
            else if (mode == 6)w=weg * 0.061;//ïóä
            else if (mode == 7) w=weg / 1000.0f;//òîííà
        }
        friend std::ostream& operator<<(std::ostream& os, const Weight& W) {
            os << "Âåñ â êã: " << W.weg;
            return os;
        }
};
class Temperature {
private:
    double temp;
public:
    Temperature()
    {
        temp = 0;
    }
    Temperature(double t)
    {
        temp = t;
    }
    void set(double t) {
        temp= t;
    }
    void output(double& t,int mode = 0) {
        if (mode == 0) t=temp;
        else if (mode == 1) t=temp * 9 / 5 + 33.8;//F
        else if (mode == 2) t=temp + 273.15;//K
        else if (mode == 3) t=(temp + 273.15)*9/5;//Ðàíêèí
        else if (mode == 4) t=temp * 0.8;//Ðåîìþð
    }
    friend std::ostream& operator<<(std::ostream& os, const Temperature& T) {
        os << "Òåìïåðàòóðà â Öåëüñèÿ: " << T.temp;
        return os;
    }
};
void main()
{
    setlocale(LC_ALL, "Russian");
    //1.1
    Rac rac1(1, 5, 3), rac2(2, 10, 7), rac3;
    rac3 = rac1 + rac2;
    std::cout << " ÏÅÐÂÛÉ ÊËÀÑÑ ÐÀÖÈÎÍÀËÜÍÛÅ ×ÈÑËÀ" << std::endl;
    std::cout << rac1 << " + " << rac2 << " = " << rac3 << std::endl;
    std::cout << rac1 << " - " << rac2 << " = " << rac1 - rac2 << std::endl;
    std::cout << rac1 << " * " << rac2 << " = " << rac1 * rac2 << std::endl;
    std::cout << rac1 << " / " << rac2 << " = " << rac1 / rac2 << std::endl;
    //1.2
    LongLong a(2148000000), b(11148000000);
    std::cout << "\n ÂÒÎÐÎÉ ÊËÀÑÑ ÁÎËÜØÈÅ ×ÈÑËÀ" << std::endl;
    std::cout << a << " + " << b << " = " << a+b << std::endl;
    std::cout << a << " - " << b << " = " << a-b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
    std::cout << a << " / " << b << " = " << a / b << std::endl;
    std::cout << a << " % " << b << " = " << a % b << std::endl;
    //1.3
    Time t;
    int h, m, s;
    std::cout << "\n ÒÐÅÒÈÉ ÊËÀÑÑ ÂÐÅÌß" << std::endl;
    std::cout << t << std::endl;
    t.set(12, 45, 32);
    std::cout << t << std::endl;
    Time res = Time(23, 1, 5).time(t);
    std::cout << "Ðàçíèöà ìåæäó: 23:1:5 è 12:45:32 = "<< res << std::endl;
    t.shift(15, 21, 49, false);
    std::cout << "Ñäâèã âíèç 12:45:32  íà 15:21:49 = "<< t << std::endl;
    t.shift(8, 50, 49, true);
    std::cout << "Ñäâèã ââåðõ íà 8:50:49 = "<< t << std::endl;
    t.output(h,m,s);
    std::cout << "×àñû: "<<h<<"\nÌèíóòû: "<<m<<"\nÑåêóíäû: "<< s << std::endl;
    // 1.4
    std::cout << "\n ×ÅÒÂÅÐÒÛÉ ÊËÀÑÑ ÊÎÍÂÅÐÒÎÐ ÄËÈÍÛ" << std::endl;
    Length l;
    double leg;
    std::cout << l << std::endl;
    l.set(173);
    std::cout << l << std::endl;
    for (int i = 0; i <= 7; i++)
    {
        l.output(leg,i);
        std::cout << leg<<" "<< i << std::endl;
    }
    // 1.5
    std::cout << "\n ÏßÒÛÉ ÊËÀÑÑ ÊÎÍÂÅÐÒÎÐ ÂÅÑÀ" << std::endl;
    Weight w;
    double weg;
    std::cout << w << std::endl;
    w.set(279);
    std::cout << w << std::endl;
    for (int i = 0; i <= 7; i++)
    {
        w.output(weg, i);
        std::cout << weg << " " << i << std::endl;
    }
    // 1.6
    std::cout << "\n ØÅÑÒÎÉ ÊËÀÑÑ ÊÎÍÂÅÐÒÎÐ ÒÅÌÏÅÐÀÒÓÐÛ" << std::endl;
    Temperature T;
    double Temp;
    std::cout << T << std::endl;
    T.set(36.6);
    std::cout << T << std::endl;
    for (int i = 0; i <= 4; i++)
    {
        T.output(Temp, i);
        std::cout << Temp << " " << i << std::endl;
    }
}