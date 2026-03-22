#include <iostream>
#include <cmath>

class Vector {
private:
    int* data;
    size_t size;
public:
    Vector(size_t n) : size(0), data(nullptr) {
        if (n >= 1 && n <= 20) {
            size = n;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = 0;
            }
        }
        else {
            std::cerr << "Error.\n";
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    size_t getSize() const {
        return size;
    }

    void resize(size_t new_size) {
        if (new_size >= 1 && new_size <= 20) {
            int* temp_data = new int[new_size];
            size_t min_size = std::min(new_size, size);
            for (size_t i = 0; i < min_size; ++i) {
                temp_data[i] = data[i];
            }
            delete[] data;
            data = temp_data;
            size = new_size;
        }
        else {
            std::cerr << "Error.\n";
        }
    }

    int getElement(size_t idx) const {
        if (idx < size) {
            return data[idx];
        }
        else {
            std::cerr << "Error.\n";
            return 0;
        }
    }

    void setElement(size_t idx, int val) {
        if (idx < size) {
            data[idx] = val;
        }
        else {
            std::cerr << "Error.\n";
        }
    }

    int length() const {
        int sum = 0;
        for (size_t i = 0; i < size; ++i) {
            sum += (data[i]) * data[i];
        }
        return std::sqrt(sum);
    }

    int scalarProduct(const Vector& other) const {
        if (size != other.size) {
            std::cerr << "Error.\n";
            return 0;
        }

        int result = 0;
        for (size_t i = 0; i < size; ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector addVectors(const Vector& other) const {
        if (size != other.size) {
            std::cerr << "Error.\n";
            return Vector(0);
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    void print() const {
        if (size > 0) {
            std::cout << "The vector: ";
            for (size_t i = 0; i < size; ++i) {
                std::cout << data[i];
            }
            std::cout << "\n";
        }
        else {
            std::cout << "Error.\n";
        }
    }
};


int main()
{
    Vector v(5);
    std::cout << "Size: " << v.getSize() << "\n";
    v.print();

    v.setElement(0, 3);
    std::cout << "First element: " << v.getElement(0) << "\n";

    std::cout << "Lenght: " << v.length() << "\n";


    Vector v1(3);
    Vector v2(3);

    v1.setElement(0, 1);
    v1.setElement(1, 2);
    v1.setElement(2, 3);

    v2.setElement(0, 4);
    v2.setElement(1, 5);
    v2.setElement(2, 6);

    std::cout << "First vector:\n";
    v1.print();

    std::cout << "Second vector:\n";
    v2.print();

    //Vector sum_vector = v1.addVectors(v2);
    //std::cout << "Sum:\n";
    //sum_vector.print();

    //Vector v3 = v1;
    //std::cout << "Third vector:\n";
    //v3.print();

    return 0;
}