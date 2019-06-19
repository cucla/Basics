#include "stdafx.h"
#include <iostream>
#include <vector>

/* OOP
 * Comparable class type -> must provide operator< and operator=
 * + operator overloading via member functions;
 
 * There are two ways to overload a binary operator like << (binary because it takes two operands, one on the 
 * left side and one on the right, left << right). One is to make it a member of the type of left and give it 
 * a single parameter of the type of right. The other is to make it a non-member function with two parameters, 
 * one the type of left and the other the type of right.
 */

class Comparable {
public:
	explicit Comparable(int initial = 0) : val{initial} { }

	int getVal() const { return val; }
	bool operator< (const Comparable & rhs) const {			// operator<
		return getVal() < rhs.getVal();
	}
	Comparable operator+ (const Comparable & rhs) const {		// operator+
		return Comparable(getVal() + rhs.getVal());
	}

	void print(std::ostream & os = std::cout) const {
		os << "value is : " << getVal() << "\n";
	}
private:
	int val;
};

// define output operator
std::ostream & operator<< (std::ostream & out, const Comparable & rhs) {
	rhs.print(out);
	return out;
}

int main()
{
	Comparable a{ 3 };		
	Comparable b{ 9 };	
	Comparable c = a + b;	

	bool result = a < b;
	std::cout << result << std::endl;
	std::cout << a << b << c << std::endl;

	std::vector<Comparable> v({ Comparable{ 1 }, Comparable{ 2 }, Comparable{ 22 } });
	for (auto el : v) {
		std::cout << el;
	}

	std::cin.get();
}

