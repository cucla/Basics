/* In constant function as declared above a pointer address cannot be modified but, the value 
 * pointed by that pointer can be modified. 
 */

#include "stdafx.h"
#include "iostream"


using namespace std;

class A {
private:
	int a;
	mutable int b;
	int * ptr;
public:
	void foo() {
		b = 3;
		ptr = &b;
		*ptr = 10;
		cout << "function: foo()\n";
		cout << "*ptr " << *ptr << endl;
		cout << "b " << b << endl;
	}
	void foo2() const {
		b = 3;
		*ptr = 100;
		cout << "const function: foo2()\n";
		cout << "*ptr " << *ptr << endl;
		cout << "b " << b << endl;
	}
};


int main() {
	A ob;
	ob.foo();
	ob.foo2();

	std::cin.get();
}





