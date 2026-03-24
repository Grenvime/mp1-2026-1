#include <iostream>
#include <string>

using namespace std;

class TemperatureConverter {
private:
    double celsius;

public:
    TemperatureConverter(double temp) : celsius(temp) {}

    void setCelsius(double temp) {
        celsius = temp;
    }

    double getCelsius() {
        return celsius;
    }

    double getFahrenheit() {
        return (celsius * 9.0 / 5.0) + 32.0;
    }

    double getKelvin() {
        return celsius + 273.15;
    }

    double getRankine() {
        return (celsius + 273.15) * 9.0 / 5.0;
    }

    void print() {
        cout << "--- Текущее состояние конвертера ---" << endl;
        cout << "Цельсий:    " << celsius << " C" << endl;
        cout << "Фаренгейт:  " << getFahrenheit() << " F" << endl;
        cout << "Кельвин:    " << getKelvin() << " K" << endl;
        cout << "Ранкин:     " << getRankine() << " Ra" << endl;
        cout << "------------------------------------" << endl;
    }
};

int main() {
    TemperatureConverter myTemp(25.0);

    myTemp.print();

    cout << "\nУстанавливаем новую температуру: 100 C" << endl;
    myTemp.setCelsius(100.0);

    cout << "Только Кельвины: " << myTemp.getKelvin() << " K" << endl;
    cout << "Только Фаренгейты: " << myTemp.getFahrenheit() << " F" << endl;

    return 0;
}