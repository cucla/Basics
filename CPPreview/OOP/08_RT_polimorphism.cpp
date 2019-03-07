#include "stdafx.h"
#include "iostream"



/* Run time polymorphism - function overriding where functions get resolved at run time from VTABLE.
*
* C++ compiler creates VTABLE at compile time & inserts a pointer v_ptr that holds the address of
* VTABLE in every class that has virtual function or class that inherits from the class that has a
* virtual function. VTABLE is an array of function pointers pointing to virtual functions. If Derived
* class is missing implementation, its VTABLE contains pointer to the function, implemented in a
* Base class.
* Virtual desturctor is used to maintain the destructors call order in a polymorphic class in an 
* inheritance hierarchy.
*
*
* RTTI – Run Time Type Information - allows the type of an object to be determined at run time.
*
* RTTI is included in VTABLE. Only for 
* POLYMORPHIC CLASS - has at least one virtual method;
* (ABSTRACT CLASS - has at least 1 pure virtual function, cannot be instantiated, but we can create pointer)
* RTTI is provided through two operators:
* dynamic_cast :	Used for type conversion of polymorphic types.
* typeid operator:  Used for identifying the exact type of an object.
*
*
* Upcasting   - converting a derived-class reference or pointer to a base-class reference or pointer,
*               it is always allowed for public inheritance without the need for an explicit type cast.
* Downcasting - is not allowed without an explicit type cast.
*/

using namespace std;

class Base {
public:
	Base() { cout << "Base_ctor" << endl; }
	virtual ~Base() { cout << "Base_destructor" << endl; }
	virtual void foo() { cout << "Base_foo()" << endl; }
	virtual void bar() { cout << "Base_bar()" << endl; }
};

class D1 : public Base {
public:
	D1() { cout << "D1_ctor" << endl; }
	~D1() { cout << "D1_destructor" << endl; }
	void foo() { cout << "D1_foo()" << endl; }
	void extra() { cout << "D1_extra()" << endl; }
};

class D2 : public Base {
public:
	D2() { cout << "D2_ctor" << endl; }
	~D2() { cout << "D2_destructor" << endl; }
	virtual void bar() { cout << "D2_bar()" << endl; }
};

class D3 : public D2 {
public:
	D3() { cout << "D3_ctor" << endl; }
	~D3() { cout << "D3_destructor" << endl; }
	void bar() { cout << "D3_bar()" << endl; }
};


// still upcasting: D3 Obj to D2 pointer
Base * f1() {
	Base * bPtr = new D3;
	D2 * dPtr = dynamic_cast<D2*>(bPtr);
	return dPtr;
}

// downcasting: D2 Obj to D3 pointer
Base * f2() {
	Base * bPtr = new D2;
	D3 * dPtr = dynamic_cast<D3*>(bPtr);
	return dPtr;
}


void DoSomething(Base * w) {
	// Base has no extra(), check if the pointer is pointing to D1
	D1 * ww = dynamic_cast<D1*>(w);
	if (ww) ww->extra();
}



int main() {
	Base * b = new D1;   // create an object of derived class to base class pointer
	b->foo();
	delete b;

	/* The first destructor called will be the one for the most derived object.
	* If Base ctor is not virtual:          If Base ctor is virtual:
	*
	* Base_ctor                             Base_ctor
	* D1_ctor                               D1_ctor
	* D1k_foo()                             D1_foo()
	*                                       D1_destructor
	* Base_destructor                       Base_destructor
	*/
	                  cout << endl;

	Base * bPtr1 = new Base;
	Base * bPtr2 = new D2;
	//D2 * cPtr = dynamic_cast<D2*>(bPtr1);  - nullptr, bPtr1 points to object of Base class
	D2 * cPtr = dynamic_cast<D2*>(bPtr2);

	/* bPtr2 & cPtr are copies of each other; if base class destructor is virtual,
	 * can delete any of them
	 */

	delete bPtr2;
	delete bPtr1;
	                  cout << endl;

	Base bObj;
	D2 cObj;
	bPtr2 = &cObj;
	cPtr = dynamic_cast<D2*>(&bObj);  // base-to-derived conversion, downcasting, gives nullptr
	                  
	                  cout << endl;
	
	f1()->foo();     // "Base_foo()"
	f1()->bar();     // "D3_bar()"
	//f2()->bar();   error: downcasting - D2 Obj to D3 pointer
	                  cout << endl;

	Base * b01 = new Base;
	D1 * d01 = new D1;
	DoSomething(b01);
	DoSomething(d01);

	Base bb;
	D1 dd;
	if (typeid(D1) == typeid(dd)) {
		D1 * p = (D1 *)&dd;
		p->extra();
	}

	std::cin.get();
}




