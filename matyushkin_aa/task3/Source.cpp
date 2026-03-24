#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef double (*SimpleFunc)(double);

class FunctionTabulator {
private:
    SimpleFunc func;
    int points;
    double start, end;

    vector<double> x_vals;
    vector<double> y_vals;

public:
    FunctionTabulator() {
        func = nullptr;
        points = 0;
        start = 0.0;
        end = 0.0;
    }

    ~FunctionTabulator() {}

    void setFunction(SimpleFunc f) {
        func = f;
    }

    void setNumPoints(int n) {
        points = n;
    }

    int getNumPoints() {
        return points;
    }

    void setInterval(double a, double b) {
        start = a;
        end = b;
    }

    void getInterval(double& a, double& b) {
        a = start;
        b = end;
    }

    void tabulate() {
        x_vals.clear();
        y_vals.clear();

        double step = (end - start) / (points - 1);

        for (int i = 0; i < points; i++) {
            double x = start + i * step;
            double y = func(x);

            x_vals.push_back(x);
            y_vals.push_back(y);
        }
    }

    void printResults() {
        cout << "X \t Y\n";
        cout << "----------------\n";
        for (int i = 0; i < points; i++) {
            cout << x_vals[i] << " \t " << y_vals[i] << "\n";
        }
    }

    void saveToFile(string filename) {
        ofstream out(filename);
        out << "X \t Y\n";
        for (int i = 0; i < points; i++) {
            out << x_vals[i] << " \t " << y_vals[i] << "\n";
        }
        out.close();
        cout << "\nСохранено в файл: " << filename << "\n";
    }
};

double myFunc(double x) {
    return x * x;
}

int main() {
    setlocale(LC_ALL, "ru");
    FunctionTabulator tab;

    tab.setFunction(myFunc);
    tab.setNumPoints(5);
    tab.setInterval(0.0, 4.0);

    tab.tabulate();
    tab.printResults();
    tab.saveToFile("result.txt");

    system("pause");

    return 0;
}