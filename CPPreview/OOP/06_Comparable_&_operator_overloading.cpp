#include "stdafx.h"
#include <iostream>
#include <vector>

/* OOP
 * Comparable class type -> must provide < and ==
 * + operator overloading via member functions;
 */

class Comparable {
public:
	explicit Comparable(int initial = 0) : val{initial} { }

	int getVal() const { return val; }
	bool operator< (const Comparable & rhs) const {
		return getVal() < rhs.getVal();
	}
	Comparable operator+ (const Comparable & rhs) const {
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

