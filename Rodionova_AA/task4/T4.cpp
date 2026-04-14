#include <iostream>
#include <fstream>

enum Month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
class Date {
private:
	short day;
	Month month;
	int year;
public:
	Date(int d = 1, int m = 1, int y = 1) : day(d), month(static_cast<Month>(m)), year(y) {
		if ((m < 1) || (m > 12) || (d <= 0) || (d > days[m % 13])) {
			throw "Некоректные данные";
		}
	}
	bool operator<(const Date& other) {
		bool t;
		if (year < other.year) {
			t = true;
		}
		else {
			if (month < other.month) {
				t = true;
			}
			else {
				if (day < other.day) {
					t = true;
				}
				else t = false;
			}
		}
		return t;
	}
	bool operator>(const Date& other) {
		bool t;
		if (year > other.year) {
			t = true;
		}
		else {
			if (month > other.month) {
				t = true;
			}
			else {
				if (day > other.day) {
					t = true;
				}
				else t = false;
			}
		}
		return t;
	}

	Month Getmonth() {
		return month;
	}
	friend std::ostream& operator<<(std::ostream& os, const Date& d) {
		os << d.year << "\n" << d.month << "\n" << d.day << std::endl;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Date& d) {
		int m;
		is >> d.year >> m >> d.day;
		d.month = static_cast<Month>(m);
		return is;
	}
};

class Time {
private:
	short hour;
	short minute;
public:
	Time(short h = 0, short m = 0) : hour(h), minute(m) {
		if ((h > 23) || (h < 0) || (m < 0) || (m > 59)) {
			throw "Некоректные данные";
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const Time& t) {
		os << t.hour << "\n" << t.minute << std::endl;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Time& t) {
		is >> t.hour >> t.minute;
		return is;
	}
};
class Tally {
private:
	Time start;
	Time end;
	int len;
public:
	Date date;
	Tally(Date d = Date(), Time s = Time(), Time e = Time(), int c = 0) : date(d), start(s), end(e), len(c) {
	}
	Tally& operator=(const Tally& t) {
		date = t.date;
		start = t.start;
		end = t.end;
		len = t.len;
		return *this;
	}
	int Getlen() {
		return len;
	}
	friend std::ostream& operator<<(std::ostream& os, const Tally& t) {
		os << t.start << "\n" << t.end << "\n" << t.len << '\n' << t.date << std::endl;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Tally& t) {
		is >> t.start >> t.end >> t.len >> t.date;
		return is;
	}
};
class Pedometer {
private:
	Date start;
	Tally* ped;
	unsigned int len;
	unsigned int count;
public:
	Pedometer(Date s = Date()) : start(s) {
		ped = new Tally[2];
		len = 2;
		count = 0;
	}
	void SetStart(Date s)
	{
		Tally* temp = new Tally[len];
		int t = 0;
		count = 0;
		start = s;
		for (size_t i = 0; i < len; i++) {
			if (start < ped[i].date) {
				temp[t++] = ped[i];
				count++;
			}
		}
		delete[] ped;
		ped = new Tally[t];
		memcpy(ped, temp, sizeof(Tally) * t);
		delete[] temp;
	}
	Date GetStart() {
		return start;
	}
	void SetTally(const Tally& t) {
		if (start > t.date) {
			throw  "Некоректные данные";
		}

		if (count >= len) {
			Tally* temp = new Tally[len * 2];
			memcpy(temp, ped, sizeof(Tally) * len);
			delete[] ped;
			ped = new Tally[len * 2];
			memcpy(ped, temp, sizeof(Tally) * len * 2);
			delete[] temp;
			len *= 2;
		}
		ped[count] = t;
		count++;

	}
	Tally& operator[](int c) {
		return ped[c];
	}
	const Tally& operator[](int c) const {
		return ped[c];
	}
	double Mean(int m) {
		double mean = 0.0;
		int c = 0;
		if (m == 0) {
			for (int i = 0; i < count; i++) {
				mean += ped[i].Getlen();
				c++;
			}
		}
		else {
			for (int i = 0; i < count; i++) {
				if (ped[i].date.Getmonth() == static_cast<Month>(m)) {
					mean += ped[i].Getlen();
					c++;
				}
			}
		}
		return mean / static_cast<double>(c);
	}
	const Tally& max(int m) {
		int max = 0;
		int c = 0;
		if (m == 0) {
			for (int i = 0; i < count; i++) {
				if (ped[i].Getlen() > max) {
					max = ped[i].Getlen();
					c = i;
				}
			}
		}
		else {
			for (int i = 0; i < count; i++) {
				if (ped[i].date.Getmonth() == static_cast<Month>(m)) {
					if (ped[i].Getlen() > max) {
						max = ped[i].Getlen();
						c = i;
					}
				}
			}
		}
		return ped[c];
	}
	void Outfile() {
		std::ofstream ofs("Steps.txt");
		if (!ofs) {
			std::cerr << "Cannot open file for writing\n";
			return;
		}
		ofs << start << count << "\n" << std::endl;
		for (unsigned int i = 0; i < count; ++i) {
			ofs << ped[i] << std::endl;
		}
		ofs.close();
	}

	void Infile() {
		std::ifstream ifs("Steps.txt");
		if (!ifs) {
			std::cerr << "Cannot open file for reading\n";
			return;
		}
		ifs >> start;
		ifs >> count;
		delete[] ped;
		len = count + 1;
		ped = new Tally[len];
		for (unsigned int i = 0; i < count; ++i) {
			ifs >> ped[i];
		}
		ifs.close();
	}
	friend std::ostream& operator<<(std::ostream& os, const Pedometer& p) {
		os << p.start << "\n" << p.count << std::endl;
		for (unsigned int i = 0; i < p.count; ++i) {
			os << p.ped[i] << std::endl;
		}
		return os;
	}
	~Pedometer() {
		delete[] ped;
	}
};

int main() {
	Tally t;

	Pedometer a(Date(15, 10, 2006));
	for (int i = 0; i < 19; i++) {
		a.SetTally(Tally(Date(21, 10, 2007 + i), Time(8, 0), Time(22, 30), 200 + (rand() % (10000))));
	}
	a.Outfile();
	Pedometer b;
	b.Infile();
	std::cout << b << std::endl;
}