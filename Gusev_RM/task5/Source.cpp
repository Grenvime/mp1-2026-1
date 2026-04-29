#include <iostream>
#include <map>
#include <string>
using namespace std;

struct date {
    int day, mounth, year;

    bool operator<(const date& other) const {
        if (year != other.year) return year < other.year;
        if (mounth != other.mounth) return mounth < other.mounth;
        return day < other.day;
    }
};

struct deposit_status {
    bool statys;
    unsigned int sum;
    float rate;
    int time;
    float sum_rate;
    float total;
};

struct client {
    string nomscheta;
    string name;
    unsigned int sum;
    string password;
    bool info_deposit;
};

class ProcessingCenter {
    map<string, client> clients;
public:
    ProcessingCenter() {
        clients["0001"] = { "0001", "Иванов И.И.", 900000, "1111", false };
        clients["0002"] = { "0002", "Петров П.П.", 600000, "2222", false };
        clients["0003"] = { "0003", "Сидоров С.С.", 50000, "3333", false };
    }
    ~ProcessingCenter(){}
    bool check(string nomscheta_, string password_) {
        return clients.count(nomscheta_) && clients[nomscheta_].password == password_;
    }

    client* getClient(string nomscheta_) {
        if (clients.count(nomscheta_)) return &clients[nomscheta_];
        return nullptr;
    }
};

class Deposit {
    ProcessingCenter& pc;
    client* current = nullptr;
    bool pass = false;
    unsigned int sum_dep = 0;
    float sum_proz = 0;
    float prozent = 0;
    int srok = 0;
    date old = { 0, 0, 0 };
    date temp = { 0, 0, 0 };
    date end = { 0, 0, 0 };

public:
    Deposit(ProcessingCenter& p) : pc(p) {}
    ~Deposit(){}
    int authorize(string nomscheta_, string password_) {
        if (pc.check(nomscheta_, password_)) {
            pass = true;
            current = pc.getClient(nomscheta_);
            return 1;
        }
        else {
            pass = false;
            current = nullptr;
            return -1;
        }
    }

    int var_dep() {
        if (!current) return -1;

        double money = current->sum;
        if (money < 100000) return 1;
        if (money >= 100000 && money < 500000) return 2;
        if (money >= 500000 && money <= 1000000) return 3;
        if (money > 1000000) return 4;
        return -1;
    }

    bool check_opendep() {
        if (!current) return false;
        return current->info_deposit;
    }

    int open_deposit(int time, date a) {
        if (!current) return -1;
        if (current->info_deposit) return -2;
        if (time != 3 && time != 6 && time != 12 && time != 24 && time != 36) return -3;

        int range = var_dep();
        if (range == -1) return -1;

        sum_dep = current->sum;
        current->sum = 0;
        current->info_deposit = true;
        srok = time;

        float rates[4] = { 5.0, 7.0, 9.0, 11.0 };
        prozent = rates[range - 1] + 0.5 * (time / 3);

        old = a;
        temp = a;

        end = old;
        end.mounth += srok;
        while (end.mounth > 12) {
            end.mounth -= 12;
            end.year++;
        }

        return 1;
    }

    deposit_status depositstatus() {
        deposit_status st = { false, 0, 0, 0, 0, 0 };
        if (!current || !current->info_deposit) return st;

        st.statys = current->info_deposit;
        st.rate = prozent;
        st.sum = sum_dep;
        st.sum_rate = sum_proz;
        st.time = srok;
        st.total = sum_dep + sum_proz;
        return st;
    }

    date getEndDate() {
        return end;
    }

    int accrualofinterest(date now) {
        if (!current || !current->info_deposit) return -1;
        if (now < temp) return -2;
        if (end < now) return -3;

        int months = (now.year - temp.year) * 12 + (now.mounth - temp.mounth);

        for (int i = 0; i < months; i++) {
            float monthlyRate = prozent / 100.0 / 12.0;
            sum_proz += sum_dep * monthlyRate;
        }
        temp = now;
        return 0;
    }

    int withdrawinterest() {
        if (!current) return -1;
        if (!current->info_deposit) return -2;

        current->sum += (unsigned int)sum_proz;
        sum_proz = 0;
        return 1;
    }

    int closedeposit(date now) {
        if (!current) return -1;
        if (!current->info_deposit) return -2;
        if (now < end) return -3;

        accrualofinterest(now);

        current->sum += sum_dep + (unsigned int)sum_proz;
        sum_dep = 0;
        sum_proz = 0;
        current->info_deposit = false;
        return 1;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ProcessingCenter pc;
    Deposit dep(pc);

    int choice;
    string acc, pass;

    cout << "=== СИСТЕМА УПРАВЛЕНИЯ ДЕПОЗИТАМИ ===\n";

    while (true) {
        cout << "\nВведите номер счета: ";
        cin >> acc;
        cout << "Введите пароль: ";
        cin >> pass;

        int res = dep.authorize(acc, pass);

        if (res == 1) {
            cout << "\nАвторизация успешна!\n";
            break;
        }
        else {
            cout << "Ошибка! Неверный счет или пароль.\n";
        }
    }

    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Показать доступные ставки\n";
        cout << "2. Проверить наличие депозита\n";
        cout << "3. Открыть депозит\n";
        cout << "4. Показать состояние депозита\n";
        cout << "5. Начислить проценты\n";
        cout << "6. Снять проценты\n";
        cout << "7. Закрыть депозит\n";
        cout << "8. Показать дату окончания\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int range = dep.var_dep();
            if (range == -1) {
                cout << "Ошибка: не авторизован\n";
                break;
            }

            cout << "\n=== ДОСТУПНЫЕ СТАВКИ ===\n";
            cout << "Ваш диапазон сумм: ";

            float baseRate = 0;
            switch (range) {
            case 1:
                cout << "до 100 000 руб.\n";
                baseRate = 5.0;
                break;
            case 2:
                cout << "100 000 - 500 000 руб.\n";
                baseRate = 7.0;
                break;
            case 3:
                cout << "500 000 - 1 000 000 руб.\n";
                baseRate = 9.0;
                break;
            case 4:
                cout << "свыше 1 000 000 руб.\n";
                baseRate = 11.0;
                break;
            }

            cout << "\nСтавки по срокам:\n";
            cout << "3 месяца:  " << baseRate + 0.5 * (3 / 3.0) << "%\n";
            cout << "6 месяцев: " << baseRate + 0.5 * (6 / 3.0) << "%\n";
            cout << "1 год:     " << baseRate + 0.5 * (12 / 3.0) << "%\n";
            cout << "2 года:    " << baseRate + 0.5 * (24 / 3.0) << "%\n";
            cout << "3 года:    " << baseRate + 0.5 * (36 / 3.0) << "%\n";
            break;
        }

        case 2: {
            if (dep.check_opendep()) {
                cout << "Депозит открыт\n";
            }
            else {
                cout << "Депозит не открыт\n";
            }
            break;
        }

        case 3: {
            if (dep.check_opendep()) {
                cout << "Ошибка: у вас уже есть открытый депозит\n";
                break;
            }

            int months;
            cout << "Введите срок (3, 6, 12, 24, 36 месяцев): ";
            cin >> months;

            date today;
            cout << "Введите сегодняшнюю дату (день месяц год): ";
            cin >> today.day >> today.mounth >> today.year;

            int res = dep.open_deposit(months, today);

            if (res == -1) cout << "Ошибка: не авторизован\n";
            else if (res == -2) cout << "Ошибка: депозит уже открыт\n";
            else if (res == -3) cout << "Ошибка: неверный срок\n";
            else if (res == 1) {
                deposit_status st = dep.depositstatus();
                date endDate = dep.getEndDate();
                cout << "\n=== ДЕПОЗИТ ОТКРЫТ ===\n";
                cout << "Сумма: " << st.sum << " руб.\n";
                cout << "Срок: " << st.time << " мес.\n";
                cout << "Ставка: " << st.rate << "%\n";
                cout << "Дата окончания: " << endDate.day << "."
                    << endDate.mounth << "." << endDate.year << "\n";
            }
            break;
        }

        case 4: {
            deposit_status st = dep.depositstatus();

            if (!st.statys) {
                cout << "Депозит не открыт\n";
            }
            else {
                date endDate = dep.getEndDate();
                cout << "\n=== СОСТОЯНИЕ ДЕПОЗИТА ===\n";
                cout << "Сумма: " << st.sum << " руб.\n";
                cout << "Ставка: " << st.rate << "%\n";
                cout << "Срок: " << st.time << " мес.\n";
                cout << "Проценты: " << st.sum_rate << " руб.\n";
                cout << "Итого: " << st.total << " руб.\n";
                cout << "Дата окончания: " << endDate.day << "."
                    << endDate.mounth << "." << endDate.year << "\n";
            }
            break;
        }

        case 5: {
            if (!dep.check_opendep()) {
                cout << "Нет открытого депозита\n";
                break;
            }

            date now;
            cout << "Введите текущую дату (день месяц год): ";
            cin >> now.day >> now.mounth >> now.year;

            deposit_status before = dep.depositstatus();
            int res = dep.accrualofinterest(now);
            deposit_status after = dep.depositstatus();

            if (res == -1) cout << "Ошибка: не авторизован или нет депозита\n";
            else if (res == -2) cout << "Ошибка: дата раньше последнего начисления\n";
            else if (res == -3) cout << "Ошибка: срок депозита истек\n";
            else if (res == 0) {
                cout << "Начислено процентов: " << after.sum_rate - before.sum_rate << " руб.\n";
            }
            break;
        }

        case 6: {
            int res = dep.withdrawinterest();

            if (res == -1) cout << "Ошибка: не авторизован\n";
            else if (res == -2) cout << "Ошибка: нет депозита\n";
            else if (res == 1) {
                cout << "Проценты сняты на зарплатный счет\n";
            }
            break;
        }

        case 7: {
            if (!dep.check_opendep()) {
                cout << "Нет открытого депозита\n";
                break;
            }

            date now;
            cout << "Введите текущую дату (день месяц год): ";
            cin >> now.day >> now.mounth >> now.year;

            int res = dep.closedeposit(now);

            if (res == -1) cout << "Ошибка: не авторизован\n";
            else if (res == -2) cout << "Ошибка: нет депозита\n";
            else if (res == -3) cout << "Ошибка: срок депозита ещё не истек\n";
            else if (res == 1) {
                cout << "\n=== ДЕПОЗИТ ЗАКРЫТ ===\n";
                cout << "Средства переведены на зарплатный счет\n";
            }
            break;
        }

        case 8: {
            if (!dep.check_opendep()) {
                cout << "Нет открытого депозита\n";
                break;
            }
            date endDate = dep.getEndDate();
            cout << "Дата окончания депозита: "
                << endDate.day << "." << endDate.mounth << "." << endDate.year << "\n";
            break;
        }

        case 0:
            cout << "До свидания!\n";
            break;

        default:
            cout << "Неверный выбор\n";
        }

    } while (choice != 0);

    return 0;
}