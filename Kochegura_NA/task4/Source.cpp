#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    string toString() const {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }

    static Date fromString(const string& str) {
        Date d;
        char dot;
        stringstream ss(str);
        ss >> d.day >> dot >> d.month >> dot >> d.year;
        return d;
    }

    bool isValid() const {
        if (year < 1900 || year > 2026) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeap ? 29 : 28)) return false;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        }
        return true;
    }
};

struct Song {
    string title;
    string author;
    string composer;
    string performer;
    string album;
    Date releaseDate;

    Song() {}

    Song(string t, string a, string c, string perf, string alb, Date d)
        : title(t), author(a), composer(c), performer(perf), album(alb), releaseDate(d) {
    }

    void print() const {
        cout << "----------------------------------------" << endl;
        cout << "Title:        " << title << endl;
        cout << "Author:       " << author << endl;
        cout << "Composer:     " << composer << endl;
        cout << "Performer:    " << performer << endl;
        cout << "Album:        " << (album.empty() ? "—" : album) << endl;
        cout << "Release date: " << releaseDate.toString() << endl;
        cout << "----------------------------------------" << endl;
    }

    bool operator<(const Song& other) const {
        return title < other.title;
    }
};

class Songbook {
private:
    vector<Song> songs;

    int findIndex(const string& title, const string& performer) const {
        for (size_t i = 0; i < songs.size(); ++i) {
            if (songs[i].title == title && songs[i].performer == performer) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void sortSongs() {
        sort(songs.begin(), songs.end());
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void addSong() {
        string title, author, composer, performer, album;
        int day, month, year;

        clearInputBuffer();

        getline(cin, title);

        if (title.empty()) {
            return;
        }

        getline(cin, author);
;
        getline(cin, composer);

        getline(cin, performer);

        getline(cin, album);

        cin >> day >> month >> year;

        Date date = { day, month, year };

        if (!date.isValid()) {
            clearInputBuffer();
            return;
        }

        Song newSong(title, author, composer, performer, album, date);
        songs.push_back(newSong);
        sortSongs();

    }

    void editSong() {
        string title, performer;

        clearInputBuffer();

        getline(cin, title);
        getline(cin, performer);

        int index = findIndex(title, performer);
        if (index == -1) {
            return;
        }

        Song& s = songs[index];
        s.print();


        string input;

        getline(cin, input);
        if (!input.empty()) s.title = input;

        getline(cin, input);
        if (!input.empty()) s.author = input;

        getline(cin, input);
        if (!input.empty()) s.composer = input;

        getline(cin, input);
        if (!input.empty()) s.performer = input;

        getline(cin, input);
        if (!input.empty()) s.album = input;

        int d, m, y;
        cin >> d >> m >> y;

        if (d != 0 || m != 0 || y != 0) {
            Date newDate = { d, m, y };
            if (newDate.isValid()) {
                s.releaseDate = newDate;
            }
            else {
            }
        }

        clearInputBuffer();

        sortSongs();
    }

    void findSong() const {
        string title, performer;

        const_cast<Songbook*>(this)->clearInputBuffer();

        getline(cin, title);
        getline(cin, performer);

        int index = findIndex(title, performer);
        if (index == -1) {
        }
        else {
            songs[index].print();
        }
    }

    void getSongsByAuthor() const {
        string author;

        const_cast<Songbook*>(this)->clearInputBuffer();

        getline(cin, author);

        bool found = false;
        for (const auto& song : songs) {
            if (song.author == author) {
                song.print();
                found = true;
            }
        }
        if (!found) {
        }
    }

    void getSongsByComposer() const {
        string composer;

        const_cast<Songbook*>(this)->clearInputBuffer();

        getline(cin, composer);

        bool found = false;
        for (const auto& song : songs) {
            if (song.composer == composer) {
                song.print();
                found = true;
            }
        }
        if (!found) {
        }
    }

    void getSongsByPerformer() const {
        string performer;

        const_cast<Songbook*>(this)->clearInputBuffer();

        getline(cin, performer);

        bool found = false;
        for (const auto& song : songs) {
            if (song.performer == performer) {
                song.print();
                found = true;
            }
        }
        if (!found) {
        }
    }

    int getSongCount() const {
        return songs.size();
    }

    void deleteSong() {
        string title, performer;

        clearInputBuffer();

        getline(cin, title);
        getline(cin, performer);

        int index = findIndex(title, performer);
        if (index == -1) {
        }
        else {
            songs.erase(songs.begin() + index);
        }
    }

    bool saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out.is_open()) {
            return false;
        }

        out << songs.size() << endl;
        for (const auto& song : songs) {
            out << song.title << endl;
            out << song.author << endl;
            out << song.composer << endl;
            out << song.performer << endl;
            out << song.album << endl;
            out << song.releaseDate.day << " " << song.releaseDate.month << " " << song.releaseDate.year << endl;
        }

        out.close();
        return true;
    }

    bool loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in.is_open()) {
            return false;
        }

        songs.clear();
        int count;
        in >> count;

        if (count < 0) {
            in.close();
            return false;
        }

        in.ignore();

        for (int i = 0; i < count; ++i) {
            string title, author, composer, performer, album;
            int day, month, year;

            if (!getline(in, title)) break;
            if (!getline(in, author)) break;
            if (!getline(in, composer)) break;
            if (!getline(in, performer)) break;
            if (!getline(in, album)) break;

            in >> day >> month >> year;
            in.ignore();

            Date date = { day, month, year };
            if (!date.isValid()) {
                continue;
            }

            Song newSong(title, author, composer, performer, album, date);
            songs.push_back(newSong);
        }

        sortSongs();
        in.close();
        return true;
    }

    void showAllSongs() const {
        if (songs.empty()) {
            return;
        }
        for (const auto& song : songs) {
            song.print();
        }
    }
};

void showMenu() {
    cout << "\n========== SONGBOOK MENU ==========" << endl;
    cout << "1. Add a song" << endl;
    cout << "2. Edit song data" << endl;
    cout << "3. Find song by title and performer" << endl;
    cout << "4. Show all songs by given author" << endl;
    cout << "5. Show all songs by given composer" << endl;
    cout << "6. Show all songs by given performer" << endl;
    cout << "7. Get number of songs" << endl;
    cout << "8. Delete a song" << endl;
    cout << "9. Save songbook to file" << endl;
    cout << "10. Load songbook from file" << endl;
    cout << "11. Show all songs (for verification)" << endl;
    cout << "0. Exit" << endl;
    cout << "====================================" << endl;
    cout << "Your choice: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Songbook mySongbook;
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input error! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            mySongbook.addSong();
            break;
        case 2:
            mySongbook.editSong();
            break;
        case 3:
            mySongbook.findSong();
            break;
        case 4:
            mySongbook.getSongsByAuthor();
            break;
        case 5:
            mySongbook.getSongsByComposer();
            break;
        case 6:
            mySongbook.getSongsByPerformer();
            break;
        case 7:
            cout << "Number of songs in songbook: " << mySongbook.getSongCount() << endl;
            break;
        case 8:
            mySongbook.deleteSong();
            break;
        case 9: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            mySongbook.saveToFile(filename);
            break;
        }
        case 10: {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            mySongbook.loadFromFile(filename);
            break;
        }
        case 11:
            mySongbook.showAllSongs();
            break;
        case 0:
            cout << "Exit!" << endl;
            break;
        default:
            cout << "Wrong choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}