#include <iostream>
using namespace std;

class DynamicArray {
private:
    double* a;  
    int n;      

public:
    DynamicArray() {
        a = nullptr;
        n = 0;
    }
   
    DynamicArray(int size) {
        n = size;
        a = new double[n];
        for (int i = 0; i < n; i++) {
            a[i] = 0;
        }
    }
    
    DynamicArray(const DynamicArray& b) {
        n = b.n;
        a = new double[n];
        for (int i = 0; i < n; i++) {
            a[i] = b.a[i];
        }
    }
 
    ~DynamicArray() {
            delete[] a;
        }

    DynamicArray& operator=(const DynamicArray& b) {
        if (this != &b) {
            delete[] a;
            n = b.n;
            a = new double[n];
            for (int i = 0; i < n; i++) {
                a[i] = b.a[i];
            }
        }
        return *this;
    }
     //1) задать размер массива
    void setSize(int newSize) {
        n = newSize;
        a = new double[n];
    }
   //2) узнать размер массива
    int getSize() {
        return n;
    }
  //3) задать элемент массива по его индексу
    void set(int index, double value) {
        if (index >= 0 && index < n) {
            a[index] = value;
        }
    }
// 4) узнать элемент массива по его индексу
    double get(int index) {
        if (index >= 0 && index < n) {
            return a[index];
        } 
    }
  //5) найти минимальный элемент массива
    double min() {
        double m = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] < m) {
                m = a[i];
            }
        }
        return m;
    }
  // 6) проверить, является ли массив упорядоченным
    bool sorted() {
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i-1]) {
                return false;
            }
        }
        return true;
    }
 // 7) выделить из массива подмассив с элементами с нечетными индексами
    DynamicArray oddIndexes() {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 1) count++;
        }
  
        DynamicArray res(count);
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 1) {
                res.set(index, a[i]);
                index++;
            }
        }
        return res;
    }
    
    void print() {
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << a[i];
            if (i < n-1) cout << ", ";
        }
        cout << "]\n";
    }
};

int main() {
    DynamicArray arr;
    arr.setSize(10);
    int size = arr.getSize();
    cout << "Размер массива arr равен " << size << "\n";
    cout << "Введите индекс элемента и значение\n ";
    int i;
    double el;
    cin >> i >> el;
    arr.set(i, el);
    arr.print();
    cout << "Введите индекс искомого элемента\n ";
    cin >> i;
    cout << "Элемент массива по индексу " << i << " = " << arr.get(i) << "\n";
    cout << "Минимальный элемент массива равен " << arr.min() << "\n";
    if (arr.sorted()) {
        cout << "Массив упорядоченный\n";
    } else {
        cout << "Массив неупорядоченный\n";
    }
    DynamicArray res = arr.oddIndexes();
    res.print();
}

