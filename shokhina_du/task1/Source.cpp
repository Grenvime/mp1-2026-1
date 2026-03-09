#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class LengthConverter {
private:
    double meters;
    // структура для хранения информации о единице измерения
    struct UnitInfo {
        string name;
        string abbreviation;
        double coefficient; // коэффициент для перевода из метров в данную единицу
    };

    // массив всех доступных единиц измерения
    vector<UnitInfo> units;

    // константы для перевода из метров в другие единицы
    static constexpr double METERS_TO_INCH = 39.3701;               // 1 дюйм = 0.0254 м
    static constexpr double METERS_TO_FOOT = 3.28084;               // 1 фут = 0.3048 м
    static constexpr double METERS_TO_YARD = 1.09361;               // 1 ярд = 0.9144 м
    static constexpr double METERS_TO_MILE = 0.000621371;           // 1 миля = 1609.344 м
    static constexpr double METERS_TO_NAUTICAL_MILE = 0.000539957;  // 1 морская миля = 1852 м
    static constexpr double METERS_TO_LEAGUE = 0.000207125;         // 1 лига = 4,828 км
    static constexpr double METERS_TO_VERSTA = 0.000937383;         // 1 верста = 1066.8 м
    static constexpr double METERS_TO_SAGENE = 0.468691;            // 1 сажень = 2.1336 м
    static constexpr double METERS_TO_ARSHIN = 1.40607;             // 1 аршин = 0.7112 м
    static constexpr double METERS_TO_AU = 6.68459e-12;             // 1 а.е. = 149597870700 м

public:
    LengthConverter() : meters(0.0) {
        initializeUnits();
    }

    // единицы измерения
    void initializeUnits() {
        units = {
            {"Метры", "m", 1.0},
            {"Дюймы", "in", METERS_TO_INCH},
            {"Футы", "ft", METERS_TO_FOOT},
            {"Ярды", "yd", METERS_TO_YARD},
            {"Мили", "mi", METERS_TO_MILE},
            {"Морские мили", "nmi", METERS_TO_NAUTICAL_MILE},
            {"Лиги", "lea", METERS_TO_LEAGUE},
            {"Версты", "verst", METERS_TO_VERSTA},
            {"Сажени", "sag", METERS_TO_SAGENE},
            {"Аршины", "arsh", METERS_TO_ARSHIN},
            {"Астрономические единицы", "AU", METERS_TO_AU}
        };
    }

    void setLengthInMeters(double value) {
        meters = (value < 0) ? 0 : value;
    }

    bool setLengthInUnit(double value, int unitIndex) {
        if (unitIndex < 0 || unitIndex >= static_cast<int>(units.size()) || value < 0) {
            return false;
        }
        meters = value / units[unitIndex].coefficient;
        return true;
    }

    double getLengthInMeters() const {
        return meters;
    }

    double getLengthInUnit(int unitIndex) const {
        if (unitIndex < 0 || unitIndex >= static_cast<int>(units.size())) {
            return -1;
        }
        return meters * units[unitIndex].coefficient;
    }

    string getUnitName(int unitIndex) const {
        if (unitIndex < 0 || unitIndex >= static_cast<int>(units.size())) {
            return "";
        }
        return units[unitIndex].name;
    }

    string getUnitAbbreviation(int unitIndex) const {
        if (unitIndex < 0 || unitIndex >= static_cast<int>(units.size())) {
            return "";
        }
        return units[unitIndex].abbreviation;
    }

    int getUnitsCount() const {
        return static_cast<int>(units.size());
    }

    void getAllUnits(vector<string>& names, vector<string>& abbreviations) const {
        names.clear();
        abbreviations.clear();
        for (const auto& unit : units) {
            names.push_back(unit.name);
            abbreviations.push_back(unit.abbreviation);
        }
    }
};

// отображение доступных единиц измерения
void displayUnitSelection(const LengthConverter& converter) {
    vector<string> names, abbreviations;
    converter.getAllUnits(names, abbreviations);

    cout << "\n====== ДОСТУПНЫЕ ЕДИНИЦЫ ИЗМЕРЕНИЯ ======\n";
    for (size_t i = 0; i < names.size(); ++i) {
        cout << i + 1 << ". " << names[i] << " (" << abbreviations[i] << ")\n";
    }
    cout << "------------------------------------------\n";
}

// меню
void displayMenu() {
    cout << "\n========== МЕНЮ КОНВЕРТЕРА ДЛИН ==========\n";
    cout << "1. Установить новую длину в метрах\n";
    cout << "2. Установить новую длину в другой единице\n";
    cout << "3. Вывести текущую длину в метрах\n";
    cout << "4. Вывести текущую длину в конкретной единице\n";
    cout << "5. Вывести текущую длину во всех единицах\n";
    cout << "6. Выход из программы\n";
    cout << "Выберите действие (1-6): ";
}

int main() {
    setlocale(LC_ALL, "rus");

    LengthConverter converter;
    int choice;
    double value;
    int unitIndex;

    cout << "======= ПРОГРАММА КОНВЕРТАЦИИ ДЛИН =======\n";
    cout << "Сначала введите начальную длину в метрах: ";
    cin >> value;

    if (value < 0) {
        cout << "Длина не может быть отрицательной. Установлено значение 0.\n";
        converter.setLengthInMeters(0);
    }
    else {
        converter.setLengthInMeters(value);
    }
    cout << "------------------------------------------\n";

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите длину в метрах: ";
            cin >> value;
            if (value < 0) {
                cout << "Длина не может быть отрицательной. Установлено значение 0.\n";
                converter.setLengthInMeters(0);
            }
            else {
                converter.setLengthInMeters(value);
            }
            cout << "------------------------------------------\n";
            break;
        }

        case 2: {
            displayUnitSelection(converter);
            cout << "Выберите единицу измерения (1-" << converter.getUnitsCount() << "): ";
            cin >> unitIndex;

            if (unitIndex >= 1 && unitIndex <= converter.getUnitsCount()) {
                cout << "Введите длину в " << converter.getUnitName(unitIndex - 1) << ": ";
                cin >> value;

                if (converter.setLengthInUnit(value, unitIndex - 1)) {
                    cout << "Длина установлена: " << value << " "
                        << converter.getUnitAbbreviation(unitIndex - 1)
                        << " = " << converter.getLengthInMeters() << " m\n";
                }
                else {
                    cout << "Длина не может быть отрицательной. Операция отменена.\n";
                }
            }
            else {
                cout << "Неверный выбор.\n";
            }
            cout << "------------------------------------------\n";
            break;
        }

        case 3: {
            cout << fixed << setprecision(3);
            cout << "Текущая длина: " << converter.getLengthInMeters() << " метров\n";
            cout << "------------------------------------------\n";
            break;
        }

        case 4: {
            displayUnitSelection(converter);
            cout << "Выберите единицу измерения для вывода (1-" << converter.getUnitsCount() << "): ";
            cin >> unitIndex;

            if (unitIndex >= 1 && unitIndex <= converter.getUnitsCount()) {
                double convertedValue = converter.getLengthInUnit(unitIndex - 1);
                cout << fixed << setprecision(6);
                cout << converter.getLengthInMeters() << " m = " << convertedValue << " "
                    << converter.getUnitAbbreviation(unitIndex - 1)
                    << " (" << converter.getUnitName(unitIndex - 1) << ")\n";
            }
            else {
                cout << "Неверный выбор.\n";
            }
            cout << "------------------------------------------\n";
            break;
        }

        case 5: {
            vector<string> names, abbreviations;
            converter.getAllUnits(names, abbreviations);

            cout << fixed << setprecision(6);
            cout << "\n=== ДЛИНА В РАЗЛИЧНЫХ ЕДИНИЦАХ ИЗМЕРЕНИЯ ===\n";
            cout << "Метры: " << converter.getLengthInMeters() << " m\n";

            for (size_t i = 1; i < names.size(); ++i) {
                double convertedValue = converter.getLengthInUnit(static_cast<int>(i));
                cout << names[i] << ": " << convertedValue << " " << abbreviations[i] << "\n";
            }
            cout << "------------------------------------------\n";
            break;
        }

        case 6: {
            cout << "Программа завершена.\n";
            break;
        }

        default: {
            cout << "Неверный выбор. Пожалуйста, выберите 1-6.\n";
            }
        }
    } while (choice != 6);

    return 0;
}
