#include <iostream>
#include <cmath>
class Vector {
private:
    unsigned short size;
    int* vec;
public:
    Vector() {
        size = 1;
        vec = new int[size] {0};
    }
    Vector(unsigned short n) {
        if ((n > 20) || (n == 0))
        {
            size = 1;
            vec = new int[size] {0};
        }
        else {
            size = n;
            vec = new int[size] {0};
        }
    }
    Vector(const Vector& other) {
        size = other.size;
        vec = new int[size];
        for (int i = 0; i < size; i++) {
            vec[i] = other.vec[i];
        }
    }
    Vector& operator=(const Vector& other) {
        if (this == &other)
            return *this;
        delete[] vec;
        size = other.size;
        vec = new int[size];
        for (int i = 0; i < size; i++) {
            vec[i] = other.vec[i];
        }
        return *this;
    }
    void SetSize(int n) {
        if (n < 1 || n > 20) {
            return;
        }
        if (n >= size)
        {
            int* vec1 = new int[n];
            memcpy(vec1, vec, size * sizeof(int));
            delete[] vec;
            size = n;
            vec = vec1;
        }
        else
        {
            delete[] vec;
            size = n;
            vec = new int[size] {0};
        }
    }
    void Size(int& len) const {
        len = size;
    }
    int& operator[](unsigned short index) {
        index %= size;
        return vec[index];
    }
    const int& operator[](unsigned short index) const {
        index %= size;
        return vec[index];
    }
    double len() {
        double sum = 0;

        for (int i = 0; i < size; i++) {
            sum += vec[i] * vec[i];
        }
        return sqrt(sum);
    }
    int dotS(const Vector& other) const {
        if (size != other.size) {
            return 0;
        }
        int dot = 0;
        for (int i = 0; i < size; i++)
            dot += vec[i] * other.vec[i];
        return dot;
    }
    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            return Vector();
        }
        Vector sum(size);
        for (int i = 0; i < size; i++)
            sum.vec[i] = vec[i] + other.vec[i];
        return sum;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector& Vec) {
        os << "(";
        for (int i = 0; i < Vec.size; i++)
        {
            os << Vec.vec[i];
            if (i < Vec.size - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }

    ~Vector() {
        delete[] vec;
    }
};

void main() {
    Vector v1, v2(3);
    v1.SetSize(3);
    for (int i = 0; i < 3; i++) {
        v1[i] = i;
        v2[i] = i * 2;
    }
    Vector v3 = v2 + v1;
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v2.len() << std::endl;
    std::cout << v2.dotS(v1) << std::endl;
    std::cout << v3 << std::endl;
}