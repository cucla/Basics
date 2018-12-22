#include "stdafx.h"
#include <iostream>
#include <math.h> 

/* OOP
 * - inheriting ctors
 */

class Degree {
	// ... data and lots of nice constructors ...
public:
	explicit Degree(int deg) {                                        
		degree = deg % 360;
		if (degree < 0) degree += 360;
	}
	Degree() : Degree(0) {}                                    
	Degree(double deg) : Degree(static_cast<int>(ceil(deg))) {}

	int read() const { return degree; }
protected:
	int degree;
};

class Derived1 : public Degree {
	// ... no data members ...
	// ... lots of nice utility functions ...
public:
	using Degree::Degree;
};

struct Derived2 : public Degree {
	// if derived class has own members, they are uninitialised with inherited ctors
public:
	using Degree::Degree;
	Derived2(int deg, int x) : _x(x), Degree(deg) { }
	void read() const { std::cout << degree << " " << _x << std::endl; }
private:
	int _x;
};

int main()
{
	Degree * myObj = new Degree{7.7};
	std::cout << myObj->read() << std::endl;

	Derived1 * myObj2 = new Derived1{ 5 };
	std::cout << myObj2->read() << std::endl;

	Derived2 * myObj3 = new Derived2{ 10, 11 };
	myObj3->read();

	std::cin.get();
}

