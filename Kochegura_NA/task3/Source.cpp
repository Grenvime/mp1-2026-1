#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

class Redactor {
private:
	int length;
	int x;
	int y;
	string text;

public:

	Redactor() {
		length = 20;
		x = 0;
		y = 0;
		text = "";
	}

	Redactor(int len, int posicX, int posicY) {
		if (len > 0) {
			length = len;
		}
		else {
			length = 20;
		}
		x = posicX;
		y = posicY;
		text = "";
	}

	~Redactor() {
	}

	Redactor(const Redactor& other) {
		length = other.length;
		x = other.x;
		y = other.y;
		text = other.text;
	}

	void zadatDlinu(int len) {
		if (len > 0) {
			length = len;
		}
	}

	int uznatDlinu() {
		return length;
	}

	void zadatPosiciu(int posicX, int posicY) {
		x = posicX;
		y = posicY;
	}

	void ecran() {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		cout << "[";
		for (int i = 0; i < length; i++) {
			cout << " ";
		}
		cout << "]";

		coord.X = x + 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void vvod() {
		COORD coord;
		coord.X = x + 1;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		char ch;
		text = "";
		int pos = 0;

		while (true) {
			ch = _getch();

			if (ch == 13) {
				break;
			}
			else if (ch == 8) {
				if (pos > 0) {
					pos--;
					text.erase(pos, 1);

					coord.X = x + 1;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					cout << text;

					for (int j = text.length(); j < length; j++) {
						cout << " ";
					}
					coord.X = x + 1 + pos;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				}
			}
			else if (ch == 27) {
				text = "";
				pos = 0;
				coord.X = x + 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				for (int j = 0; j < length; j++) {
					cout << " ";
				}
				coord.X = x + 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			}
			else if (ch >= 32 && ch <= 126) {
				if (text.length() < length) {
					text.insert(pos, 1, ch);
					pos++;

					coord.X = x + 1;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					cout << text;
					coord.X = x + 1 + pos;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				}
			}
		}
	}

	string poluchitText() {
		return text;
	}

	void clear() {
		text = "";
		ecran();
	}

};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("cls");

	Redactor editor(30, 10, 10);

	cout << "Enter Text:" << endl;
	editor.ecran();
	editor.vvod();

	cout << endl << endl << "You Enter: \"" << editor.poluchitText() << "\"" << endl;

	cout << "Len:" << editor.uznatDlinu() << endl;
	
	int posicX = 0, posicY = 0;
	editor.zadatPosiciu(posicX, posicY);
	cout << "Posicion: (" << posicX << ", " << posicY << ")" << endl;

	_getch();

	return 0;
}