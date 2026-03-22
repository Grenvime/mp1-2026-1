#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess, attempts = 0;

    cout << "=== УГАДАЙ ЧИСЛО (1-100) ===\n";

    do {
        cout << "Твой вариант: ";
        cin >> guess;
        attempts++;

        if (guess > secret)
            cout << "Меньше!\n";
        else if (guess < secret)
            cout << "Больше!\n";
        else
            cout << "Поздравляю! Ты угадал за " << attempts << " попыток!\n";

    } while (guess != secret);

    return 0;
}