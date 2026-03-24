#include <iostream>
#include <cmath>

using Funcptr = double(*)(double);
using Funcelptr = double(*)(double, double, int);
double Exp(double y_past, double y, int n);
double Sin(double y_past, double y, int n);
double Cos(double y_past, double y, int n);

class Tylor {
	private:
		int n;
		double(*func[3])(double) = {sin,cos,exp};
		short numfunc;
		double (*func_el[3])(double, double, int) = { Sin,Cos,Exp };
		double x;
	public:
		Tylor(int count = 1, short num = 0,double X=0) {
			n = count;
			numfunc = num;
			x = X;
		}
		void Setfunc(short num) { numfunc=num%3; }
		Funcptr Getfunc() const { return func[numfunc]; }
		void SetNum(int count) { n = count; }
		int GetNum() const { return n; }
		void SetX(double X) { x = X; }
		Funcelptr GetForm() const { return func_el[numfunc]; }
		double GetElement(int el) const {
			if (el > n) {
				return -2;
			}
			double E=0;
			for (int i = 0; i < el; i++) {
				E = func_el[numfunc](E, x, i);
			}
			return E;

		}
		double GetValue() const {
			double E = 0,sum=0;
			for (int i = 0; i < n; i++) {
				E = func_el[numfunc](E, x, i);
				sum += E;
			}
			return sum;
		}
		void Err()  {
			double T = GetValue(),t=func[numfunc](x);
			std::cout << "Отклонение: " << t - T << std::endl;
		}
};
void main() {
	setlocale(LC_ALL, "Russian");
	double x = 0.5;
	int n = 8;
	Tylor t(n, 0, x);
	std::cout << t.GetElement(1) << std::endl;
	std::cout << t.GetValue() << std::endl;
	t.Err();

}
double Exp(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return y_past * (y / n);
}

double Sin(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return fabs(y_past) * (y * y / (4 * n * n + 2 * n)) * pow(-1, n);
}

double Cos(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return fabs(y_past) * (y * y / (4 * n * n - 2 * n)) * pow(-1, n);
}