/* Overloaded NEW operator can accept additional arguments except size to be allocated.
 * In one class DELETE operator can be overloaded only once.
 * In one class NEW operator can be overloaded multiple times.
 *
 * DELETE calls the destructor before deallocating the memory; DO NOT `delete(this);` in a destructor, 
 * it wil couse endless recursion: this->~destructor, then delete(this) will again call this->~destructor...
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


