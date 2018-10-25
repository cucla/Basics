// If stack's max size can be calculated

//-----------------------HEADER-----------------------
#pragma once
#define CAPACITY 100

template<typename T>
class ArrStack {
public:
	ArrStack(int max = CAPACITY);
	~ArrStack();
	bool push(T el);
	bool pop();
	T & top();
	int size() const;
	bool isEmpty() const { return _top < 0; }
	bool isFull() const { return _top + 1 == _capacity; }
private:
	// to decide max size at run-time -> use * to a dynamically-allocated array
	T * _buffer;
	int _top{ -1 };
	int _capacity;
};
//----------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Header.h"

template<class T>
ArrStack<T>::ArrStack(int max) {
	_buffer = new T[max];
	this->_capacity = max;

	if (!_buffer) {
		throw std::string("Insufficient memory to initialize stack");
	}
}

template<class T>
ArrStack<T>::~ArrStack() {
	delete[] _buffer;
	_buffer = NULL;
	_top = -1;
}

template<class T>
bool ArrStack<T>::push(T el) {
	if (!isFull()) {
		_buffer[++_top] = el;
		return true;
	}
	return false;
}

template<class T>
bool ArrStack<T>::pop() {
	if (!isEmpty()) {
		--_top;
		return true;
	}
	return false;
}

template<class T>
T & ArrStack<T>::top() {
	if (isEmpty())
		throw std::string("Stack is empty");
	return _buffer[_top];
}

template<class T>
int ArrStack<T>::size() const {
	return _top + 1;
}


int main() {

	ArrStack<int> stack01(5);
	stack01.push(10);
	stack01.push(20);
	stack01.push(30);
	stack01.pop();
	stack01.top() += 5;

	std::cout << "Top element is: " << stack01.top() << std::endl;
	std::cout << "Stack size is " << stack01.size() << std::endl;

	std::cin.get();
}
