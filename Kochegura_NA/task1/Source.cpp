#include <iostream>
#include <iomanip>

class Vremy {
private:
	int hours;
	int minutes;
	int seconds;

	void calibrovca() {

		if (seconds >= 60) {
			minutes += seconds / 60;
			seconds = seconds % 60;
		}
		else if (seconds < 0) {
			minutes -= (-seconds + 59) / 60;
			seconds = (seconds % 60 + 60) % 60;
		}

		if (minutes >= 60) {
			hours += minutes / 60;
			minutes = minutes % 60;
		}
		else if (minutes < 0) {
			hours -= (-minutes + 59) / 60;
			minutes = (minutes % 60 + 60) % 60;
		}

		if (hours >= 24) {
			hours = hours % 24;
		}
		else if (hours < 0) {
			hours = (hours % 24 + 24) % 24;
		}
	}

public:
	Vremy() {
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	Vremy(int h, int m, int s) {
		hours = h;
		minutes = m;
		seconds = s;
		calibrovca();
	}
	
	void ustanovitVremy(int h, int m, int s) {
		hours = h;
		minutes = m;
		seconds = s;
		calibrovca();
	}

	void uznatVremy(int& h, int& m, int& s) const{
		h = hours;
		m = minutes;
		s = seconds;
	}

	Vremy raznica(const Vremy& other) const {
		int tekushieVremy = hours * 3600 + minutes * 60 + seconds;
		int otherVremy = other.hours * 3600 + other.minutes * 60 + other.seconds;
		int raznicaVremy = otherVremy - tekushieVremy;

		if (raznicaVremy < 0) {
			raznicaVremy += 24 * 3600;
		}

		Vremy result;
		result.hours = raznicaVremy / 3600;
		result.minutes = (raznicaVremy % 3600) / 60;
		result.seconds = raznicaVremy % 60;

		return result;
	}
	
	void sdvigVpered(int h, int m, int s) {
		hours += h;
		minutes += m;
		seconds += s;
		calibrovca();
	}

	void sdvigNazad(int h, int m, int s) {
		hours -= h;
		minutes -= m;
		seconds -= s;
		calibrovca();
	}

	void vivod() const {
		if (hours < 10) std::cout << "0";
		std::cout << hours << ":";

		if (minutes < 10) std::cout << "0";
		std::cout << minutes << ":";

		if (seconds < 10) std::cout << "0";
		std::cout << seconds << ":";
	}
};

int main() {
	std::cout << "test\n\n";

	Vremy v1(13, 25, 46);
	std::cout << "t1 = ";
	v1.vivod();
	std::cout << std::endl;

	Vremy v2(17, 20, 10);
	std::cout << "t2 = ";
	v2.vivod();
	std::cout << std::endl;

	Vremy razn = v1.raznica(v2);
	std::cout << " Raznica (v2 - v1) = ";
	razn.vivod();
	std::cout << std::endl << std::endl;

	std::cout << "v1 sdvig nazad na 3 hours 7 minutes 12 seconds:\n";
	v1.sdvigNazad(3, 7, 12);
	std::cout << "v1 = ";
	v1.vivod();
	std::cout << std::endl << std::endl;

	std::cout << "v1 sdvig vpered na 1 hours 40 minutes 59 seconds:\n";
	v1.sdvigVpered(1, 40, 59);
	std::cout << "v1 = ";
	v1.vivod();
	std::cout << std::endl << std::endl;

	std::cin.get();
	return 0;
}