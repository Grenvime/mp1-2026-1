#include <iostream>
#include <cmath>
class Bits64 {
private:

    int a;
    unsigned int b;

public:

    Bits64() {
        a = 0;
        b = 0;
    }

    Bits64(int h, unsigned int l) {
        a = h;
        b = l;
    }
   
    Bits64(long long val) {
        a = (int)(val >> 32);
        b = (unsigned int)(val & 0xFFFFFFFF);
    }

    Bits64 operator+(const Bits64& other) const {
        Bits64 result;

        result.b = b + other.b;

        int c = 0;
        if (pow(2, 32)-1-b < other.b)
            c = 1;
        result.a = a + other.a + c;
        return result;
    }

    Bits64 operator-(const Bits64& other) const {
        Bits64 result;
        result.b = b - other.b;
        int d = 0;
        if (b < other.b)
            d = 1;
        result.a = a - other.a - d;
        return result;
    }


    Bits64 operator*(const Bits64& other) const {
        return Bits64(toBits64() * other.toBits64());
    }

    Bits64 operator/(const Bits64& other) const {

        if (other.toBits64() == 0) {
            std::cout << "Ошибка: деление на 0\n" << std::endl;
            return Bits64();
        }
        return Bits64(toBits64() / other.toBits64());
    }

    Bits64 operator%(const Bits64& other) const {

        if (other.toBits64() == 0) {
            std::cout << "Ошибка: деление на 0\n" << std::endl;
            return Bits64();
        }
        return Bits64(toBits64() % other.toBits64());
    }


    long long toBits64() const {
        return ((long long)a << 32) | b;
    }


    friend std::ostream& operator<<(std::ostream& os, const Bits64& longnumber) {
        os << longnumber.toBits64();
        return os;
    }
};
void main()
{
    Bits64 rac1(999999), rac2(10001);
    Bits64 rac3 = rac1 + rac2;

    std::cout << rac3 << std::endl;
}