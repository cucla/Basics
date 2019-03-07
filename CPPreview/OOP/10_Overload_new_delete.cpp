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
 *
 * MALLOC vs NEW
 * 1. new operator constructs the object and initializes allocated memory from heap memory by calling constructor 
 * where as malloc function does not, and allocate uninitialized memory.
 * 2. new can be overloaded but malloc cannot be.
 * 3. C++ syntax of using new is easy e.g int*p = new int; where as for malloc it is little bit complex e.g 
 * int *p= (int*)malloc(sizeof(int));
 * 4. new returns proper typed pointer and malloc returns void pointer which needs to be typecasted.
 * 5. No need to calculate the size of memory using sizeof() operator in case of “new”.
 * 6. new throws an exception on memory allocation failure and malloc returns NULL.
 * 7. heap memory allocated by new cannot be resized while memory allocated by malloc can be resized using realloc function.
 * 
 * If we don’t use delete but free() function, it will not call class destructor and memory leak may happen.
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
/* this pointer is not available to static method
 * friend function doesn’t have this pointer
 * this pointer is rvalue not lvalue, so, can’t access address of it
 *
 * Whenever we call a non-static member function of a class on some objects, a ‘this’ pointer get created and 
 * address of that object get stored in it and passed as a hidden argument to that function and in function 
 * body we can use this pointer as a local variable
 */

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
