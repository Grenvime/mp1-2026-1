#include <iostream>
#include <windows.h>

class Length {
private:
	float meters = 0;
public:
	Length() {}
	Length(const float meters_n) {
		meters = meters_n;
	}

	float Meters() { return meters; }
	void Meters(const float meters_n) { meters = meters_n; }

	float GetExoticUnit(std::string unit) {

		if (unit == "фут") { return meters * 3.28084; }
		else if (unit == "ярд") { return meters * 1.093613; }
		else if (unit == "аршин") { return meters * 0.7112; }
		else if (unit == "сажень") { return meters * 2.1336; }
		else { throw std::exception("е.и. не распознана"); }
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Length l = Length();

	while (1) {
		char mode = 0;

		std::cout << "1 - Установить длину в метрах\n2 - Узнать длину в метрах\n3 - Узнать длину в других е.и." << std::endl;
		std::cin >> mode;

		if (mode == '1') {
			float length_n;

			std::cout << "Укажите длину" << std::endl;
			std::cin >> length_n;

			l.Meters(length_n);
		}
		if (mode == '2') {
			std::cout << "Длина в метрах: " << l.Meters() << std::endl;
		}
		if (mode == '3') {
			std::string unit;

			std::cout << "Выберите е.и. (фут, ярд, аршин, сажень)" << std::endl;
			std::cin >> unit;

			try {
				std::cout << l.GetExoticUnit(unit) << std::endl;
			}
			catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
		}
	}
}
