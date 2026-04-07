#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Word {
    string english;
    string russian;
};

class Dictionary {
private:
    Word words[100]; 
    int count;       
    
public:
    Dictionary() {
        count = 0;
    }
    
    Dictionary(const Dictionary& other) {
        count = other.count;
        for (int i = 0; i < count; i++) {
            words[i].english = other.words[i].english;
            words[i].russian = other.words[i].russian;
        }
    }

    ~Dictionary() {
    }
 
    Dictionary& operator=(const Dictionary& other) {
        if (this != &other) {
            count = other.count;
            for (int i = 0; i < count; i++) {
                words[i].english = other.words[i].english;
                words[i].russian = other.words[i].russian;
            }
        }
        return *this;
    }
  // 1) добавить в словарь слово и его перевод
    void addWord(string eng, string rus) {
        for (int i = 0; i < count; i++) {
            if (words[i].english == eng) {
                return;
            }
        }
        
        if (count < 100) {
            words[count].english = eng;
            words[count].russian = rus;
            count++;
        }
    }
    
    // 2) изменить перевод указанного слова
    void changeTranslation(string eng, string newRus) {
        for (int i = 0; i < count; i++) {
            if (words[i].english == eng) {
                words[i].russian = newRus;
                break;
            }
        }
    }
    
    // 3) получить перевод выбранного слова
    string getTranslation(string eng) {
        for (int i = 0; i < count; i++) {
            if (words[i].english == eng) {
                return words[i].russian;
            }
        }
        return "";
    }
    
    // 4) проверить наличие слова в словаре
    bool hasWord(string eng) {
        for (int i = 0; i < count; i++) {
            if (words[i].english == eng) {
                return true;
            }
        }
        return false;
    }
    
    // 5) получить число слов в словаре
    int getCount() {
        return count;
    }
    
    // 6) сохранить словарь в файл
    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            return;
        }
        
        for (int i = 0; i < count; i++) {
            file << words[i].english << " " << words[i].russian << endl;
        }
        file.close();
    }
    
    // 7) считать словарь из файла
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        
        count = 0;
        string eng, rus;
        
        while (file >> eng >> rus && count < 100) {
            bool alreadyExists = false;
            for (int i = 0; i < count; i++) {
                if (words[i].english == eng) {
                    alreadyExists = true;
                    break;
                }
            }
            
            if (!alreadyExists) {
                words[count].english = eng;
                words[count].russian = rus;
                count++;
            }
        }
        file.close();
    }

    void showAll() {
        if (count == 0) {
            return;
        }
        
        for (int i = 0; i < count; i++) {
            cout << words[i].english << " - " << words[i].russian << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    Dictionary dict;
    int choice;
    string eng, rus;
    
    do {
        cout << "1: Добавить слово" << endl;
        cout << "2: Изменить перевод" << endl;
        cout << "3: Найти перевод" << endl;
        cout << "4: Проверить наличие слова" << endl;
        cout << "5: Показать количество слов" << endl;
        cout << "6: Сохранить в файл" << endl;
        cout << "7: Загрузить из файла" << endl;
        cout << "8: Показать все слова" << endl;
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Введите слово на английском: ";
                cin >> eng;
                cout << "Введите перевод: ";
                cin >> rus;
                dict.addWord(eng, rus);
                break;
                
            case 2:
                cout << "Введите слово на английском: ";
                cin >> eng;
                cout << "Введите новый перевод: ";
                cin >> rus;
                dict.changeTranslation(eng, rus);
                break;
                
            case 3:
                cout << "Введите слово на английском: ";
                cin >> eng;
                cout << "Перевод: " << dict.getTranslation(eng) << endl;
                break;
                
            case 4:
                cout << "Введите слово на английском: ";
                cin >> eng;
                if (dict.hasWord(eng)) {
                    cout << "Слово есть в словаре" << endl;
                } else {
                    cout << "Слова нет в словаре" << endl;
                }
                break;
                
            case 5:
                cout << "В словаре " << dict.getCount() << " слов" << endl;
                break;
                
            case 6:
                dict.saveToFile("dictionary.txt");
                cout << "Сохранено" << endl;
                break;
                
            case 7:
                dict.loadFromFile("dictionary.txt");
                cout << "Загружено" << endl;
                break;
                
            case 8:
                dict.showAll();
                cout << "Всего слов: " << dict.getCount() << endl;
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}