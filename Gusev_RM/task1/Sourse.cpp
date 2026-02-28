#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
		printf("\nВ цельсия : % f\n", temp);
	}
	double far() {
		double farg;
		farg = temp * (1.8) + 32;
		printf("\nв фаренгейтах: %f\n", farg);
		return farg;
	}
	double kel() {
		double kelvin;
		kelvin = temp + 273.15;
		printf("\nв Кельвинах: %f\n", kelvin);
		return kelvin;
	}
	double rank() {
		double rankin;
		rankin = (temp + 273.15)*(1.8);
		printf("\nв Ранкинах: %f\n", rankin);
		return rankin;
	}
	double deli() {
		double delilu;
		delilu = (100-temp) * 1.5;
		printf("\nпо Делилю: %f\n", delilu);
		return delilu;
	}
	double niut() {
		double niuton;
		niuton = temp * 0.33;
		printf("\nпо Ньютону: %f\n", niuton);
		return niuton;
	}
	double reom() {
		double reomur;
		reomur = temp * 0.8;
		printf("\nпо Реомюру: %f\n", reomur);
		return reomur;
	}
	double rem() {
		double remer;
		remer = temp *(21.0/40.0)+7.5;
		printf("\nпо Рёмеру: %f\n", remer);
		return remer;
	}
};
int main() {
	setlocale(LC_ALL, "rus");
	int a;
	bool q = true;
	double temp;
	printf("Ведите температуру в градусах цельсия\n");
	scanf_s(" %lf", &temp);
	temper t(temp);
	while (q == true){
		printf("\nВ какие единицы перевести:\n");
		printf("0-стоп\n1-вывести в цельсия\n2-Фаренгейт\n3-Кельвины\n"\
			"4-Ранкины\n5 - по Делилю\n6 - по Ньютону\n7 - по Реомюру\n8 - по Рёмеру\n"\
			"9-сменить значение\n");
		scanf_s("%i", &a);
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
			printf("Ведите температуру в градусах цельсия\n");
			scanf_s(" %lf", &temp);
			t.smen(temp);
		}
	}
	system("pause");
}