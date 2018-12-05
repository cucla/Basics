// 1. dynamic_cast basic example #1
// 2. dynamic_cast or typeid: pass pointer to base to an independent method and chack if an object is derived or base class
// 3. 'override' (override not possible) non virtual function

/* When to use RTTI:
 * -> to call a specialized member function of a child class using base class pointer (2.)
 * -> to override a function from base class that is not virtual and we can’t make it virtual 
 *    as base class is sitting in a library (3.)
 *
 * Alternatives:
 * -> Virtual methods, puts the work within the object itself;
 * -> If the work belongs outside the object in some processing code, consider a double-dispatch solution, 
 *    such as the Visitor design pattern;
 */

// 1. dynamic_cast basic example #1---------------------------------------------------------------
#include "stdafx.h"
#include <iostream>


/* RTTI – Run time type identification
 * available only for polymorphic classes -> have at least 1 virtual method
 *
 * -> dynamic_cast -> safely converts from a pointer/reference to a base type to 
 *	  a pointer/reference to a derived type;
 * -> typeid -> returns the actual type of the object referred to by a pointer/reference
 *
 * Upcasting : derived-class reference/pointer to a base-class reference/pointer
 * Downcasting : base-class pointer/reference to a derived-class pointer/reference
 */


class Base {
public:
	virtual void f() { std::cout << "Base::f()" << std::endl; }
};

class Derived : public Base {
public:
	void f() { std::cout << "Derived::f()" << std::endl; }
};


int main() {

	Base b;
	Derived d;
	b.f();		// Base::f()
	d.f();		// Derived::f()

	Base * ptrB = &b;
	Derived * ptrD = &d;
	ptrB->f();      // Base::f()
	ptrD->f();      // Derived::f()

	ptrB = &d;		// or ptrB = dynamic_cast<Base*>(&d); 
	// ptrD = &b;		// not allowed
	ptrD = dynamic_cast<Derived *>(&b); // nullptr


	Base * pBDerived = new Derived;
	Base * pBBase = new Base;
	Derived * pd;

	pd = dynamic_cast<Derived *>(pBDerived);	// SUCCESS, pBDerived is pointing to a full object of class Derived
	pd = dynamic_cast<Derived *>(pBBase);		// nullptr, pBBase is pointing to an incomplete object of class Derived

	std::cin.get();
}
//------------------------------------------------------------------------------------------------

// 2. dynamic_cast or typeid: pass pointer to base to an independent method and chack------------- 
// if an object is derived or base class----------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <string>

class Base {
public:
	Base(const std::string & s) : name(s) {};
	virtual ~Base() {};
	void getName() { std::cout << name << std::endl; };
private:
	std::string name;
};

class Derived : public Base {
public:
	Derived(const std::string & s) : Base(s) {};
	~Derived() {};
	void scroll() { std::cout << "scroll()" << std::endl; };
};

void DoSomething(Base * w) {
	w->getName();

	// check if the pointer is pointing to a scroll window
	Derived * sw = dynamic_cast<Derived *>(w);
	if (sw)		// if not null
		sw->scroll();
}

void DoSomething2(Base * w) {
	w->getName();

	// check if two objects are the same
	if (typeid(Derived) == typeid(*w)) {
		Derived * sw = dynamic_cast<Derived *>(w);
		sw->scroll();
	}
	// Base b("plain window");
	// if (typeid(Derived) == typeid(b)) ...
}

int main() {
	Base * w = new Base("plain window");
	Derived * sw = new Derived("scroll window");

	DoSomething(w);
	DoSomething(sw);
	DoSomething2(w);
	DoSomething2(sw);
	std::cin.get();
}
//------------------------------------------------------------------------------------------------

// 3. 'override' (override not possible) non-virtual function-------------------------------------
#include "stdafx.h"
#include <iostream>
#include <string>

class Base {
public:
	Base(const std::string & s) : name(s) {};
	virtual ~Base() {};

	virtual void getName() { std::cout << "Base class " << name << std::endl; };
	void func2() { std::cout << "Base class func2()" << std::endl; }     //Not virtual  !!!!!!
private:
	std::string name;
};

class Derived : public Base {
public:
	Derived(const std::string & s) : Base(s) {};
	~Derived() {};
	void func2() { std::cout << "Derived class func2()" << std::endl; }
};

//client code
void DoSomething(Base * b) {
	Derived * d = dynamic_cast<Derived *>(b);
	if (d)		// if not null
		d->func2();
}

int main() {
	Base * w = new Base("plain window");
	Derived * sw = new Derived("scroll window");
	DoSomething(w);
	DoSomething(sw);

	std::cin.get();
}
//------------------------------------------------------------------------------------------------


