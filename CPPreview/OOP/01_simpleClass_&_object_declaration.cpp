#include "stdafx.h"
#include <iostream>

/* OOP
 * - make one parameter ctor 'explicit'
 * - make accessors 'const'
 */

class IntCell {
public:
	IntCell() { storedValue = 0; }
	explicit IntCell(int initialValue) : storedValue{ initialValue } { }
	int read() const { return storedValue; }
	void write(int x) { storedValue = x; }
private:
	int storedValue;
};

int main()
{
	IntCell obj01;			// zero parameter ctor
	IntCell obj02{ };		// zero parameter ctor
	IntCell obj03( 3 );		// one parameter ctor
	IntCell obj04{ 4 };		// one parameter ctor

	std::cout << obj01.read() << std::endl;
	std::cout << obj02.read() << std::endl;
	std::cout << obj03.read() << std::endl;
	std::cout << obj04.read() << std::endl;

	// dynamic object creation
	IntCell * objPtr = nullptr;	
	objPtr = new IntCell();
	objPtr = new IntCell{ };
	objPtr = new IntCell;

	std::cout << objPtr->read() << std::endl;

	std::cin.get();
}

