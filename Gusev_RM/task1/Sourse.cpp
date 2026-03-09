#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
class temper {
	double temp;
public:
	temper(double celsi) {
		temp = celsi;
	}
	void smen(double celsi) {
		temp = celsi;
	}
	void print() {
		std::cout <<"\nВ цельсия: "<<temp<<"\n";
	}
	double far() {
		double farg;
		farg = temp * (1.8) + 32;
		std::cout <<"\nВ фаренгейтах: "<<farg<<"\n";
		return farg;
	}
	double kel() {
		double kelvin;
		kelvin = temp + 273.15;
		std::cout <<"\nВ Кельвинах: \n"<<kelvin<<"\n";
		return kelvin;
	}
	double rank() {
		double rankin;
		rankin = (temp + 273.15)*(1.8);
		std::cout <<"\nВ Ранкинах: "<<rankin<<"\n";
		return rankin;
	}
	double deli() {
		double delilu;
		delilu = (100-temp) * 1.5;
		std::cout <<"\nПо Делилю: "<<delilu<<"\n";
		return delilu;
	}
	double niut() {
		double niuton;
		niuton = temp * 0.33;
		std::cout <<"\nПо Ньютону: "<<niuton<<"\n";
		return niuton;
	}
	double reom() {
		double reomur;
		reomur = temp * 0.8;
		std::cout <<"\nПо Реомюру: "<<reomur<<"\n";
		return reomur;
	}
	double rem() {
		double remer;
		remer = temp *(21.0/40.0)+7.5;
		std::cout << "\nПо Рёмеру: "<<remer<<"\n";
		return remer;
	}
};
int main() {
	setlocale(LC_ALL, "rus");
	int a;
	bool q = true;
	double temp;
	std::cout <<"Ведите температуру в градусах цельсия"<<"\n";
	std::cin >>temp;
	temper t(temp);
	while (q == true){
		std::cout <<"\nВ какие единицы перевести:"<<"\n";
		std::cout <<"0-стоп\n1-вывести в цельсия\n2-Фаренгейт\n3-Кельвины\n"\
			"4-Ранкины\n5 - по Делилю\n6 - по Ньютону\n7 - по Реомюру\n8 - по Рёмеру\n"\
			"9-сменить значение"<<"\n";
		std::cin >> a;
		if (a == 0) {
			q = false;
		}
		if (a == 1) {
			t.print();
		}
		if (a == 2) {
			t.far();
		}
		if (a == 3) {
			t.kel();
		}
		if (a == 4) {
			t.rank();
		}
		if (a == 5) {
			t.deli();
		}
		if (a == 6) {
			t.niut();
		}
		if (a == 7) {
			t.reom();
		}
		if (a == 8) {
			t.rem();
		}
		if (a == 9) {
			std::cout<<"Ведите температуру в градусах цельсия"<<"\n";
			std::cin >>temp;
			t.smen(temp);
		}
	}
	system("pause");
}