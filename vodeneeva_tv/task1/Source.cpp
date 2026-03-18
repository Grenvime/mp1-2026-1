#include <iostream>

class LengthConverter {
private:
    double meters; 

public:
    LengthConverter() {
        meters = 0;
    }
    LengthConverter(double m) {
        meters = m;
    }
    void setMeters(double m) {
        meters = m;
    }
    double getMeters() {
        return meters;
    }

    double perevod(int len) const {
        const double fut = 3.281;
        const double yard = 1.094;
        const double arshin = 0.711;
        const double sazhen = 0.547;
        if (len == 1) return meters * fut;
        if (len == 2) return meters * yard;
        if (len == 3) return meters / arshin;
        if (len == 4) return meters * sazhen;
    }

    void print() {
        std::cout << "Длина: " << meters << " м\n";
    }
};

int main() {
    LengthConverter length;

    length.setMeters(5); 
    length.print();

    std::cout << "Выберите единицы измерения для перевода: 1 – фут, 2 – ярд, 3 – аршин, 4 – сажень\n";
    
    int res;
    std::cin >> res;
    switch (res) {
        case 1: 
            std::cout << length.perevod(res) << " футов\n";
            break;
        case 2:
            std::cout << length.perevod(res) << " ярдов\n";
            break;
        case 3:
            std::cout << length.perevod(res) << " аршинов\n";
            break;
        case 4:
            std::cout << length.perevod(res) << " саженей\n";
            break;
    }

    return 0;
}