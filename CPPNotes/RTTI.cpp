// 1. dynamic_cast basic example #1
// 2. dynamic_cast usage example #2: pass pointer to base to an independent method and chack if an object is derived or base class

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
	b.f();			// Base::f()
	d.f();			// Derived::f()

	Base * ptrB = &b;
	Derived * ptrD = &d;
	ptrB->f();      // Base::f()
	ptrD->f();      // Derived::f()

	ptrB = &d;			// or ptrB = dynamic_cast<Base*>(&d); 
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

// 2. dynamic_cast usage example #2---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

class Window
{
public:
	Window(){}
	Window(const string s):name(s) {};
	virtual ~Window() {};
	void getName() { cout << name << endl;};
private:
	string name;
};

class ScrollWindow : public Window
{
public:
	ScrollWindow(string s) : Window(s) {};
	~ScrollWindow() {};
	void scroll() { cout << "scroll()" << endl;};
};

void DoSomething(Window *w)
{
	w->getName();
	// w->scroll();  // class "Window" has no member scroll

	// check if the pointer is pointing to a scroll window
	ScrollWindow *sw = dynamic_cast<ScrollWindow*>(w);

	// if not null, it's a scroll window object
	if(sw) sw->scroll();
}

int main()
{
	Window *w = new Window("plain window");
	ScrollWindow *sw = new ScrollWindow("scroll window");

	DoSomething(w);
	DoSomething(sw);

	return 0;
}
//------------------------------------------------------------------------------------------------

