#include "stdafx.h"
#include "iostream"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <string.h>



template<typename Object>
class myVector {
public:
	myVector() { reset(); } 

	explicit myVector(int size = 0) : 
		_size{ size }, 
		_capasity{ size + SPARE_CAPACITY } 
	{
		_buff = new Object[_capasity];
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

std::ostream & operator<< (std::ostream & out, const myVector<int> & rhs) {
	rhs.print(out);
	return out;
}


int main() {

	myVector<int> v(5);
	std::cout << v << std::endl;



	std::cin.get();
}

