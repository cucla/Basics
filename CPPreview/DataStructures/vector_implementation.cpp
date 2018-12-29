#include "stdafx.h"
#include "iostream"
#include <vector>

// implementation doesn't contain error checks

template<typename Object>
class myVector {
public:
	// if in ctor all the parameters have default values -> default ctor
	explicit myVector(int size = 0) :
		_size{ size },
		_capasity{ size + SPARE_CAPACITY }
	{
		_buff = new Object[_capasity]{};   // {} -> value-initialize items
	}

	myVector(const myVector & rhs) :
		_size{ rhs._size },
		_capasity{ rhs._capasity },
		_buff{ nullptr }
	{
		_buff = new Object[_capasity];
		for (int i = 0; i < _size; i++) {
			_buff[i] = rhs._buff[i];
		}
	}

	myVector(myVector && rhs) noexcept :
	_size{ rhs._size },
		_capasity{ rhs._capasity },
		_buff{ rhs._buff }
	{
		rhs.reset();
	}

	~myVector() { reset(); }

	myVector & operator= (const myVector & rhs) {
		myVector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	myVector & operator= (myVector && rhs) {
		std::swap(_size, rhs._size);
		std::swap(_capasity, rhs._capacity);
		std::swap(_buff, rhs._buff);
		return *this;
	}

	void reset() {
		delete[] _buff;
		_buff = nullptr;
		_size = 0;
		_capasity = 10;
	}

	int size() const { return _size; }
	int capacity() const { return _capacity; }
	bool empty() const { return _size == 0; }

	void resize(int newSize) {
		if (newSize > _capasity)
			reserve(newSize * 2);
		_size = newSize;
	}
	void reserve(int newCapacity) {
		if (newCapacity < _size) return;

		Object * tmp = new Object[newCapacity];
		for (int i = 0; i < _size; i++) {
			tmp[i] = std::move(_buff[i]);
		}

		_capasity = newCapacity;
		std::swap(_buff, tmp);
		delete[] tmp;
	}

	myVector & operator[] (int index) { return _buff[index]; }
	const myVector & operator[] (int index) const { return _buff[index]; }

	void push_back(const Object & item) {
		if (_size == _capasity)
			reserve(_capasity * 2 + 1);
		_buff[_size++] = item;
	}

	void push_back(Object && item) {
		if (_size == _capasity)
			reserve(_capasity * 2 + 1);
		_buff[_size++] = std::move(item);
	}

	void pop_back() { --_size; }

	const Object & back() const { return _buff[_size - 1]; }
	const Object & front() const { return _buff[0]; }

	typedef Object * iterator;
	typedef const Object * const_iterator;

	iterator begin() { return &_buff[0]; }
	const_iterator begin() const { return &_buff[0]; }
	iterator end() { return &_buff[size()]; }
	const_iterator end() const { return &_buff[size()]; }

	void print(std::ostream & os = std::cout) const {
		for (int i = 0; i < _size; i++) {
			os << _buff[i] << " ";
		}
	}

	static const int SPARE_CAPACITY = 16;

private:
	Object * _buff = nullptr;
	int _size;
	int _capasity;
};

template<typename Object>
std::ostream & operator<< (std::ostream & out, const myVector<Object> & rhs) {
	rhs.print(out);
	return out;
}


void printVect(const std::vector<int> & v) {
	for (auto el : v) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> libV01;				printVect(libV01);
	std::vector<int> libV02(5);				printVect(libV02);
	std::vector<int> libV03(5, 100);			printVect(libV03);
	std::vector<int> libV04 = libV03;			printVect(libV04);
	std::vector<int> libV05(libV03);			printVect(libV05);
	std::vector<int> libV06{ 1, 2, 3, 4, 5, 6 };		printVect(libV06);
	std::vector<int> libV07 = { 1, 2, 3, 4, 5, 6 };		printVect(libV07);


	std::cout << "myVector: " << std::endl;
	myVector<int> v01;					std::cout << v01 << std::endl;
	myVector<int> v02(5);					std::cout << v02 << std::endl;

	myVector<int> v04 = v02;				std::cout << v04 << std::endl;
	myVector<int> v05(v02);					std::cout << v04 << std::endl;

	myVector<double> vd02(5);				std::cout << "D " << vd02 << std::endl;

	std::cin.get();
}
