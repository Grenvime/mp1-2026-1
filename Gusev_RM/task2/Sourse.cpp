#include <iostream>
#include <array>
#include <string>
#include <locale.h>
#include <windows.h>

class kalendar {
    std::array<std::array<int, 3>, 30> kalend = {};
    std::array<std::string, 30> sobytia = {};
    int chek = 0;
public:
    void yst_sob(std::string name, int god, int mes, int den)
    {
        for (int i = 0; i <= 30; i++)
        {
            if (sobytia[i] == "" && chek < 30)
            {
                sobytia[i] = name;
                kalend[i][0] = god;
                kalend[i][1] = mes;
                kalend[i][2] = den;
                chek += 1;
                break;
            }
        }
    }
    std::array<int, 3> raznicha(int nom, int god, int mes, int den){
        std::array<int, 3> result;
        result[0] = abs(kalend[nom][0] - god);
        result[1] = abs(kalend[nom][1] - mes);
        result[2] = abs(kalend[nom][2] - den);
        return result;
    }
    void smeshenie(int nom, int nom1, int param, int param2){
        if (param2 == 1)
        {
            if (nom1 == 1) {
                kalend[nom][0] += param;
            }
            if (nom1 == 2) {
                kalend[nom][1] += param;
            }
            if (nom1 == 3) {
                kalend[nom][2] += param;
            }
        }
        else
        {
            if (nom1 == 1) {
                kalend[nom][0] -= param;
            }
            if (nom1 == 2) {
                kalend[nom][1] -= param;
            }
            if (nom1 == 3) {
                kalend[nom][2] -= param;
            }
        }
    }
    std::string get_sobytie(int nom)
    {
        return sobytia[nom];
    }
    std::array<int, 3> get_kalend(int nom)
    {
        return kalend[nom];
    }
    int get_chek()
    {
        return chek;
    }
    ~kalendar() {}
};
int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    kalendar kalend;
    bool chek = true;
    while (chek)
    {
        int deyst;
        std::cout << "Выберите действие\n"
            << "1 - Ввести событие \n"
            << "2 - Посмотреть события\n"
            << "3 - Посчитать разницу\n"
            << "4 - Изменить событие\n"
            << "5 - Выйти\n\n";
        std::cin >> deyst;

        if (deyst == 1)
        {
            std::cout << "Введите название события" << "\n";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);

            int god, mes, den;
            std::cout << "Введите год события" << "\n";
            std::cin >> god;
            std::cout << "Введите номер месяца события" << "\n";
            std::cin >> mes;
            std::cout << "Введите день события" << "\n";
            std::cin >> den;

            kalend.yst_sob(name, god, mes, den);
        }
        if (deyst == 2)
        {
            if (kalend.get_chek() == 0)
            {
                std::cout << "Нет событий\n";
                continue;
            }
            std::cout << "\n";
            for (int i = 0; i < kalend.get_chek(); i++)
            {
                std::cout << i + 1 << " - " << kalend.get_sobytie(i) << "\n";
            }
            std::cout << "введите номер события про которое хотите узнать\n\n";
            int nom;
            std::cin >> nom;
            nom -= 1;
            auto data = kalend.get_kalend(nom);
            std::cout << kalend.get_sobytie(nom) << "\n";
            std::cout << "Год-" << data[0] << "\n"
                << "Месяц-" << data[1] << "\n"
                << "День-" << data[2] << "\n\n";
        }
        if (deyst == 3)
        {
            if (kalend.get_chek() == 0)
            {
                std::cout << "Нет событий\n";
                continue;
            }
            std::cout << "\n";
            for (int i = 0; i < kalend.get_chek(); i++)
            {
                std::cout << i + 1 << " - " << kalend.get_sobytie(i) << "\n";
            }
            std::cout << "Введите номер события с которым хотите сравнить\n\n";
            int nom;
            std::cin >> nom;
            nom -= 1;
            int god, mes, den;
            std::cout << "Введите год\n";
            std::cin >> god;
            std::cout << "Введите номер месяца\n";
            std::cin >> mes;
            std::cout << "Введите день\n";
            std::cin >> den;
            auto result = kalend.raznicha(nom, god, mes, den);
            std::cout << "Разница:\n"
                << "В годах - " << result[0] << "\n"
                << "В месяцах - " << result[1] << "\n"
                << "В днях - " << result[2] << "\n\n";
        }
        if (deyst == 4)
        {
            if (kalend.get_chek() == 0)
            {
                std::cout << "Нет событий\n";
                continue;
            }
            std::cout << "\n";
            for (int i = 0; i < kalend.get_chek(); i++)
            {
                std::cout << i + 1 << " - " << kalend.get_sobytie(i) << "\n";
            }
            std::cout << "Введите номер события которое хотите изменить\n\n";
            int nom;
            std::cin >> nom;
            nom -= 1;

            bool izm = true;
            while (izm)
            {
                std::cout << "Введите номер который хотите сместить\n";
                std::cout << "1 - Год\n"
                    << "2 - Месяц\n"
                    << "3 - День\n"
                    << "4 - Выйти\n\n";
                int nom1;
                std::cin >> nom1;

                if (nom1 == 4) {
                    break;
                }
                std::cout << "Введите смещение\n\n";
                int param;
                std::cin >> param;

                std::cout << "1 - Вверх\n2 - Вниз\n\n";
                int param2;
                std::cin >> param2;

                kalend.smeshenie(nom, nom1, param, param2);
            }
        }

        if (deyst == 5) break;
    }
    system("pause");
    return 0;
}