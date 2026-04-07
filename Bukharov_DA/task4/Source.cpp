#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Date {
	int day, month, year;
};

struct Time {
	int hour, minute;
};

class Record {
public:
	Date date;
	Time start;
	Time end;
	int steps;

	Record() {
		date = { 0,0,0 };
		start = { 0,0 };
		end = { 0,0 };
		steps = 0;
	}

	Record(int d, int m, int y, int sh, int sm, int eh, int em, int s) {
		date = { d, m, y };
		start = { sh, sm };
		end = { eh, em };
		steps = s;
	}

	string getDateString() {
		stringstream ss;
		ss << setfill('0') << setw(2) << date.day << "." << setw(2) << date.month << "." << date.year;
		return ss.str();
	}

	string getTimeString() {
		stringstream ss;
		ss << setfill('0') << setw(2) << start.hour << ":" << setw(2) << start.minute << " - " << setw(2) << end.hour << ":" << setw(2) << end.minute;
		return ss.str();
	}

	string toString() {
		return getDateString() + " " + getTimeString() + " -> " + to_string(steps) + " steps";
	}

	int getWeekday() {
		int d = date.day;
		int m = date.month;
		int y = date.year;

		if (m < 3) {
			m += 12;
			y -= 1;
		}
		int K = y % 100;
		int J = y / 100;
		int h = (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

		return h;
	}
};

class StepCounter {
private:
	vector<Record> history;
	Date startDate;
	bool hasStartDate;

public:
	StepCounter() {
		hasStartDate = false;
		startDate = { 0,0,0 };
	 }
	void setStartDate(int d, int m, int y) {
		startDate = { d, m, y };
		hasStartDate = true;
		cout << "Start date set: " << getStartDate() << endl;
	}

	string getStartDate() {
		if (!hasStartDate) return "Not set";
		stringstream ss;
		ss << startDate.day << "." << startDate.month << "." << startDate.year;
		return ss.str();
	}

	void addRecord(int d, int m, int y, int sh, int sm, int eh, int em, int s) {
		Record rec(d, m, y, sh, sm, eh, em, s);
		history.push_back(rec);
		cout << "Added: " << rec.toString() << endl;
	}

	string getRecord(int index) {
		if (index < 0 || index >= history.size()) {
			return "Record not found";
		}
		return history[index].toString();
	}

	double getAverage(int month = -1, int year = -1) {
		int total = 0;
		int count = 0;

		for (int i = 0; i < history.size(); i++) {
			if (month == -1) {
				total += history[i].steps;
				count++;
			}
			else if (history[i].date.month == month && history[i].date.year == year) {
				total += history[i].steps;
				count++;
			}
		}

		if (count == 0) return 0;
		return (double)total / count;
	}

	double getAverageByWeekday(int weekday) {
		int total = 0;
		int count = 0;

		for (int i = 0; i < history.size(); i++) {
			if (history[i].getWeekday() == weekday) {
				total += history[i].steps;
				count++;
			}
		}
		if (count == 0) return 0;
		return (double)total / count;
	}

	pair<int, string> getMaxInMonth(int month, int year) {
		int maxSteps = 0;
		string maxDate;

		for (int i = 0; i < history.size(); i++) {
			if (history[i].date.month == month && history[i].date.year == year) {
				if (history[i].steps > maxSteps) {
					maxSteps = history[i].steps;
					maxDate = history[i].getDateString();
				}
			}
		}
		return make_pair(maxSteps, maxDate);
	}


	pair<int, string> getMaxAllTime() {
		int maxSteps = 0;
		string maxDate;

		for (int i = 0; i < history.size(); i++) {
			if (history[i].steps > maxSteps) {
				maxSteps = history[i].steps;
				maxDate = history[i].getDateString();
			}
		}
		return make_pair(maxSteps, maxDate);
	}

	void saveToFile(string filename) {
		ofstream file(filename);
		file << "START_DATE:" << startDate.day << "," << startDate.month << "," << startDate.year << endl;
		file << "HAS_START:" << hasStartDate << endl;
		file << "COUNT:" << history.size() << endl;

		for (int i = 0; i < history.size(); i++) {
			file << history[i].date.day << "," << history[i].date.month << "," << history[i].date.year << "," << history[i].start.hour << "," << history[i].start.minute << "," << history[i].end.hour << "," << history[i].end.minute << "," << history[i].steps << endl; 
		}
		file.close();
		cout << "Saved to " << filename << endl;
	}

	void loadFromFile(string filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Cannot open file" << endl;
			return;
		}
		history.clear();

		string line;

		getline(file, line);
		sscanf_s(line.c_str(), "START_DATE: %d, %d, %d", &startDate.day, &startDate.month, &startDate.year);
		getline(file, line);
		int flag;
		sscanf_s(line.c_str(), "HAS_START: %d", &flag);
		hasStartDate = (flag == 1);

		getline(file, line);
		int count;
		sscanf_s(line.c_str(), "COUNT:%d", &count);

		for (int i =0; i < count; i++) {
			getline(file, line);
			int d, m, y, sh, sm, eh, em, s;
			sscanf_s(line.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d", &d, &m, &y, &sh, &sm, &eh, &em, &s);
			addRecord(d, m, y, sh, sm, eh, em, s);
		}
		file.close();
		cout << "Loaded from " << filename << endl;
	}


	void showAll() {
		if (history.empty()) {
			cout << "No records" << endl;
			return;
		}

		cout << "\n=== ALL RECORDS ===" << endl;
		for (int i = 0; i < history.size(); i++) {
			cout << i << ". " << history[i].toString() << endl;
		}
		cout << "==============\n" << endl;
	}

	int getCount() {
		return history.size();
	}
};

int main() {
	StepCounter counter;

	cout << "=== STEP COUNTER ===" << endl;
	counter.addRecord(15, 1, 2025, 8, 0, 8, 30, 3000);
	counter.addRecord(16, 1, 2025, 9, 15, 10, 0, 4500);
	counter.addRecord(20, 1, 2025, 7, 45, 8, 20, 5000);
	counter.addRecord(1, 2, 2025, 8, 0, 8, 45, 6200);
	counter.addRecord(3, 2, 2025, 8, 30, 9, 15, 3800);

	counter.showAll();

	counter.setStartDate(1, 1, 2025);
	cout << "Start date: " << counter.getStartDate() << endl;

	cout << "\nRecord at index 0: " << counter.getRecord(0) << endl;
	
	cout << "\nAverage for January 2025: " << counter.getAverage(1, 2025) << endl;
	cout << "Average all time: " << counter.getAverage() << endl;

	cout << "\nAverage on Monday (2): " << counter.getAverageByWeekday(2) << endl;

	pair<int, string> maxJan = counter.getMaxInMonth(1, 2025);
	cout << "\nMax in January: " << maxJan.first << " steps on " << maxJan.second << endl;

	counter.saveToFile("steps.txt");

	StepCounter counter2;
	counter2.loadFromFile("steps.txt");
	cout << "\nLoaded " << counter2.getCount() << " records" << endl;


	cin.get();
	return 0;
}