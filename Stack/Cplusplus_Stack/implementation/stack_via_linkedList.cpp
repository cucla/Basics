// One disadvantage of using an array to implement a stack is the wasted space---most of the time most of the array is unused. 
// A more elegant and economical implementation of a stack uses a linked list

#include "stdafx.h"
#include <iostream>
#include <stdexcept>


template<class T>
class LlistStack {
public:
	LlistStack();
	~LlistStack() { clear(); }
	bool push(T data);
	bool pop();
	T & top();
	bool isEmpty() const { return _topOfStack == NULL; }
	void clear();
	int size() const;
private:
	struct Node {
		T _data;
		Node * _link;
	};
	Node * _topOfStack;
	int _count;
};

template<class T>
LlistStack<T>::LlistStack() {
	_topOfStack = NULL;
	_count = 0;
}

template<class T>
bool LlistStack<T>::push(T data) {
	Node * newNode = new Node;
	newNode->_data = data;
	newNode->_link = _topOfStack;

	_topOfStack = newNode;	
	++_count;
	return true;
}

template<class T>
bool LlistStack<T>::pop() {
	if (isEmpty())
		return false;

	Node * tmp = _topOfStack;
	_topOfStack = _topOfStack->_link;
	delete tmp;
	--_count;
	return true;
}

template<class T>
T & LlistStack<T>::top() {
	if (isEmpty())
		throw std::runtime_error("Stack is empty");

	return _topOfStack->_data;
}

template<class T>
void LlistStack<T>::clear() {
	while (!isEmpty())
		pop();
}

template<class T>
int LlistStack<T>::size() const {
	return _count;
}



int main()
{
	LlistStack<int> stack02;
	stack02.push(70);
	stack02.push(80);
	stack02.push(90);

	stack02.pop();

	stack02.top() += 5;

	std::cout << "Top element is: " << stack02.top() << std::endl;
	std::cout << "Stack size is " << stack02.size() << std::endl;


	std::cin.get();
}
