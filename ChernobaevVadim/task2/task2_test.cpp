#include <iostream>
#include <cmath>
#include <locale.h>

class Matrix {
private:
    int** data;
    int size;

public:
    //По умолчанию
    Matrix(int n = 2) : size(n) {
        if (n < 2 || n > 8) {
            std::cout << "Ошибка: Размер матрицы должен быть от 2 до 8. Устанавливаем размер 2x2.\n";
            size = 2;
        }
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size] {0};
        }
    }

    // Копирование
    Matrix(const Matrix& other) : size(other.size) {
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // Освобождение старой памяти
            for (int i = 0; i < size; i++) {
                delete[] data[i];
            }
            delete[] data;

            size = other.size;
            data = new int* [size];
            for (int i = 0; i < size; i++) {
                data[i] = new int[size];
                for (int j = 0; j < size; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Размер
    bool setSize(int n) {
        if (n < 2 || n > 8) {
            std::cout << "Ошибка: Размер матрицы должен быть от 2 до 8. Размер не изменен.\n";
            return false;
        }
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;

        size = n;
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size] {0};
        }
        return true;
    }

    // Узнать размер
    int getSize() const {
        return size;
    }

    //Задать элемент матрицы по индексам
    bool setElement(int row, int col, int value) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            std::cout << "Ошибка: Индексы выходят за пределы матрицы.\n";
            return false;
        }
        data[row][col] = value;
        return true;
    }

    //Узнать элемент матрицы по индексам
    int getElement(int row, int col) const {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            std::cout << "Ошибка: Индексы выходят за пределы матрицы.\n";
            return -1;  //-1 = ошибка
        }
        return data[row][col];
    }

    //Диагональное преобладание
    bool Diagonal() const {
        for (int i = 0; i < size; i++) {
            int sumOther = 0;
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    sumOther += std::abs(data[i][j]);
                }
            }
            if (std::abs(data[i][i]) <= sumOther) {
                return false;
            }
        }
        return true;
    }

    //Сумма двух
    bool addMatrices(const Matrix& other, Matrix& result) const {
        if (size != other.size) {
            std::cout << "Ошибка: Матрицы должны быть одного размера.\n";
            return false;
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return true;
    }

    //Вывод матрицы на консоль
    void print() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    //3 на 3
    Matrix m1(3);
    m1.setElement(0, 0, 5);
    m1.setElement(0, 1, 3);
    m1.setElement(0, 2, 2);
    m1.setElement(1, 0, 4);
    m1.setElement(1, 1, 6);
    m1.setElement(1, 2, 1);
    m1.setElement(2, 0, 7);
    m1.setElement(2, 1, 8);
    m1.setElement(2, 2, 9);

    std::cout << "Первая матрица 3x3:\n";
    m1.print();

    //3 на 3 (вторая)
    Matrix m2(3);
    m2.setElement(0, 0, 3);
    m2.setElement(0, 1, 6);
    m2.setElement(0, 2, 2);
    m2.setElement(1, 0, 1);
    m2.setElement(1, 1, 8);
    m2.setElement(1, 2, 5);
    m2.setElement(2, 0, 6);
    m2.setElement(2, 1, 10);
    m2.setElement(2, 2, 2);

    std::cout << "Вторая матрица 3x3:\n";
    m2.print();

    Matrix m3(3);
    if (m1.addMatrices(m2, m3)) {
        std::cout << "Сумма матриц (3x3 + 3x3):\n";
        m3.print();
    }


    std::cout << "Первая матрица имеет диагональное преобладание? "
        << (m1.Diagonal() ? "Да" : "Нет") << std::endl;

    //4x4
    Matrix m4(4);
    m4.setElement(0, 0, 1);
    m4.setElement(0, 1, 1);
    m4.setElement(0, 2, 1);
    m4.setElement(0, 3, 1);
    m4.setElement(1, 0, 1);
    m4.setElement(1, 1, 1);
    m4.setElement(1, 2, 1);
    m4.setElement(1, 3, 1);
    m4.setElement(2, 0, 1);
    m4.setElement(2, 1, 1);
    m4.setElement(2, 2, 1);
    m4.setElement(2, 3, 1);
    m4.setElement(3, 0, 1);
    m4.setElement(3, 1, 1);
    m4.setElement(3, 2, 1);
    m4.setElement(3, 3, 1);

    std::cout << "Матрица 4x4:\n";
    m4.print();

    return 0;
}