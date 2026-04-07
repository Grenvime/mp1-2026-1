#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    string toString() const {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

struct Film {
    string title;
    string director;
    string screenwriter;
    string composer;
    Date releaseDate;
    double earnings;

    Film() : earnings(0) {}

    Film(string t, string d, string sw, string c, Date rd, double e)
        : title(t), director(d), screenwriter(sw), composer(c), releaseDate(rd), earnings(e) {
    }

    bool operator<(const Film& other) const {
        if (title != other.title) return title < other.title;
        return releaseDate.year < other.releaseDate.year;
    }

    string toFileString() const {
        stringstream ss;
        ss << title << "\n" << director << "\n" << screenwriter << "\n" << composer << "\n"
            << releaseDate.day << " " << releaseDate.month << " " << releaseDate.year << "\n"
            << earnings << "\n";
        return ss.str();
    }
};

class Filmoteka {
private:
    vector<Film> films;

    int findFilmIndex(const string& title, int year) const {
        for (size_t i = 0; i < films.size(); i++) {
            if (films[i].title == title && films[i].releaseDate.year == year) {
                return i;
            }
        }
        return -1;
    }

    void sortFilms() {
        sort(films.begin(), films.end());
    }

public:
    Filmoteka() {}
    Filmoteka(const Filmoteka& other) : films(other.films) {}
    ~Filmoteka() {}
    void addFilm(const string& title, const string& director, const string& screenwriter,
        const string& composer, int day, int month, int year, double earnings) {
        Film newFilm(title, director, screenwriter, composer, Date(day, month, year), earnings);
        films.push_back(newFilm);
        sortFilms();
    }
    bool editFilm(const string& title, int year, const string& newTitle,
        const string& newDirector, const string& newScreenwriter,
        const string& newComposer, int newDay, int newMonth,
        int newYear, double newEarnings) {
        int index = findFilmIndex(title, year);
        if (index == -1) return false;

        Film& film = films[index];
        if (!newTitle.empty()) {
            film.title = newTitle;
        }
        if (!newDirector.empty()) {
            film.director = newDirector;
        }
        if (!newScreenwriter.empty()) {
            film.screenwriter = newScreenwriter;
        }
        if (!newComposer.empty()) {
            film.composer = newComposer;
        }
        if (newDay > 0) {
            film.releaseDate.day = newDay;
        }
        if (newMonth > 0) {
            film.releaseDate.month = newMonth;
        }
        if (newYear > 0) {
            film.releaseDate.year = newYear;
        }
        if (newEarnings >= 0) {
            film.earnings = newEarnings;
        }
        sortFilms();
        return true;
    }

    bool findFilm(const string& title, int year, Film& result) const {
        int index = findFilmIndex(title, year);
        if (index == -1) return false;
        result = films[index];
        return true;
    }

    vector<Film> getFilmsByDirector(const string& director) const {
        vector<Film> result;
        for (const auto& film : films) {
            if (film.director == director) {
                result.push_back(film);
            }
        }
        return result;
    }

    vector<Film> getFilmsByYear(int year) const {
        vector<Film> result;
        for (const auto& film : films) {
            if (film.releaseDate.year == year) {
                result.push_back(film);
            }
        }
        return result;
    }

    vector<Film> getTopEarnings(int count) const {
        vector<Film> sortedFilms = films;
        sort(sortedFilms.begin(), sortedFilms.end(),
            [](const Film& a, const Film& b) {
                return a.earnings > b.earnings;
            });

        int toShow = min(count, (int)sortedFilms.size());
        return vector<Film>(sortedFilms.begin(), sortedFilms.begin() + toShow);
    }

    vector<Film> getTopEarningsByYear(int year, int count) const {
        vector<Film> filteredFilms;
        for (const auto& film : films) {
            if (film.releaseDate.year == year) {
                filteredFilms.push_back(film);
            }
        }

        sort(filteredFilms.begin(), filteredFilms.end(),
            [](const Film& a, const Film& b) {
                return a.earnings > b.earnings;
            });

        int toShow = min(count, (int)filteredFilms.size());
        return vector<Film>(filteredFilms.begin(), filteredFilms.begin() + toShow);
    }

    int getFilmCount() const {
        return films.size();
    }

    bool deleteFilm(const string& title, int year) {
        int index = findFilmIndex(title, year);
        if (index == -1) return false;
        films.erase(films.begin() + index);
        return true;
    }

    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) return false;

        file << films.size() << "\n";
        for (const auto& film : films) {
            file << film.toFileString();
        }
        file.close();
        return true;
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        films.clear();
        int count;
        file >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Film film;
            getline(file, film.title);
            getline(file, film.director);
            getline(file, film.screenwriter);
            getline(file, film.composer);
            file >> film.releaseDate.day >> film.releaseDate.month >> film.releaseDate.year;
            file >> film.earnings;
            file.ignore();
            films.push_back(film);
        }
        sortFilms();
        file.close();
        return true;
    }

    const vector<Film>& getAllFilms() const {
        return films;
    }
};





void printFilm(const Film& film) {
    cout << "=====================================\n";
    cout << "Название: " << film.title << "\n";
    cout << "Режиссер: " << film.director << "\n";
    cout << "Сценарист: " << film.screenwriter << "\n";
    cout << "Композитор: " << film.composer << "\n";
    cout << "Дата выхода: " << film.releaseDate.toString() << "\n";
    cout << "Сборы: " << fixed << setprecision(2) << film.earnings << " руб.\n";
    cout << "=====================================\n";
}

void printFilms(const vector<Film>& films) {
    if (films.empty()) {
        cout << "Фильмы не найдены\n";
        return;
    }
    for (const auto& film : films) {
        printFilm(film);
    }
}

void showMenu() {
    cout << "\n=====================================\n";
    cout << "          ФИЛЬМОТЕКА - МЕНЮ\n";
    cout << "=====================================\n";
    cout << "1  - Добавить фильм\n";
    cout << "2  - Изменить данные выбранного фильма\n";
    cout << "3  - Найти фильм по названию и году\n";
    cout << "4  - Выдать все фильмы заданного режиссера\n";
    cout << "5  - Выдать все фильмы выбранного года\n";
    cout << "6  - Выдать N фильмов с наибольшими сборами\n";
    cout << "7  - Выдать N фильмов с наибольшими сборами в выбраном году\n";
    cout << "8  - Узнать текущее число фильмов\n";
    cout << "9  - Удалить фильм\n";
    cout << "10 - Сохранить фильмотеку в файл\n";
    cout << "11 - Считать фильмотеку из файла\n";
    cout << "12 - Показать все фильмы\n";
    cout << "0  - Выход\n";
    cout << "=====================================\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    Filmoteka filmoteka;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string title, director, screenwriter, composer;
            int day, month, year;
            double earnings;

            cout << "\n--- ДОБАВЛЕНИЕ ФИЛЬМА ---\n";
            cout << "Введите название: ";
            getline(cin, title);
            cout << "Введите режиссера: ";
            getline(cin, director);
            cout << "Введите сценариста: ";
            getline(cin, screenwriter);
            cout << "Введите композитора: ";
            getline(cin, composer);
            cout << "Введите день выхода: ";
            cin >> day;
            cout << "Введите месяц выхода: ";
            cin >> month;
            cout << "Введите год выхода: ";
            cin >> year;
            cout << "Введите сборы (в рублях): ";
            cin >> earnings;

            filmoteka.addFilm(title, director, screenwriter, composer, day, month, year, earnings);
            cout << "Фильм успешно добавлен!\n";
            break;
        }
        case 2: {
            string title, newTitle, newDirector, newScreenwriter, newComposer;
            int year, newDay = 0, newMonth = 0, newYear = 0;
            double newEarnings = -1;

            cout << "\n--- ИЗМЕНЕНИЕ ДАННЫХ ФИЛЬМА ---\n";
            cout << "Введите название фильма: ";
            getline(cin, title);
            cout << "Введите год выпуска: ";
            cin >> year;
            cin.ignore();

            Film oldFilm;
            if (!filmoteka.findFilm(title, year, oldFilm)) {
                cout << "Фильм не найден!\n";
                break;
            }

            cout << "\nТекущие данные фильма:\n";
            printFilm(oldFilm);

            cout << "\nВведите новые данные (0 или пустая строка - оставить без изменений):\n";

            cout << "Новое название (" << oldFilm.title << "): ";
            getline(cin, newTitle);

            cout << "Новый режиссер (" << oldFilm.director << "): ";
            getline(cin, newDirector);

            cout << "Новый сценарист (" << oldFilm.screenwriter << "): ";
            getline(cin, newScreenwriter);

            cout << "Новый композитор (" << oldFilm.composer << "): ";
            getline(cin, newComposer);

            cout << "Новый день выхода (" << oldFilm.releaseDate.day << "): ";
            cin >> newDay;

            cout << "Новый месяц выхода (" << oldFilm.releaseDate.month << "): ";
            cin >> newMonth;

            cout << "Новый год выхода (" << oldFilm.releaseDate.year << "): ";
            cin >> newYear;

            cout << "Новые сборы (" << oldFilm.earnings << "): ";
            cin >> newEarnings;

            filmoteka.editFilm(title, year, newTitle, newDirector, newScreenwriter,
                newComposer, newDay, newMonth, newYear, newEarnings);
            cout << "Данные фильма обновлены!\n";
            break;
        }
        case 3: {
            string title;
            int year;

            cout << "\n--- ПОИСК ФИЛЬМА ---\n";
            cout << "Введите название фильма: ";
            getline(cin, title);
            cout << "Введите год выпуска: ";
            cin >> year;

            Film foundFilm;
            if (filmoteka.findFilm(title, year, foundFilm)) {
                cout << "\nФильм найден:\n";
                printFilm(foundFilm);
            }
            else {
                cout << "Фильм не найден!\n";
            }
            break;
        }
        case 4: {
            string director;

            cout << "\n--- ФИЛЬМЫ РЕЖИССЕРА ---\n";
            cout << "Введите фамилию режиссера: ";
            getline(cin, director);

            vector<Film> result = filmoteka.getFilmsByDirector(director);
            printFilms(result);
            break;
        }
        case 5: {
            int year;

            cout << "\n--- ФИЛЬМЫ ГОДА ---\n";
            cout << "Введите год: ";
            cin >> year;

            vector<Film> result = filmoteka.getFilmsByYear(year);
            printFilms(result);
            break;
        }
        case 6: {
            int count;

            cout << "\n--- ТОП ФИЛЬМОВ ПО СБОРАМ ---\n";
            cout << "Введите количество фильмов: ";
            cin >> count;

            if (count <= 0) {
                cout << "Неверное количество!\n";
                break;
            }

            vector<Film> result = filmoteka.getTopEarnings(count);
            if (result.empty()) {
                cout << "В фильмотеке нет фильмов\n";
            }
            else {
                cout << "\nТоп " << result.size() << " фильмов по сборам:\n";
                for (size_t i = 0; i < result.size(); i++) {
                    cout << "\n" << i + 1 << " место:\n";
                    printFilm(result[i]);
                }
            }
            break;
        }
        case 7: {
            int year, count;

            cout << "\n--- ТОП ФИЛЬМОВ ПО СБОРАМ ЗА ГОД ---\n";
            cout << "Введите год: ";
            cin >> year;
            cout << "Введите количество фильмов: ";
            cin >> count;

            if (count <= 0) {
                cout << "Неверное количество!\n";
                break;
            }

            vector<Film> result = filmoteka.getTopEarningsByYear(year, count);
            if (result.empty()) {
                cout << "Нет фильмов за " << year << " год\n";
            }
            else {
                cout << "\nТоп " << result.size() << " фильмов за " << year << " год по сборам:\n";
                for (size_t i = 0; i < result.size(); i++) {
                    cout << "\n" << i + 1 << " место:\n";
                    printFilm(result[i]);
                }
            }
            break;
        }
        case 8: {
            cout << "\n--- КОЛИЧЕСТВО ФИЛЬМОВ ---\n";
            cout << "В фильмотеке " << filmoteka.getFilmCount() << " фильмов\n";
            break;
        }
        case 9: {
            string title;
            int year;

            cout << "\n--- УДАЛЕНИЕ ФИЛЬМА ---\n";
            cout << "Введите название фильма: ";
            getline(cin, title);
            cout << "Введите год выпуска: ";
            cin >> year;

            if (filmoteka.deleteFilm(title, year)) {
                cout << "Фильм удален!\n";
            }
            else {
                cout << "Фильм не найден!\n";
            }
            break;
        }
        case 10: {
            string filename;

            cout << "\n--- СОХРАНЕНИЕ В ФАЙЛ ---\n";
            cout << "Введите имя файла: ";
            cin >> filename;

            if (filmoteka.saveToFile(filename)) {
                cout << "Фильмотека сохранена в файл " << filename << "\n";
            }
            else {
                cout << "Ошибка: не удалось сохранить файл\n";
            }
            break;
        }
        case 11: {
            string filename;

            cout << "\n--- ЗАГРУЗКА ИЗ ФАЙЛА ---\n";
            cout << "Введите имя файла: ";
            cin >> filename;

            if (filmoteka.loadFromFile(filename)) {
                cout << "Фильмотека загружена из файла " << filename << "\n";
                cout << "Загружено фильмов: " << filmoteka.getFilmCount() << "\n";
            }
            else {
                cout << "Ошибка: не удалось открыть файл\n";
            }
            break;
        }
        case 12: {
            const vector<Film>& allFilms = filmoteka.getAllFilms();
            if (allFilms.empty()) {
                cout << "Фильмотека пуста\n";
            }
            else {
                cout << "\n=== ВСЕ ФИЛЬМЫ ===\n";
                printFilms(allFilms);
            }
            break;
        }
        case 0:
            cout << "До свидания!\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}