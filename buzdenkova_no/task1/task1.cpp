#include <iostream>

class LongNumber {
private:
    int64_t result;

public:
    int first;
    unsigned int second;

    LongNumber(int64_t r = 0) : result(r) {}

    LongNumber(int32_t first, uint32_t second) :
        result(static_cast<int64_t>(first) << 32 | second) {
    }

    void print() const {
        std::cout << result << '\n';
    }

    int64_t toInt64() const {
        return result;
    }

    LongNumber add(const LongNumber& b);
    LongNumber sub(const LongNumber& b);
    LongNumber mul(const LongNumber& b);
    LongNumber divc(const LongNumber& b);
    LongNumber divr(const LongNumber& b);

};

LongNumber LongNumber::add(const LongNumber& b)
{
    LongNumber t;
    t.result = result + b.result;
    return t;
}

LongNumber LongNumber::sub(const LongNumber& b)
{
    LongNumber t;
    t.result = result - b.result;
    return t;
}

LongNumber LongNumber::mul(const LongNumber& b)
{
    LongNumber t;
    t.result = result * b.result;
    return t;
}

LongNumber LongNumber::divc(const LongNumber& b)
{
    LongNumber t;
    t.result = result / b.result;
    return t;
}

LongNumber LongNumber::divr(const LongNumber& b)
{
    LongNumber t;
    t.result = result % b.result;
    return t;
}

int main() {
    LongNumber a(0xFFFE, 0xFEDC);
    LongNumber b(0xAABBCCDD);

    std::cout << "Print first number:";
    a.print();

    std::cout << "Print second number:";
    b.print();

    LongNumber sum = a.add(b);
    std::cout << "Sum: ";
    sum.print();

    LongNumber sub = a.sub(b);
    std::cout << "Difference: ";
    sub.print();

    LongNumber mul = a.mul(b);
    std::cout << "Multiplication: ";
    mul.print();

    LongNumber divc = a.divc(b);
    std::cout << "Division is complete: ";
    divc.print();

    LongNumber divr = a.divr(b);
    std::cout << "Division with remainder: ";
    divr.print();

    return 0;
}