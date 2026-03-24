#include <iostream> 
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

class TextEditor {
private:
	int length;
	int posx;
	int posy;
	string text;

	void gotoxy(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	}

public:

	TextEditor() {
		length = 10;
		posx = 0;
		posy = 0;
		text = "";
	}

	TextEditor(int len, int x, int y) {
		length = len;
		posx = x;
		posy = y;
		text = "";
	}

	~TextEditor() {

	}


	void set_length(int new_length) {
		if (new_length > 0) {
			length = new_length;
			if (text.length() > length) {
				text = text.substr(0, length);
			}
		}
	}

	int get_length() {
		return length;
	}

	void set_position(int x, int y) {
		posx = x;
		posy = y;
	}

	void get_position(int& x, int& y) {
		x = posx;
		y = posy;
	}

	void show() {

		gotoxy(posx, posy);

		cout << "[";
		for (int i = 0; i < length; i++) {
			if (i < text.length()) {
				cout << text[i];
			}
			else {
				cout << " ";
			}
		}
		cout << "]";

		gotoxy(posx + 1, posy);
	}


	void input() {
		gotoxy(posx + 1, posy);

		for (int i = 0; i < length; i++) {
			cout << " ";
		}
		gotoxy(posx + 1, posy);

		text = "";
		char ch;
		int pos = 0;

		while (true) {
			ch = _getch();

			if (ch == 13) {
				break;
			}
			else if (ch == 8) {
				if (pos > 0) {
					pos--;
					text = text.substr(0, pos);
					cout << "\b \b";
				}
			}
			else if (ch >= 32 && ch <= 126 && pos < length) {
				text += ch;
				cout << ch;
				pos++;
			}
		}

		show();
		gotoxy(posx, posy + 1);
	}

	string get_text() {
		return text;
	}
};

int main() {
	TextEditor editor;

	editor.set_length(13);
	editor.set_position(10, 5);

	editor.show();

	cout << "\nEnter your text: ";
	editor.input();

	cout << "You entered: " << editor.get_text() << endl;

	int x, y;
	editor.get_position(x, y);
	cout << "\nEditor position: (" << x << ", " << y << ")" << endl;
	cout << "Editor length: " << editor.get_length() << endl;
	cout << "Current text: \"" << editor.get_text() << "\"" << endl;

	_getch();

	return 0;
}