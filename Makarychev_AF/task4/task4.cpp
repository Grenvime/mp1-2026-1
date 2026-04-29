#include <iostream>
#include <fstream>
#include <Vector>
#include <string>
#include <algorithm>
#include <stdexcept> 

using std::string;
using std::vector;

class film {
	private:
		string title;
		string direct;
		string writer;
		string composer;
		short day;
		short mon;
		unsigned short year;
		unsigned long long money;
	public:
		film(string t = "-", string d = "-", string w = "-", string c = "-", short days = 1, short month = 1, unsigned short y = 1895, unsigned long long m = 0) :
			title(t), direct(d), writer(w), composer(c), day(days), mon(month), year(y), money(m) {
		};
		bool operator>(const film& f) { 
			if (title > f.title) {
				return true;
			}
			if ((title == f.title)&&(year < f.year)) {
				return true;
			}
			return false;
		}
		bool operator<(const film& f) {
			if (title < f.title) {
				return true;
			}
			if ((title == f.title) && (year > f.year)) {
				return true;
			}
			return false;
		}
		bool operator==(const film& f) {
			if ((title == f.title) && (year == f.year)) {
				return true;
			}
			return false;
		}
		friend bool sort(const film& f1, const film& f2) {
			return f1.year > f2.year;
		}
		string& GetDirect()  {
			return direct;
		}
		unsigned short& GetYear() {
			return year;
		}
		friend std::ostream& operator<<(std::ostream& os, const film& t) {
			os << t.title << "\t" << t.direct << "\t" << t.writer << '\t' << t.composer << '\t' << t.day << '\t' << t.mon << '\t' << t.year << '\t' << t.money << std::endl;
			return os;
		}
		friend std::istream& operator>>(std::istream& is, film& t) {
			is >> t.title >> t.direct >> t.writer >> t.composer >> t.day >> t.mon >> t.year >> t.money;
			return is;
		}

};

class FilmLibary {
	private:
	vector<film> lib;
	public:
		FilmLibary() {
			lib.resize(1, film());
		}
		void Add(const film& f) {
			lib.emplace_back(f);
			std::sort(begin(lib), end(lib));
		}
		film& find(string& const tit,unsigned short y ) {
			film target(tit, "", "", "", 1, 1, y, 0);
			for (auto& f : lib) {
				if (target == f) {
					return f;
				}
			}
			throw std::runtime_error("Film not found");
		}
		vector<film> Direct(string& const d) {
			vector<film> res;
			for (auto& f : lib) {
				if (f.GetDirect() == d) {
					res.push_back(f);
				}
			}
			return res;
		}
		vector<film> Years(unsigned short& const y) {
			vector<film> res;
			for (auto& f : lib) {
				if (f.GetYear() == y) {
					res.push_back(f);
				}
			}
			return res;
		}
		vector<film> MoneyTop(const int& a) {
			vector<film> temp(lib);
			vector<film> res;
			std::sort(begin(temp), end(temp),sort);
			for (int i = 0; i < a; i++) {
				res.push_back(temp[i]);
			}
			return res;
		}
		vector<film> MoneyTopYear(const int& a, unsigned short& const y) {
			vector<film> temp(Years(y));
			vector<film> res;
			std::sort(begin(temp), end(temp), sort);
			for (int i = 0; i < a; i++) {
				res.push_back(temp[i]);
			}
			return res;
		}
		int Len() {
			return lib.size();
		}
		void del(const film& f) {
			int t=0, i;
			for (auto& fil : lib) {
				if (fil==f) {
					t = i;
				}
				i++;
			}
			lib.erase(lib.cbegin() + t);
		}
		void Outfile() {
			std::ofstream ofs("Films.txt");
			if (!ofs) {
				std::cerr << "Cannot open file for writing\n";
				return;
			}
			ofs  << lib.size() << "\n" << std::endl;
			for (unsigned int i = 0; i < lib.size(); ++i) {
				ofs << lib[i] << std::endl;
			}
			ofs.close();
		}

		void Infile() {
			std::ifstream ifs("Films.txt");
			int count;
			if (!ifs) {
				std::cerr << "Cannot open file for reading\n";
				return;
			}
			ifs >> count;
			lib = vector <film> (count);
			for (unsigned int i = 0; i < count; ++i) {
				ifs >> lib[i];
			}
			ifs.close();
		}
};
void main(){

}

