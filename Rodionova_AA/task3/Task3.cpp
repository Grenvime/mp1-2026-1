#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "windows.h"
#include "stdio.h"
#include "memory.h"

using namespace std;
void gotoxy(int x, int y);
int wherey(void);
int wherex(void);
class Menu {
	private:
		vector <string> menu;
		unsigned short n;
		unsigned short last; 
		unsigned short GetNum() {
			Print();
			std::cout << "Напишите выбранный номер: " << std::endl;
			std::cin >> last;//я забыла что пользователь сразу вводит нужную ему команду начиная соответственно с 1 а не с 0
			if ((0 < last) && (last <= n)) {
				return last;
			}
			else {
				
				throw std::out_of_range("Попытка выйти за пределы массива:");
			}
		}
	public:
		Menu(unsigned short count = 1) {
			menu = vector <string>(count);
			last = 0;
			n = count;
		}
		void SetCount(unsigned short count) {
			vector <string> temp = menu;
			n = count;
			menu = vector <string>(n);
			for (int i = 0; i < count; i++) {
				menu[i] = temp[i];
			}
		}
		unsigned short GetCount() const {
			return n;
		}
		void SetPoint(unsigned short num,string s) {
			try {
				menu.at(num-1) = s;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Попытка обратиться к элементу за пределы массива" << std::endl;
			}
		
		}
		const string& GetPoint(unsigned short num) const {
			try {
				return menu.at(num-1);
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Попытка обратиться к элементу за пределы массива"<< std::endl;
			}
		}
		void Print(int x = wherex(), int y = wherey()) const {
			gotoxy(x,y);
			for (int i = 0; i < n; i++) {
				std::cout << i + 1 << ". " << menu[i] << std::endl;
			}
		}
		unsigned short Choise() {
			try {
				return GetNum();
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Попытка выйти за пределы массива" << std::endl;
			}
		}
		unsigned short GetLast() const {
			return last;
		}

};

void main() {
	setlocale(LC_ALL, "Russian");
	short n = 5;
	Menu m(5);
	for (int i = 1; i <= m.GetCount(); i++) {
		m.SetPoint(i, "123");
	}
	m.GetPoint(6);
	unsigned short t=m.Choise();
	m.Print(50, 50);
}


int wherex(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.X;
}

int wherey(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.Y;
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}

