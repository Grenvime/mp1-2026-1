#include <iostream>
using namespace std;

class Matrix {
private:
	int data[8][8];
	int size;
public:

	Matrix() {
		size = 2;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				data[i][j] = 0;
			}
		}
	}

	Matrix(int s) {
		if (s < 2) {
			s = 2;
		}
		if (s > 8) {
			s = 8;
		}
		size = s;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				data[i][j] = 0;
			}
		}
	}

	Matrix(const Matrix& other) {
		size = other.size;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				data[i][j] = other.data[i][j];
			}
		}
	}

	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			size = other.size;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	void set_size(int s) {
		if (s >= 2 && s <= 8) {
			size = s;
		}
	}

	int get_size() {
		return size;
	}

	void set_element(int i, int j, int value) {
		if (i >= 0 && i < size && j >= 0 && j < size) {
			data[i][j] = value;
		}
	}

	int get_element(int i, int j) {
		if (i >= 0 && i < size && j >= 0 && j < size) {
			return data[i][j];
		}
		return 0;
	}

	bool has_diagonal_dominance() {
		for (int i = 0; i < size; i++) {
			int diag = abs(data[i][i]);
			int sum = 0;
			for (int j = 0; j < size;j++) {
				if (i != j) {
					sum += abs(data[i][j]);
				}
			}
			if (diag <= sum) {
				return false;
			}
		}
		return true;
	}

	Matrix sum(Matrix other) {
		Matrix result(size);
		if (size != other.size) {
			cout << "The matrix sizes are different!" << endl;
			return result;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}

	void print() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << data[i][j] << "\t";
			}
			cout << endl;
		}
	}

};


int main() {
	Matrix m1(3);
	
	m1.set_element(0, 0, 5);
	m1.set_element(0, 1, 1);
	m1.set_element(0, 2, 2);
	m1.set_element(1, 0, 2);
	m1.set_element(1, 1, 6);
	m1.set_element(1, 2, 1);
	m1.set_element(2, 0, 1);
	m1.set_element(2, 1, 2);
	m1.set_element(2, 2, 7);

	cout << "Matrix m1: " << endl;
	m1.print();

	if (m1.has_diagonal_dominance()) {
		cout << "There is diagonal dominance" << endl;
	}
	else {
		cout << "There is no diagonal dominance";
	}

	Matrix m2(3);
	m2.set_element(0, 0, 1);
	m2.set_element(0, 1, 2);
	m2.set_element(0, 2, 3);
	m2.set_element(1, 0, 4);
	m2.set_element(1, 1, 5);
	m2.set_element(1, 2, 6);
	m2.set_element(2, 0, 7);
	m2.set_element(2, 1, 8);
	m2.set_element(2, 2, 9);

	cout << "\nMatrix m2: " << endl;
	m2.print();

	Matrix m3 = m1.sum(m2);
	cout << "\nSumm: " << endl;
	m3.print();

	cout << "The element from the second matrix ([2][3]): " << endl;
	cout << m2.get_element(1, 2) << endl;


	cin.get();
	return 0;
} 