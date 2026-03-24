#include <iostream>

class String {
	private:
		char* str;
		unsigned short len;
	public:
		String()
		{
			len = 0;
			str = new char[1];
			str[0] = '\0';
		}

		String(const String& other) {
			len = other.len;
			str = new char[len + 1];
			memcpy(str, other.str, other.len * sizeof(char));
			str[len] = '\0';
		}

		String(char* s) {
			int i = 0;
			while ((s[i] != '\0') || (i < 40)) {
				i++;
			}
			len = i;
			str = new char[len + 1];
			memcpy(str, s, len * sizeof(char));
			str[len] = '\0';
		}
		String& operator=(const String& other) {
			len = other.len;
			delete[] str;
			str = new char[len + 1];
			memcpy(str, other.str, len * sizeof(char));
			str[len] = '\0';
		}
		void Setstr(const char* s) {
			int i = 0;
			while ((s[i] != '\0') || (i < 40)) {
				i++;
			}
			len = i;
			delete[] str;
			str = new char[len + 1];
			memcpy(str, s, len * sizeof(char));
			str[len] = '\0';
		}

		char& operator[](unsigned short index) {
			index %= len;
			return str[index];
		}
		const char& operator[](unsigned short index) const {
			index %= len;
			return str[index];
		}
		int Len() {
			return len;
		}
		String substr(int start, int count) const {
			if (start < 0 || start >= len || count < 0) {
				return String("");
			}

			if (start + count > len) {
				count = len - start;
			}

			char* temp = new char[count + 1];
			for (int i = 0; i < count; i++) {
				temp[i] = str[start + i];
			}
			temp[count] = '\0';

			String result(temp);
			delete[] temp;
			return result;
		}
		bool isPalindrome() const {
			int left = 0;
			int right = len - 1;

			while (left < right) {
				if (str[left] != str[right]) {
					return false;
				}
				left++;
				right--;
			}
			return true;
		}
		int CountAlp() const {
			bool used[26] = { false };

			for (int i = 0; i < len; i++) {
				if (isalpha((unsigned char)str[i])) {
					char ch = tolower((unsigned char)str[i]);
					if (ch >= 'a' && ch <= 'z') {
						used[ch - 'a'] = true;
					}
				}
			}
			int count = 0;
			for (int i = 0; i < 26; i++) {
				if (used[i]) {
					count++;
				}
			}
			return count;
		}
		friend std::ostream& operator<<(std::ostream& os, const String& Str) {
			os << Str.str;
			return os;
		}
		~String() {
			delete[] str;
		}
};

void main() {
	String s1, s2("Hello World");
	std::cout << s1 << std::endl;
	s1.Setstr("123321");
	std::cout << s2 << std::endl;
	s2.Setstr("Thequickbrownfoxjumpsoverthelazydog");
	std::cout << s1 <<" "<<s1.isPalindrome()<< std::endl;
	std::cout << s2 << " " << s2.isPalindrome() << " " <<s2.CountAlp() << std::endl;
}