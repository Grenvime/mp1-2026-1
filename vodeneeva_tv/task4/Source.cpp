#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Date {
    int day, month, year;
    Date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {

    }
};

struct Contact {
    string surname, name, patronymic, phone;
    Date birthday;
    bool isFavorite;
    
    Contact(string s = "", string n = "", string p = "", 
            string ph = "", Date bd = Date(), bool fav = false)
        : surname(s), name(n), patronymic(p), phone(ph), birthday(bd), isFavorite(fav) {}
    
    string getFullName() const {
        return surname + " " + name + " " + patronymic;
    }
    
    bool operator<(const Contact& other) const {
        if (surname != other.surname) return surname < other.surname;
        if (name != other.name) return name < other.name;
        return patronymic < other.patronymic;
    }
};

class Contacts {
private:
    vector<Contact> contacts;
    
    int findIndexByFullName(const string& surname, const string& name, const string& patronymic) const {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].surname == surname && contacts[i].name == name && contacts[i].patronymic == patronymic) {
                return i;
            }
        }
        return -1;
    }
    
    int findIndexByPhone(const string& phone) const {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].phone == phone) return i;
        }
        return -1;
    }
    
public:
    // 1) создать новый контакт
    bool addContact(const string& surname, const string& name, const string& patronymic,
                    const string& phone, const Date& birthday, bool isFavorite) {
        if (findIndexByFullName(surname, name, patronymic) != -1) return false;
        
        Contact newContact(surname, name, patronymic, phone, birthday, isFavorite);
        contacts.push_back(newContact);
        sort(contacts.begin(), contacts.end());
        return true;
    }
    
    // 2) изменить выбранный контакт
    bool editContact(const string& surname, const string& name, const string& patronymic,
                     const string& newSurname, const string& newName, const string& newPatronymic,
                     const string& newPhone, const Date& newBirthday, bool newIsFavorite) {
        int index = findIndexByFullName(surname, name, patronymic);
        if (index == -1) return false;
        
        if (!newSurname.empty()) contacts[index].surname = newSurname;
        if (!newName.empty()) contacts[index].name = newName;
        if (!newPatronymic.empty()) contacts[index].patronymic = newPatronymic;
        if (!newPhone.empty()) contacts[index].phone = newPhone;
        if (newBirthday.day != 0) contacts[index].birthday = newBirthday;
        contacts[index].isFavorite = newIsFavorite;
        
        sort(contacts.begin(), contacts.end());
        return true;
    }
    
    // 3) найти контакт по ФИО
    bool findByName(const string& surname, const string& name, const string& patronymic, Contact& result) const {
        int index = findIndexByFullName(surname, name, patronymic);
        if (index == -1) return false;
        result = contacts[index];
        return true;
    }
    
    // 4) найти контакт по телефону
    bool findByPhone(const string& phone, Contact& result) const {
        int index = findIndexByPhone(phone);
        if (index == -1) return false;
        result = contacts[index];
        return true;
    }
    
    // 5) выдать все контакты на заданную букву
    vector<Contact> getContactsByFirstLetter(char letter) const {
        vector<Contact> result;
        for (const auto& contact : contacts) {
            if (!contact.surname.empty() && contact.surname[0] == letter) {
                result.push_back(contact);
            }
        }
        return result;
    }
    
    // 6) узнать текущее число контактов
    int getCount() const {
        return contacts.size();
    }
    
    // 7) внести контакт в список избранных
    bool addToFavorites(const string& surname, const string& name, const string& patronymic) {
        int index = findIndexByFullName(surname, name, patronymic);
        if (index == -1) return false;
        contacts[index].isFavorite = true;
        return true;
    }
    
    // 8) удалить контакт из списка избранных
    bool removeFromFavorites(const string& surname, const string& name, const string& patronymic) {
        int index = findIndexByFullName(surname, name, patronymic);
        if (index == -1) return false;
        contacts[index].isFavorite = false;
        return true;
    }
    
    // 9) выдать все избранные контакты
    vector<Contact> getFavorites() const {
        vector<Contact> result;
        for (const auto& contact : contacts) {
            if (contact.isFavorite) result.push_back(contact);
        }
        return result;
    }
    
    // 10) удалить контакт
    bool deleteContact(const string& surname, const string& name, const string& patronymic) {
        int index = findIndexByFullName(surname, name, patronymic);
        if (index == -1) return false;
        contacts.erase(contacts.begin() + index);
        return true;
    }
    
    // 11) сохранить контакты в файл
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) return false;
        
        for (const auto& contact : contacts) {
            file << contact.surname << " "
                 << contact.name << " "
                 << contact.patronymic << "\n"
                 << contact.phone << "\n"
                 << contact.birthday.day << "." << contact.birthday.month << "." << contact.birthday.year << "\n"
                 << contact.isFavorite << "\n";
        }
        file.close();
        return true;
    }
    
    // 12) считать контакты из файла
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        
        contacts.clear();
        Contact temp;
        
        while (file >> temp.surname >> temp.name >> temp.patronymic >> temp.phone) {
            file >> temp.birthday.day >> temp.birthday.month >> temp.birthday.year;
            file >> temp.isFavorite;
            contacts.push_back(temp);
        }
        
        file.close();
        sort(contacts.begin(), contacts.end());
        return true;
    }
    
};

int main() {
    bool correct = true;
    Contacts book;
    correct = book.addContact("Vodeneeva", "Taisiya", "Vladimirovna", "+79301234567", Date(13, 10, 2007), true);
    correct = book.addContact("Petrov", "Petr", "Petrovich", "+79100002312", Date(02, 01, 1975), false);
    correct = book.saveToFile("contacts.txt");
    if (!correct) throw -1;
};
