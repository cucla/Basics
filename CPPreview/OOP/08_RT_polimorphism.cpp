#include "stdafx.h"
#include "iostream"


/* Run time polymorphism - function overriding where functions get resolved at run time from VTABLE.
 *
 * C++ compiler creates VTABLE at compile time & inserts a pointer v_ptr that holds the address of 
 * VTABLE in every class that has virtual function or class that inherits from the class that has a 
 * virtual function. VTABLE is an array of function pointers pointing to virtual functions. If Derived
 * class is missing implementation, its VTABLE contains pointer to the function, implemented in a 
 * Base class.
 */
 

using namespace std;

class Bank {
public:
	Bank() { cout << "Bank_ctor" << endl; }
	virtual ~Bank() { cout << "Bank_destructor" << endl; }
	virtual void getAccountType() { cout << "Bank_getAccountType()" << endl; }
	virtual void getRateOfInterest() { cout << "Bank_getRateOfInterest()" << endl; }
};

class DeutscheBank : public Bank {
public:
	DeutscheBank() { cout << "DeutscheBank_ctor" << endl; }
	~DeutscheBank() { cout << "DeutscheBank_destructor" << endl; }
	void getAccountType() { cout << "DeutscheBank_getAccountType()" << endl; }
};

class CITI :public Bank {
public:
	CITI() { cout << "CITI_ctor" << endl; }
	~CITI() { cout << "CITI_destructor" << endl; }
	void getRateOfInterest() { cout << "CITI_getRateOfInterest()" << endl; }
};


int main() 
{ 
	Bank * b = new DeutscheBank;   // create object of derived class to base class pointer
	b->getAccountType();

/* If getAccountType() is virtual in Bank class -> derived class function is called,
 * if getAccountType() is not virtual in Bank class -> base class function is called
 */
	delete b;

/* If Bank ctor is not virtual:          If Bank ctor is virtual:
 *
 * Bank_ctor                             Bank_ctor
 * DeutscheBank_ctor                     DeutscheBank_ctor
 * DeutscheBank_getAccountType()         DeutscheBank_getAccountType()
 *                                       DeutscheBank_destructor
 * Bank_destructor                       Bank_destructor
 */

	std::cin.get();
}

