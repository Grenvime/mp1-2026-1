#include <iostream>

class LongNumber
{
public:
    int first;
    unsigned int second;
    bool init(int s, unsigned int m)
    {
        if (m < 0)
            return false;
        else
        {
            first = s;
            second = m;
            return true;
        }
    }

    LongNumber add(const LongNumber& a, const LongNumber& b);
    LongNumber sub(const LongNumber& a, const LongNumber& b);
    LongNumber mul(const LongNumber& a, const LongNumber& b);
    LongNumber divc(const LongNumber& a, const LongNumber& b);
    LongNumber divr(const LongNumber& a, const LongNumber& b);

    void read();

};

LongNumber LongNumber::add(const LongNumber& a, const LongNumber& b)
{
    LongNumber t;
    t.first = a.first + b.first;
    t.second = a.second + b.second;
    if (t.second > 999999999)
    {
        t.first = t.first + 1;
        t.second = t.second - 1000000000;
    }
    return t;
}

LongNumber LongNumber::sub(const LongNumber& a, const LongNumber& b)
{
    LongNumber t;
    t.first = a.first - b.first;
    t.second = a.second - b.second;
    return t;
}

LongNumber LongNumber::mul(const LongNumber& a, const LongNumber& b)

{
    LongNumber t;
    t.first = a.first * b.first;
    t.second = a.second * b.second;
    return t;
}

LongNumber LongNumber::divc(const LongNumber& a, const LongNumber& b)
{
    LongNumber t;
    t.first = a.first / b.first;
    t.second = a.second / b.second;
    return t;
}

LongNumber LongNumber::divr(const LongNumber& a, const LongNumber& b)
{
    LongNumber t;
    t.first = a.first % b.first;
    t.second = a.second % b.second;
    return t;
}

void LongNumber::read()
{
    int s = 0;
    unsigned int m = 0;
    do
    {
        std::cout << "First number: ";
        std::cin >> s;
        std::cout << "Second number: ";
        std::cin >> m;
    } while (!init(s, m));
}


int main() {
    LongNumber a, b, result;

    std::cout << "Print first number:" << std::endl;
    a.read();

    std::cout << "Print second number:" << std::endl;
    b.read();

    result = a.add(a, b);
    std::cout << "Sum: " << result.first << " " << result.second << std::endl;

    result = a.sub(a, b);
    std::cout << "Difference: " << result.first << " " << result.second << std::endl;

    result = a.mul(a, b);
    std::cout << "Multiplication: " << result.first << " " << result.second << std::endl;

    result = a.divc(a, b);
    std::cout << "Division is complete: " << result.first << " " << result.second << std::endl;

    result = a.divr(a, b);
    std::cout << "Division with remainder: " << result.first << " " << result.second << std::endl;

    return 0;
}