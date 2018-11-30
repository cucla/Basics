/* 
 * Pure virtual function -
 * is a virtual function with the expression " = 0" appended to it's declaration;
 * must be defined or have to be implemented in ALL derived classes;
 *
 * Abstract class -
 * is a class that contains at least 1 pure virtual function and cannot be instantiated;
 * may also contain non-virtual functions and member variables;
 *
 * -> An abstract class can have constructors
 * -> We cannot create the object of an abstract class, but we can create the pointer/reference
 *    of this class and assign the object of derived classes;
 * -> If we do not override the pure virtual function in derived class, 
 *    then derived class also becomes abstract class
 */

class AbstractBase {
	std::string s1 = "water";
	std::string s2 = "sugar";
	void printInfo() { std::cout << s1 << "\n" << s2 << std::endl; }
public:
	AbstractBase() { std::cout << "AbstractBase class" << std::endl; }
	void showCommonInfo() { printInfo(); }
	virtual void showMore() = 0;
};


class Derived1 : public AbstractBase {
	std::string s1 = "tee";
public:
	Derived1() { std::cout << "Derived 1 for tee:" << std::endl; }
	void showMore() { std::cout << s1 << std::endl; }
};

class Derived2 : public AbstractBase {
	std::string s1 = "coffee";
public:
	Derived2() { std::cout << "Derived 2 for coffee:" << std::endl; }
	void showMore() { std::cout << s1 << std::endl; }
};


int main() {
	AbstractBase * bp[2];
	bp[0] = new Derived1();		// "Derived 1 for tee:"
	bp[1] = new Derived2();		// "Derived 2 for coffee:"

	for (size_t i = 0; i < 2; i++) {
		bp[i]->showCommonInfo();
		bp[i]->showMore();
	}

	std::cin.get();
}

//OUTPUT:
AbstractBase class
Derived 1 for tee:
AbstractBase class
Derived 2 for coffee:
water
sugar
tee
water
sugar
coffee
