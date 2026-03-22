#include <iostream>

using namespace std;

class Matrica {
private:
	int size;
	int elem[8][8];

public:

	Matrica() {
		size = 2;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				elem[i][j] = 0;
			}
		}
	}

	Matrica(int n) {
		if (n < 2 || n > 8) {
			cout << "Error: wrong size" << endl;
			size = 2;
		}
		else {
			size = n;
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				elem[i][j] = 0;
			}
		}
	}

	Matrica(const Matrica& drug) {
		size = drug.size;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				elem[i][j] = drug.elem[i][j];
			}
		}
		for (int i = size; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				elem[i][j] = 0;
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = size; j < 8; j++) {
				elem[i][j] = 0;
			}
		}
	}

	~Matrica() {
	}

	Matrica& operator=(const Matrica& drug) {
		if (this != &drug) {
			size = drug.size;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					elem[i][j] = drug.elem[i][j];
				}
			}
			for (int i = size; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					elem[i][j] = 0;
				}
			}
			for (int i = 0; i < size; i++) {
				for (int j = size; j < 8; j++) {
					elem[i][j] = 0;
				}
			}
		}
		return *this;
	}

	void zadatSize(int newSize) {
		if (newSize >= 2 && newSize <= 8) {
			size = newSize;
		}
		else {
			cout << "Error: wrong size" << endl;
		}
	}

	int uznatSize() const {
		return size;
	}

	void zadatElement(int row, int col, int znach) {
		if (row >= 0 && row < size && col >= 0 && col < size) {
			elem[row][col] = znach;
		}
		else {
			cout << "Error index!" << endl;
		}
	}

	 int uznatElement(int row, int col) const {
		if (row >= 0 && row < size && col >= 0 && col < size) {
			return elem[row][col];
		}
		else {
			cout << "Error: index not found!" << endl;
			return 0;
		}
	}

	 bool DiagonalPreoblad() const {
		 for (int i = 0; i < size; i++) {
			 int diag = elem[i][i];
			 if (diag < 0) diag = -diag;

			 int sum = 0;
			 for (int j = 0; j < size; j++) {
				 if (j != i) {
					 int chislo = elem[i][j];
					 if (chislo < 0) chislo = -chislo;
					 sum += chislo;
				 }
			 }
			 if (diag <= sum) {
				 return false;
			 }
		 }
		 return true;
	 }

	 Matrica sum(const Matrica& drug) const {
		 if (size != drug.size) {
			 cout << "Error" << endl;
			 return Matrica(size);
		 }
		 Matrica result(size);
		 for (int i = 0; i < size; i++) {
			 for (int j = 0; j < size; j++) {
				 result.elem[i][j] = elem[i][j] + drug.elem[i][j];
			 }
		 }
		 return result;
	 }

	 void ecran() const {
		 cout << "Matrica " << size << "X" << size << ":" << endl;
		 for (int i = 0; i < size; i++) {
			 for (int j = 0; j < size; j++) {
				 cout << elem[i][j] << "\t";
			 }
			 cout << endl;
		 }
		 cout << endl;
	 }
};

int main() {

	cout << "=== Matrica class test ===" << endl;

	Matrica m1(3);

	m1.zadatElement(0, 0, 5);
	m1.zadatElement(0, 1, 6);
	m1.zadatElement(0, 2, 1);
	m1.zadatElement(1, 0, 7);
	m1.zadatElement(1, 1, 8);
	m1.zadatElement(1, 2, 3);
	m1.zadatElement(2, 0, 2);
	m1.zadatElement(2, 1, 4);
	m1.zadatElement(2, 2, 9);

	cout << "First matrica:" << endl;
	m1.ecran();

	if (m1.DiagonalPreoblad()) {
		cout << "Matrica Diagonal Preoblad" << endl;
	}
	else {
		cout << "Matrica Ne Diagonal Preoblad" << endl;
	}
	cout << endl;


	Matrica m2(3);
	m2.zadatElement(0, 0, 1);
	m2.zadatElement(0, 1, 2);
	m2.zadatElement(0, 2, 3);
	m2.zadatElement(1, 0, 4);
	m2.zadatElement(1, 1, 5);
	m2.zadatElement(1, 2, 6);
	m2.zadatElement(2, 0, 7);
	m2.zadatElement(2, 1, 8);
	m2.zadatElement(2, 2, 9);

	cout << "Vtoraya matrica:" << endl;
	m2.ecran();

	Matrica m3 = m1.sum(m2);
	cout << "Sum of matrices:" << endl;
	m3.ecran();

	cout << "element is vtotoi matrici [1][2] = " << endl;
	cout << m2.uznatElement(1, 2) << endl;

	cin.get();

	return 0;
}