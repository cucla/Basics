/* Algorithm to parse char array for not matching opening or clothing parenthesis, using stack
 *
 * To loop char array:
 *
 * const char * expr1{ "((A + B) / C" };
 * while (*expr1) {
 *    cout << *expr1;
 *    ++expr1;
 */

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

void parseParentheses(const char * expr) {
	LlistStack<char> stack;

	while (*expr) {
		if (*expr == '(')
			stack.push(*expr);
		else if (*expr == ')')
			if (!stack.isEmpty())
				stack.pop();
			else
				std::cout << "Closing parenthesis not matched\n";
		++expr;
	}
	if (!stack.isEmpty())
		std::cout << "Opening parenthesis not matched\n";

	stack.clear();
}


int main()
{
	const char * expr1{ "((A + B) / C" };
	const char * expr2{ "(A + B) / C)" };

	parseParentheses(expr1);
	parseParentheses(expr2);

	std::cin.get();
}
