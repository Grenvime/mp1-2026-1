#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct Song {
    string title;
    string poet;
    string composer;
    string performer;
    string album;
    int day, month, year;   

    bool operator<(const Song& other) const {
        if (title == other.title)
            return performer < other.performer;
        return title < other.title;
    }

};

class Songbook {

private:

    set<Song> songs;

public:

    Songbook() = default;

    bool addSong(const string& title, const string& poet, const string& composer,
        const string& performer, const string& album,
        int day, int month, int year) {
        Song s{ title, poet, composer, performer, album, day, month, year };
        return songs.insert(s).second;
    }

    bool updateSong(const string& oldTitle, const string& oldPerformer,
        const string& newTitle, const string& newPoet,
        const string& newComposer, const string& newPerformer,
        const string& newAlbum, int day, int month, int year) {
        Song oldKey{ oldTitle, "", "", oldPerformer, "", 0,0,0 };
        auto it = songs.find(oldKey);
        if (it == songs.end()) return false;

        songs.erase(it);
        return addSong(newTitle, newPoet, newComposer, newPerformer, newAlbum, day, month, year);
    }

    const Song* findSong(const string& title, const string& performer) const {
        Song key{ title, "", "", performer, "", 0,0,0 };
        auto it = songs.find(key);
        if (it != songs.end())
            return &(*it);
        return nullptr;
    }

    vector<Song> getSongsByPoet(const string& poet) const {
        vector<Song> result;
        for (const auto& s : songs)
            if (s.poet == poet) result.push_back(s);
        return result;
    }

    vector<Song> getSongsByComposer(const string& composer) const {
        vector<Song> result;
        for (const auto& s : songs)
            if (s.composer == composer) result.push_back(s);
        return result;
    }

    vector<Song> getSongsByPerformer(const string& performer) const {
        vector<Song> result;
        for (const auto& s : songs)
            if (s.performer == performer) result.push_back(s);
        return result;
    }

    size_t getSongCount() const {
        return songs.size();
    }

    bool removeSong(const string& title, const string& performer) {
        Song key{ title, "", "", performer, "", 0,0,0 };
        return songs.erase(key) > 0;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) return;
        for (const auto& s : songs) {
            file << s.title << '|';
            file << s.poet << '|';
            file << s.composer << '|';
            file << s.performer << '|';
            file << (s.album.empty() ? "N/A" : s.album) << '|';
            file << s.day << '|';
            file << s.month << '|';
            file << s.year << '\n';
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) return;

        songs.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            istringstream iss(line);
            string title, poet, composer, performer, album;
            string dayStr, monthStr, yearStr;

            getline(iss, title, '|');
            getline(iss, poet, '|');
            getline(iss, composer, '|');
            getline(iss, performer, '|');
            getline(iss, album, '|');
            getline(iss, dayStr, '|');
            getline(iss, monthStr, '|');
            getline(iss, yearStr);

            if (album == "N/A") album.clear();
            int day = stoi(dayStr);
            int month = stoi(monthStr);
            int year = stoi(yearStr);

            songs.insert({ title, poet, composer, performer, album, day, month, year });
        }
    }
};

int main() {
}
