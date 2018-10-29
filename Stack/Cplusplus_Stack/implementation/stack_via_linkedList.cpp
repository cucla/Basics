// TEMPLATE CLASS with a FRIEND function

// One disadvantage of using an array to implement a stack is the wasted space---most of the time most of the array is unused. 
// A more elegant and economical implementation of a stack uses a linked list

#include "stdafx.h"
#include <iostream>


template<class T>	// forward declaration to enable friend function
class LlStack;

template<class T>	// forward declaration to enable friend function
void print(const LlStack<T> & s);

template<class T>
class LlStack {
public:
	LlStack();
	~LlStack() { clear(); }
	bool push(T el);
	bool pop();
	T & top();
	int count() const { return _count; }
	bool isEmpty() const { return _topNode == NULL; }
	void clear();

	friend void print<T>(const LlStack<T> & s);
private:
	struct Node {
		T _data;
		Node * _link;
	};
	Node * _topNode;
	int _count;
};

template<class T>
LlStack<T>::LlStack() {
	_topNode = NULL;
	_count = 0;
}

template<class T>
bool LlStack<T>::push(T el) {
	Node * newNode = new Node;
	newNode->_data = el;
	newNode->_link = _topNode;
	_topNode = newNode;
	++_count;

	return true;
}

template<class T>
bool LlStack<T>::pop() {
	if (isEmpty())
		return false;
	Node * tmp = _topNode;
	_topNode = _topNode->_link;
	delete tmp;
	--_count;

	return true;
}

template<class T>
T & LlStack<T>::top() {
	if (!isEmpty())
		return _topNode->_data;
}

template<class T>
void LlStack<T>::clear() {
	while (!isEmpty()) 
		pop();
}

template<class T>
void print(const LlStack<T> & s) {

	LlStack<T>::Node * cur = s._topNode;
	while (cur) {
		std::cout << cur->_data << " ";
		cur = cur->_link;
	}
	std::cout << std::endl;
}


int main()
{
	LlStack<int> * st = new LlStack<int>;
	st->push(10);
	st->push(20);
	st->push(30);

	st->pop();
	st->top() += 5;

	print<int>(*st);
	std::cout << "Top element is: " << st->top() << std::endl;
	std::cout << "Number of elements in a stack: " << st->count() << std::endl;
	//--------------------------------------------------------

	LlStack<int> st2;
	st2.push(100);
	st2.push(200);
	st2.push(300);

	st2.pop();
	st2.top() += 5;

	std::cout << "Top element is: " << st2.top() << std::endl;
	std::cout << "Number of elements in a stack: " << st2.count() << std::endl;


	std::cin.get();
}

