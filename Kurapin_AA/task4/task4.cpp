#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
#include <map>
#include <unordered_map>
#include <variant>
#include <functional>
#include <algorithm>
#include <fstream>


class Movie {
private:
	using TypeNameRange = std::variant<std::string, unsigned, std::chrono::year_month_day>;

	std::string name;
	std::string director;
	std::string scriptwriter;
	std::string composer;
	std::chrono::year_month_day date;
	unsigned box_office;

	static const std::unordered_map<std::string, std::function<TypeNameRange(const Movie&)>>& Field_Getters() {
		static std::unordered_map<std::string, std::function<TypeNameRange(const Movie&)>> fields = {
			{ "name", [](const Movie& movie) -> TypeNameRange { return movie.name; } },
			{ "director", [](const Movie& movie) -> TypeNameRange { return movie.director; } },
			{ "scriptwriter", [](const Movie& movie) -> TypeNameRange { return movie.scriptwriter; } },
			{ "composer", [](const Movie& movie) -> TypeNameRange { return movie.composer; } },
			{ "date", [](const Movie& movie) -> TypeNameRange { return movie.date; } },
			{ "box office", [](const Movie& movie) -> TypeNameRange { return movie.box_office; } },
		};
		return fields;
	}

	static const std::unordered_map<std::string, std::function<void(Movie&, TypeNameRange)>>& Field_Setters() {
		static std::unordered_map<std::string, std::function<void(Movie&, TypeNameRange)>> fields = {
			{ "name", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<std::string>(value)) movie.name = std::get<std::string>(value); }},
			{ "director", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<std::string>(value)) movie.director = std::get<std::string>(value); } },
			{ "scriptwriter", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<std::string>(value)) movie.scriptwriter = std::get<std::string>(value); } },
			{ "composer", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<std::string>(value)) movie.composer = std::get<std::string>(value); } },
			{ "date", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<std::chrono::year_month_day>(value)) movie.date = std::get<std::chrono::year_month_day>(value); } },
			{ "box office", [](Movie& movie, TypeNameRange value) { if (std::holds_alternative<unsigned>(value)) movie.box_office = std::get<unsigned>(value); } },
		};
		return fields;
	}

public:
	Movie(std::string name_t,
		std::string director_t,
		std::string scriptwriter_t,	
		std::string composer_t,
		int year, unsigned month, unsigned day,
		unsigned box_office_t)
		: name(name_t), director(director_t), scriptwriter(scriptwriter_t),
		composer(composer_t), box_office(box_office_t),
		date(std::chrono::year_month_day{
				std::chrono::year{year},
				std::chrono::month{month},
				std::chrono::day{day}
			})
	{}
	Movie() {
		name = "";
		director = "";
		scriptwriter = "";
		composer = "";
		date = std::chrono::year_month_day();
		box_office = 0;
	}

	bool operator< (const Movie& other) const {
		if (name != other.name) {
			return name < other.name;
		}
		return date < other.date;
	}

	TypeNameRange Value(std::string field) const { return Field_Getters().at(field)(*this); }

	using TypeNameRange_ = TypeNameRange;

	bool Matches(std::string field, TypeNameRange value) const { // почему в cpp нет string.ToLower???
		if (!Field_Getters().contains(field)) return false;

		TypeNameRange current = Value(field);

		if (current.index() != value.index()) return false;

		return current == value;
	}

	bool Greater(std::string field, TypeNameRange value) const {
		if (!Field_Getters().contains(field)) return false;

		TypeNameRange current = Value(field);

		if (current.index() != value.index()) return false;

		if (current.index() == 0) return std::get<0>(current) > std::get<0>(value);
		if (current.index() == 1) return std::get<1>(current) > std::get<1>(value);
		return std::get<2>(current) > std::get<2>(value);
	}

	bool Less(std::string field, TypeNameRange value) const {
		if (!Field_Getters().contains(field)) return false;

		TypeNameRange current = Value(field);

		if (current.index() != value.index()) return false;

		if (current.index() == 0) return std::get<0>(current) < std::get<0>(value);
		if (current.index() == 1) return std::get<1>(current) < std::get<1>(value);
		return std::get<2>(current) < std::get<2>(value);
	}

	Movie& Change(std::string field, TypeNameRange value) {
		if (!Field_Getters().contains(field)) return *this;

		if (Value(field).index() != value.index()) return *this;
		
		Field_Setters().at(field)(*this, value);

		return *this;
	}

	std::string to_string() const {
		return std::get<std::string>(Value("name")) + ":\n"
			"Дата выхода: " + std::format("{}", std::get<std::chrono::year_month_day>(Value("date")))
			+ "\nРежиссер: " + std::get<std::string>(Value("director"))
			+ "\nСценарист: " + std::get<std::string>(Value("scriptwriter"))
			+ "\nКомпозитор: " + std::get<std::string>(Value("composer"))
			+ "\nСборы: " + std::to_string(std::get<unsigned>(Value("box office"))) + "\n";
	}
};

class MovieLibrary {
private:
	std::map<std::pair<std::string, std::chrono::year_month_day>, Movie> library;

	std::vector<Movie> CompareBy(std::vector<Movie> source, std::string field, size_t number, bool max) const {
		if (number >= source.size()) return source;

		std::partial_sort(source.begin(), source.begin() + number, source.end(),
			[max, field](const Movie& a, const Movie& b) {
				if (max == true) return a.Greater(field, b.Value(field));
				else return a.Less(field, b.Value(field));
			});

		return std::vector<Movie>(source.begin(), source.begin() + number);
	}
public:
	MovieLibrary (std::initializer_list<Movie> list) {
		for (const auto& movie : list) {
			library[{std::get<std::string>(movie.Value("name")), std::get<std::chrono::year_month_day>(movie.Value("date"))}] = movie;
		}
	}

	std::vector<Movie> Find(std::string field, Movie::TypeNameRange_ value) const {
		std::vector<Movie> results;

		for (const auto& [key, movie] : library) {
			if (movie.Matches(field, value)) { results.push_back(movie); }
		}

		return results;
	}

	std::vector<Movie> Find(std::string field1, Movie::TypeNameRange_ value1, std::string field2, Movie::TypeNameRange_ value2) const {
		std::vector<Movie> results;

		for (const auto& [key, movie] : library) {
			if (movie.Matches(field1, value1) && movie.Matches(field2, value2)) { results.push_back(movie); }
		}

		return results;
	}

	void Add(Movie movie) { library[std::pair(std::get<std::string>(movie.Value("name")), std::get<std::chrono::year_month_day>(movie.Value("date")))] = movie; }
	void Remove(std::string name) {
		std::vector<Movie> targets = Find("name", name);

		for (const auto& movie : targets) {
			library.erase(std::pair{ std::get<std::string>(movie.Value("name")), std::get<std::chrono::year_month_day>(movie.Value("date")) });
		}
	}
	void Remove(std::string name, std::chrono::year_month_day date) {
		std::vector<Movie> targets = Find("name", name, "date", date);

		for (const auto& movie : targets) {
			library.erase(std::pair{ std::get<std::string>(movie.Value("name")), std::get<std::chrono::year_month_day>(movie.Value("date")) });
		}
	}
	MovieLibrary& ChangeMovie(std::string name, std::chrono::year_month_day date, std::string field_to_change, Movie::TypeNameRange_ new_value) {
		std::vector<Movie> targets = Find("name", name, "date", date);

		for (const auto& movie : targets) {
			library[std::pair{ std::get<std::string>(movie.Value("name")), std::get<std::chrono::year_month_day>(movie.Value("date")) }].Change(field_to_change, new_value);
		}

		return *this;
	}

	size_t Size() const { return library.size(); }

	std::vector<Movie> GetMost(std::string field, size_t number, bool max) const {
		std::vector<Movie> vector_lib;
		for (const auto& [key, movie] : library) {
			vector_lib.push_back(movie);
		}

		return CompareBy(vector_lib, field, number, max);
	}

	std::vector<Movie> GetMost(std::string field1, Movie::TypeNameRange_ value1, std::string field, size_t number, bool max) const {
		return CompareBy(Find(field1, value1), field, number, max);
	}

	std::vector<Movie> GetMost(std::string field1, Movie::TypeNameRange_ value1, std::string field2, Movie::TypeNameRange_ value2, std::string field, size_t number, bool max) const {
		return CompareBy(Find(field1, value1, field2, value2), field, number, max);
	}

	std::string to_string() const {
		std::string result = "Фильмотека:\n";
		size_t count = 1;

		for (const auto& [key, movie] : library) {
			result += count + ") " + movie.to_string() + "\n";
			count++;
		}

		return result;
	}

	void Save(std::string where) const {
		std::ofstream file(where);

		if (!file.is_open()) { throw std::exception("Something went wrong"); }

		if (Size() > 0) {
			for (const auto& [key, movie] : library) {
				file << std::get<std::string>(movie.Value("name")) << "|"
					<< std::get<std::string>(movie.Value("director")) << "|"
					<< std::get<std::string>(movie.Value("scriptwriter")) << "|"
					<< std::get<std::string>(movie.Value("composer")) << "|"
					<< std::get<std::chrono::year_month_day>(movie.Value("date")) << "|"
					<< std::get<unsigned>(movie.Value("box office")) << std::endl;
			}
		}

		file.close();
	}

	void Load(std::string where) {
		std::ifstream file(where);

		if (!file.is_open()) { throw std::exception("Something went wrong"); }

		library.clear();
		std::string line;
		std::string name, director, scriptwriter, composer, date, box_office;

		while (std::getline(file, line)) {
			std::stringstream stream(line);

			std::getline(stream, name, '|');
			std::getline(stream, director, '|');
			std::getline(stream, scriptwriter, '|');
			std::getline(stream, composer, '|');
			std::getline(stream, date, '|');
			std::getline(stream, box_office, '|');

			int year;
			unsigned month, day;
			char dash1, dash2;
			std::stringstream date_stream(date);
			date_stream >> year >> dash1 >> month >> dash2 >> day;

			Movie movie = Movie(name, director, scriptwriter, composer, year, month, day, static_cast<unsigned>(std::stoi(box_office)));

			Add(movie);
		}

		file.close();
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Movie a = Movie("name", "director", "scriptwriter", "composer", 2000, 11, 13, 600);
	Movie b = Movie("Anton", "Evgeniy", "Timofey", "Arseniy", 2001, 12, 9, 6002);
	Movie c = Movie("Roman", "Dmirty", "Pepega", "Michail", 2001, 12, 9, 58229);

	MovieLibrary ml = { a, b, c };

	std::cout << ml.to_string() << std::endl;
	std::cout << ml.Size() << std::endl;

	ml.Add(Movie("1", "2", "3", "4", 5, 6, 7, 8));
	std::cout << ml.to_string() << std::endl;

	ml.ChangeMovie("1", std::chrono::year_month_day{ std::chrono::year{5}, std::chrono::month{6}, std::chrono::day{7} }, "composer", "anton");
	std::cout << ml.to_string() << std::endl;

	ml.Remove("1");
	std::cout << ml.to_string() << std::endl;

	std::vector<Movie> movies = ml.Find("director", "Evgeniy");
	for (const auto& movie : movies) {
		std::cout << movie.to_string() << std::endl;
	}

	std::vector<Movie> movies2 = ml.GetMost("date", std::chrono::year_month_day{ std::chrono::year{2001}, std::chrono::month{12}, std::chrono::day{9} }, "box office", 2, true);
	for (const auto& movie : movies2) {
		std::cout << movie.to_string() << std::endl;
	}

	ml.Save("save.txt");

	ml.ChangeMovie("1", std::chrono::year_month_day{ std::chrono::year{5}, std::chrono::month{6}, std::chrono::day{7} }, "composer", "anton");
	std::cout << ml.to_string() << std::endl;

	ml.Load("save.txt");
	std::cout << ml.to_string() << std::endl;

	getchar();
}
