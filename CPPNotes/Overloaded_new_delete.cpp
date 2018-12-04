#include "stdafx.h"
#include <iostream>


/* 
 * Overloaded 'new' and 'delete' operators are static, without access to this pointer
 * Overloaded 'new' operator can accept additional arguments except size to be allocated
 * In one class 'delete' operator can be overloaded only once
 * In one class 'new' operator can be overloaded multiple times
 *
 * -> if overloaded 'new' operator in the class -> 'new' called first -> ctor
 * -> destructor will be called first -> then overloaded delete operator
 */


class A {
public:
	A() {}
	A(int a, int b) : _a(a), _b(b) {}

	// receives size of type size_t, which specifies the number of bytes of memory to be allocated
	// returns a pointer to the beginning of the block of memory allocated
	void * operator new(size_t objSize);
	void * operator new(size_t objSize, int x);

	// receives a parameter of type void * which has to be deleted
	// should not return anything
	void operator delete(void * ptr);
private:
	int _a = 0;  // size 4 byte
	int _b = 0;  // size 4 byte
};

void * A::operator new(size_t objSize) {
	std::cout << "Custom memory allocation with size " << objSize << std::endl;
	return malloc(objSize);
}

void * A::operator new(size_t objSize, int x) {
	std::cout << "Custom 2 agrument memory allocation with size " << objSize << std::endl;
	A * ptr = (A *)malloc(objSize);
	ptr->_a = x;
	return ptr;
	// can add exception handling routine
}

void A::operator delete(void * ptr) {
	std::cout << "Custom memory de-allocation" << std::endl;
	free(ptr);
	// delete may overwrite deallocated memory with zeros in order to increase the security
}



int main() {

	A * obj = new A();
	A * obj2 = new(55) A();

	delete obj;
	obj = nullptr;

	delete obj2;
	obj2 = nullptr;


	std::cin.get();
}


