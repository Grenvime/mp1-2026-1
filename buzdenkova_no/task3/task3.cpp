#include <iostream>
#include <windows.h>

class CustomMenu
{
private:
    int NumberOfCommands;
    static const int MAX_ITEMS = 100;
    std::string ItemsMenu[MAX_ITEMS];
    int SelectedItem;

    static void SetConsoleCursorPosition(int x, int y) {
#ifdef _WIN32
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        ::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
        std::cout << "\033[" << y << ";" << x << "H";
#endif
    }

public:
    CustomMenu() : NumberOfCommands(0), SelectedItem(0) {}

    CustomMenu(int commandCount) : NumberOfCommands(0), SelectedItem(0) {
        SetNumberOfCommands(commandCount);
    }

    ~CustomMenu() = default;

    void SetNumberOfCommands(int n = 0) {
        if (n < 0 || n > MAX_ITEMS) {
            std::cerr << "Error.";
            return;
        }
        NumberOfCommands = n;
    }
    int GetNumberOfCommands() const {
        return NumberOfCommands;
    }

    bool SetMenuItemName(int ind, const std::string& name) {
        if (ind < 0 || ind >= NumberOfCommands) {
            return false;
        }
        ItemsMenu[ind] = name;
        return true;
    }
    bool SetMenuItem(int numb, const std::string& name) {
        if (numb < 1 || numb > NumberOfCommands) {
            return false;
        }
        ItemsMenu[numb - 1] = name;
        return true;
    }

    void DisplayMenu() {
        for (int i = 0; i < NumberOfCommands; ++i) {
            if (i == SelectedItem) {
                std::cout << "> " << ItemsMenu[i] << std::endl;
            }
            else {
                std::cout << "  " << ItemsMenu[i] << std::endl;
            }
        }
    }

    int SelectMenuItem() {
        int choice;
        do {
            std::cout << "Menu item (1-" << GetNumberOfCommands() << "): ";
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Error.\n";
                choice = -1;
                continue;
            }

            if (choice < 1 || choice > GetNumberOfCommands()) {
                std::cout << "Error.\n";
            }
        } while (choice < 1 || choice > GetNumberOfCommands());

        SelectedItem = choice;
        return SelectedItem;
    }

    int GetLastItem() const {
        return SelectedItem;
    }
};

int main() {}