#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Date {
	int day;
	int month;
	int year;
};
struct Observation {
	string name;
	Date date;
	double weight;
};

class Scales {
	Observation history[100];
	Date startDate;
	int count;
public:
	Scales() {
		count = 0;
	}
	void SetStartDate(int d, int m, int y) {
		startDate.day = d;
		startDate.month = m;
		startDate.year = y;
	}
	Date GetStartDate() {
		return startDate;
	}
	void SetObservation(string name, int d, int m, int y, double weight) {
		history[count].name = name;
		history[count].date.day = d;
		history[count].date.month = m;
		history[count].date.year = y;
		for (int i = 0; i < count; i++) {
			if (history[i].name == name &&
				history[i].date.day == d &&
				history[i].date.month == m &&
				history[i].date.year == y) {
				history[i].weight = weight;
				return;
			}
		}
		count++;
	}
	double GetWeight(string name, int d, int m, int y) {
		for (int i = 0; i < count; i++) {
			if (history[i].name == name &&
				history[i].date.day == d &&
				history[i].date.month == m &&
				history[i].date.year == y) {
				return history[i].weight;
			}
		}
	}
	double AverageWeight(string name, int month = 0) {
		double sum = 0;
		double n = 0;
		for (int i; i < count; i++) {
			if (history[i].name == name &&
				(month == 0 || history[i].date.month == month)) {
				sum += history[i].weight;
				n++;
			}
		}
		return sum / n;
	}
	double MaxWeight(string name, int month) {
		double maxWeight = -1;
		for (int i; i < count; i++) {
			if (history[i].name == name &&
				(month == 0 || history[i].date.month == month)) {
				if (history[i].weight > maxWeight) {
					maxWeight = history[i].weight;
				}
			}
		}
		return maxWeight;

	}
	void SaveToFile(string filename) {
		ofstream file(filename); // output stream

		for (int i = 0; i < count; i++)
		{
			file << history[i].name << " "
				<< history[i].date.day << " "
				<< history[i].date.month << " "
				<< history[i].date.year << " "
				<< history[i].weight << endl;
		}

		file.close();

	}
	void LoadFromFile(string filename) {
		ifstream file(filename); //input stream

		count = 0;

		while (file >> history[count].name
			>> history[count].date.day
			>> history[count].date.month
			>> history[count].date.year
			>> history[count].weight)
		{
			count++;
		}

		file.close();
	}
};
int main() {

}