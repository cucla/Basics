/* Overloaded NEW operator can accept additional arguments except size to be allocated.
 * In one class DELETE operator can be overloaded only once.
 * In one class NEW operator can be overloaded multiple times.
 *
 * DELETE calls the destructor before deallocating the memory; DO NOT `delete(this);` in a destructor, 
 * it wil couse endless recursion: this->~destructor, then delete(this) will again call this->~destructor...
 *
 * We can delete “this” pointer inside a member function only if the function call is made by the class 
 * object that has been created dynamically i.e. using “new” keyword. 
 * If we call the function using statically allocated object then a runtime crash will happen.
 */

#include "stdafx.h"
#include "iostream"


using namespace std;

class CustomMemory {

	int i;   // size of int is 4 bytes
public:
	CustomMemory() { cout << "Constructor" << "\n"; }
	~CustomMemory() { cout << "Destructor" << "\n"; }

	void * operator new(size_t objectSize) {
		cout << "Custom memory allocation" << "\n";
		return malloc(objectSize);
	}

	void * operator new(size_t objectSize, int x) {
		cout << "Custom 2 argument memory allocation" << "\n"; 
		CustomMemory * ptr = (CustomMemory*)malloc(objectSize); 
		ptr->i = x;
		return ptr;
	}

	void operator delete(void* ptr) {
		cout << "Custom memory de-allocation" << "\n";
		free(ptr);
	}

	void Display() { cout << "Value of i = " << i << "\n"; }
};


int main() {
	CustomMemory * obj01 = new CustomMemory();
	obj01->Display();
	delete obj01;

	CustomMemory * obj02 = new(5)CustomMemory();
	obj02->Display();
	delete obj02;

	std::cin.get();
}


Custom memory allocation
Constructor
Value of i = -842150451
Destructor
Custom memory de-allocation
Custom 2 argument memory allocation
Constructor
Value of i = 5
Destructor
Custom memory de-allocation

//---------------------------------------------------------------------------------------

class Test {
public:
	void function() {
		delete this;
		cout << "Object deleted\n";
	}
};

int main() {
	//Test object;
	//object.function();

	Test * pointer = new Test(); 
	pointer->function();
}
