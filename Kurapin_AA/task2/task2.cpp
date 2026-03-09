#include <iostream>
#include <windows.h>
#include <algorithm>
#include <string>

class FloatArray {
private:
	size_t size = 0;
	float* array = nullptr;
public:
	FloatArray() {}
	FloatArray(size_t size_n) {
		size = size_n;

		array = (float*)malloc(size * sizeof(float));
	}
	FloatArray(std::initializer_list<float> list) {
		size = list.size();

		array = (float*)malloc(size * sizeof(float));

		size_t i = 0;
		for (float value : list) {
			array[i++] = value;
		}
	}
	FloatArray(const FloatArray &arr) {
		size = arr.size;
		array = (float*)malloc(size * sizeof(float));

		for (unsigned i = 0; i < size; i++) {
			array[i] = arr.array[i];
		}
	}
	~FloatArray() { free(array); }



	size_t Size() const { return size; }
	void Size(size_t size_n) { 
		if (size_n < size) {
			throw std::exception("");
		}
		else if (size_n > size) {
			array = (float*) realloc(array, size_n * sizeof(float));

			for (unsigned i = size; i < size_n; i++) {
				array[i] = 0;
			}

			size = size_n;
		}
	}


	FloatArray& operator=(const FloatArray& arr) {
		if (this != &arr) {
			free(array);

			size = arr.size;
			array = (float*)malloc(size * sizeof(float));
			
			for (unsigned i = 0; i < size; i++) {
				array[i] = arr.array[i];
			}
		}

		return *this;
	}
	float& operator[](unsigned index) {
		if (index >= size) {
			throw std::exception("");
		}
		return array[index];
	}
	const float operator[](unsigned index) const {
		if (index >= size) {
			throw std::exception("");
		}
		return array[index];
	}

	std::string to_string() const {
		std::string str = "[";
		if (size > 0) {
			str += std::to_string((unsigned)array[0]);

			for (unsigned i = 1; i < size; i++) {
				str += ", " + std::to_string((unsigned)array[i]);
			}
		}
		str += "]";

		return str;
	}

	float Min() const {
		if (size < 1) { return NULL; }

		float min = array[0];

		for (unsigned i = 0; i < size; i++) {
			if (array[i] < min) { min = array[i]; }
		}

		return min;
	}

	bool IsSorted() const {
		bool sorted = true;

		if (size > 1) {
			for (unsigned i = 0; i < size; i++) {
				if (array[i] > array[i + 1]) { sorted = false; }
			}
		}

		return sorted;
	}

	FloatArray OddIndex() const {
		if (size < 2) {
			return FloatArray();
		}

		size_t odd_size = (size - (size % 2)) / 2;

		FloatArray odd(odd_size);

		for (unsigned i = 0; i < odd_size; i++) {
			odd[i] = array[i * 2 + 1];
		}

		return odd;
	}

};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	FloatArray array{ 1, 2, 3 };

	std::cout << "size: " << array.Size() << " array[1]: " << array[1] << " min value: " << array.Min() << " sorted: " << array.IsSorted() << std::endl;
	std::cout << "array: " << array.to_string() << " odd index array: " << array.OddIndex().to_string() << std::endl;

	array.Size(5);
	array[3] = 4;
	std::cout << array.to_string() << std::endl;

	getchar();
}
