#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <locale>

using namespace std;

struct Client {
    string accNum;
    string fullName;
    int salary;
    string password;

    bool   depActive = false;
    double depAmount = 0;
    int    depTerm = 0;
    double depRate = 0;
    time_t depOpenDate = 0;
    double depTakenInt = 0;

    Client(const string& num, const string& name, int bal, const string& pwd) {
        accNum = num;
        fullName = name;
        salary = bal;
        password = pwd;
    }
};

class ProcessingCenter {
    vector<Client> clients;
public:
    void add(const Client& c) { clients.push_back(c); }

    Client* find(const string& acc) {
        for (auto& c : clients)
            if (c.accNum == acc) return &c;
        return nullptr;
    }
};

class Deposit {
    ProcessingCenter& pc;
    Client* cur = nullptr;

    const double rates[5][4] = {
        {4.0, 4.5, 5.0, 5.5},
        {4.5, 5.0, 5.5, 6.0},
        {5.0, 6.0, 6.6, 7.0},
        {5.5, 6.5, 7.0, 7.5},
        {6.0, 7.0, 7.5, 8.0}
    };

    const int terms[5] = { 3, 6, 12, 24, 36 };

    int rangeIdx(double amount) {
        if (amount < 100000) return 0;
        if (amount < 500000) return 1;
        if (amount < 1000000)return 2;
        return 3;
    }   

    int availInterest(Client& c) {
        time_t now = time(nullptr);
        tm now_tm = *localtime(&now);
        tm open_tm = *localtime(&c.depOpenDate);

        int years_diff = now_tm.tm_year - open_tm.tm_year;
        int months_diff = now_tm.tm_mon - open_tm.tm_mon;
        int months = years_diff * 12 + months_diff;

        if (now_tm.tm_mday < open_tm.tm_mday)
            months--;

        if (months < 0) months = 0;

        double monthlyRate = c.depRate / 100.0 / 12.0;
        double totalInterest = c.depAmount * monthlyRate * months;

        int available = (int)(totalInterest - c.depTakenInt);
        return available;
    }

public:

    Deposit(ProcessingCenter& pc) : pc(pc) {}

    bool login(const string& acc, const string& pwd) {
        cur = pc.find(acc);
        if (cur && cur->password == pwd) return true;
        cur = nullptr;
        return false;
    }

    void logout() { cur = nullptr; }

    void showAvailable() {
        if (!cur) { cout << "Не авторизован\n"; return; }
        int bal = cur->salary;
        cout << "Доступные депозиты (баланс " << bal << "):\n";
        for (int t = 0; t < 5; ++t) {
            cout << "Срок " << terms[t] << " мес: ";
            bool first = true;
            for (int r = 0; r < 4; ++r) {
                int low = (r == 0) ? 0 : (r == 1 ? 100000 : (r == 2 ? 500000 : 1000000));
                if (bal >= low) {
                    if (!first) cout << ", ";
                    cout << rates[t][r] << "%";
                    first = false;
                }
            }
            cout << "\n";
        }
    }

    bool hasDeposit() { return cur && cur->depActive; }

    bool open(double amount, int term) {
        if (!cur) { cout << "Ошибка: не авторизован\n"; return false; }
        if (cur->depActive) { cout << "Ошибка: депозит уже открыт\n"; return false; }
        int tIdx = -1;
        for (int i = 0; i < 5; ++i) if (terms[i] == term) { tIdx = i; break; }
        if (tIdx == -1) { cout << "Ошибка: неверный срок\n"; return false; }
        if (amount <= 0 || amount > cur->salary) {
            cout << "Ошибка: недопустимая сумма\n"; return false;
        }
        int rIdx = rangeIdx(amount);
        int low = (rIdx == 0) ? 0 : (rIdx == 1 ? 100000 : (rIdx == 2 ? 500000 : 1000000));
        if (cur->salary < low) {
            cout << "Ошибка: недостаточно средств для выбранного диапазона\n";
            return false;
        }
        cur->salary -= (int)amount;
        cur->depActive = true;
        cur->depAmount = amount;
        cur->depTerm = term;
        cur->depRate = rates[tIdx][rIdx];
        cur->depOpenDate = time(nullptr);
        cur->depTakenInt = 0;
        cout << "Депозит открыт\n";
        return true;
    }

    void showState() {
        if (!cur) { cout << "Не авторизован\n"; return; }
        if (!cur->depActive) { cout << "Нет депозита\n"; return; }
        int avail = availInterest(*cur);
        cout << "Начальная сумма: " << cur->depAmount
            << ", Срок: " << cur->depTerm
            << " мес, Ставка: " << cur->depRate
            << "%, Доступно процентов: " << avail
            << ", Уже снято: " << cur->depTakenInt << "\n";
    }

    bool takeInterest() {
        if (!cur || !cur->depActive) {
            cout << "Ошибка: нет депозита\n"; return false;
        }
        int avail = availInterest(*cur);
        if (avail <= 0) {
            cout << "Нет доступных процентов\n"; return false;
        }
        cur->salary += avail;
        cur->depTakenInt += avail;
        cout << "Снято процентов: " << avail << "\n";
        return true;
    }

    bool close() {
        if (!cur || !cur->depActive) {
            cout << "Ошибка: нет депозита\n"; return false;
        }
        tm* open = localtime(&cur->depOpenDate);
        tm mat = *open;
        mat.tm_mon += cur->depTerm;
        mktime(&mat);
        if (time(nullptr) < mktime(&mat)) {
            cout << "Депозит ещё не истёк\n"; return false;
        }
        int interest = availInterest(*cur);
        int total = (int)cur->depAmount + interest;
        cur->salary += total;
        cur->depActive = false;
        cout << "Депозит закрыт, выплачено: " << total << "\n";
        return true;
    }
};

int main() {
    locale::global(std::locale("ru_RU.UTF-8"));
}