#include <iostream>
#include <windows.h>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <unordered_map>

namespace Language {
	std::unordered_map<std::string, std::string> patterns = {
		{ "eng", "[(A-z)|\-| ]+"},
		{ "rus", "[(А-я)|\-| ]+"},
	};
}

namespace RegexFunc {
	bool is_Lang(std::string word, std::string lang) {
		std::regex pattern(Language::patterns[lang]);
		return std::regex_match(word, pattern);
	}

	std::smatch matches_Lang(std::string word, std::string lang) {
		std::regex pattern(Language::patterns[lang]);
		std::smatch matches;

		std::regex_search(word, matches, pattern);

		return matches;
	}
}

class TranslationDict {
private:
	size_t size = 0;
	std::vector<std::pair<std::string, std::string>> dict = {};

	int Find(std::string word, bool which) const {
		if (which == false) {
			for (unsigned i = 0; i < size; i++) {
				if (dict[i].first == word) { return i; }
			}
		}
		else {
			for (unsigned i = 0; i < size; i++) {
				if (dict[i].second == word) { return i; }
			}
		}
		return -1;
	}
public:
	TranslationDict() {}
	TranslationDict(std::initializer_list<std::pair<std::string, std::string>> list) {
		dict = list;
		size = dict.size();
	}
	TranslationDict(const TranslationDict& arr) {
		dict = arr.dict;
		size = dict.size();
	}
	~TranslationDict() {}

	std::string Get(std::string word) const {
		if (RegexFunc::is_Lang(word, "eng")) {
			int where = Find(word, false);

			if (where == -1) {
				return "Word not found";
			}
			else {
				return dict[where].second;
			}
		}
		else if (RegexFunc::is_Lang(word, "rus")) {
			int where = Find(word, true);

			if (where == -1) {
				return "Word not found";
			}
			else {
				return dict[where].first;
			}
		}
		else {
			return "Strange target word";
		}
	}

	bool Contains(std::string word) const {
		if (RegexFunc::is_Lang(word, "eng")) {
			int where = Find(word, false);

			if (where == -1) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (RegexFunc::is_Lang(word, "rus")) {
			int where = Find(word, true);

			if (where == -1) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}

	unsigned Size() const {
		return size;
	}

	TranslationDict Add(std::string eng, std::string rus) {
		if (RegexFunc::is_Lang(eng, "eng") && RegexFunc::is_Lang(rus, "rus")) {
			dict.push_back({eng, rus});
			size++;
		}
		else {
			throw std::exception("Language not supported");
		}

		return *this;
	}

	TranslationDict Modify(std::string word, std::string translation) {
		if (RegexFunc::is_Lang(word, "eng")) {
			int where = Find(word, false);

			if ((where == -1) || !(RegexFunc::is_Lang(translation, "rus"))) {
				return *this;
			}
			else {
				dict[where].second = translation;
				return *this;
			}
		}
		else if (RegexFunc::is_Lang(word, "rus")) {
			int where = Find(word, true);

			if ((where == -1) || !(RegexFunc::is_Lang(translation, "eng"))) {
				return *this;
			}
			else {
				dict[where].first = translation;
				return *this;
			}
		}
		else {
			return *this;
		}
	}

	TranslationDict Delete(std::string word) {
		if (RegexFunc::is_Lang(word, "eng")) {
			int where = Find(word, false);

			if (where == -1) {
				return *this;
			}
			else {
				dict.erase(dict.begin() + where);
				size--;
				return *this;
			}
		}
		else if (RegexFunc::is_Lang(word, "rus")) {
			int where = Find(word, true);

			if (where == -1) {
				return *this;
			}
			else {
				dict.erase(dict.begin() + where);
				size--;
				return *this;
			}
		}
		else {
			return *this;
		}
	}

	std::string to_string() const {
		std::string str = "[";
		if (size > 0) {
			str += "{" + dict[0].first + ", " + dict[0].second + "}";

			for (unsigned i = 1; i < size; i++) {
				str += ", {" + dict[i].first + ", " + dict[i].second + "}";
			}
		}
		str += "]";

		return str;
	}

	void Save(std::string where) const {
		std::ofstream file(where);

		if (!file.is_open()) { throw std::exception("Something went wrong"); }

		file << "{" << std::endl;
		if (size > 0) {
			file << "\t{" + dict[0].first + ", " + dict[0].second + "}," << std::endl;

			for (unsigned i = 1; i < size; i++) {
				file << "\t{" + dict[i].first + ", " + dict[i].second + "}," << std::endl;
			}
		}
		file << "}" << std::endl;

		file.close();
	}

	void Load(std::string where) {
		std::ifstream file(where);

		if (!file.is_open()) { throw std::exception("Something went wrong"); }

		dict.clear();
		size = 0;
		std::string line;

		while (std::getline(file, line)) {
			if (line[0] == '\t') {
				std::smatch eng_matches = RegexFunc::matches_Lang(line, "eng");
				std::smatch rus_matches = RegexFunc::matches_Lang(line, "rus");

				if (!eng_matches.empty() && !rus_matches.empty()) {
					std::string eng = rus_matches[0];
					std::string rus = rus_matches[0];

					dict.push_back({ eng_matches[0], rus_matches[0]});
					size++;
				}
			}
		}

		file.close();
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	TranslationDict dict{
		{"chair", "стул"},
		{"table", "стол"},
		{"cup", "кружка"},
	};

	std::cout << "chair: " << dict.Get("chair") << " стул: " << dict.Get("стул") << std::endl;

	try {
		dict.Add("ап", "вилка");
	}
	catch (std::exception ex) { std::cout << ex.what() << std::endl; }

	dict.Add("fork", "вилка");
	std::cout << dict.to_string() << std::endl;
	dict.Modify("fork", "ложка");
	std::cout << dict.to_string() << std::endl;
	dict.Delete("ложка");
	std::cout << dict.to_string() << std::endl;

	dict.Save("dictionary.txt");
	dict.Delete("cup");
	std::cout << dict.to_string() << std::endl;
	dict.Load("dictionary.txt");
	std::cout << dict.to_string() << std::endl;

	getchar();
}
