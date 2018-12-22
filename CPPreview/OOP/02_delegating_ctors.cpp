#include "stdafx.h"
#include <iostream>
#include <math.h> 

/* OOP
 * - delegating ctors
 */

class Degree {
public:
	explicit Degree(int deg) {                                        
		degree = deg % 360;
		if (degree < 0) degree += 360;
	}
	Degree() : Degree(0) {}                                    
	Degree(double deg) : Degree(static_cast<int>(ceil(deg))) {}

	int read() const { return degree; }
private:
	int degree;
};

int main()
{
	Degree * myObj = new Degree{7.7};
	std::cout << myObj->read() << std::endl;

	std::cin.get();
}
