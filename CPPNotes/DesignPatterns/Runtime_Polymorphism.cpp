/* 
 * Runtime polymorphism -
 * is function overriding where functions get resolved at run time;
 * the compiler determines the type of object at runtime;
 *
 * Virtual Function -
 * is overrided in the derived class, the compiler performs Late Binding on this function;
 * 
 * Static type - 			Dynamic type (of an expression that is a reference or a pointer) -
 * is always known at compile time;  	the type of the object in memory, may not be known until run time;
 *
 * Derived x;
 * Base * item = &x;		// ok
 * Derived * new_item = item; 	// ERROR, use cast
 *
 * -> Derived-to-base conversion applies only to pointer or reference types;
 * -> There is no implicit base-to-derived conversion
 *
 * -> Derived class includes body only for the functions it intends to define;
 * -> Dynamic binding happens when a vitrual function is called through:
 *		- a reference (someMethod());
 *		- a pointer (* bp[4]);
 *		!! FROM A PUBLICLY DERIVED CLASS !!
 * -> Base classes should define virtual destructors;
 * -> Any nonstatic function, other than constructor, can be virtual;
 * -> If need static member, shared across all classes -> initialize outside the class (Base::count = 0);
 */

class Base {
public:
	Base() { addCount(); }
	virtual void show() const { std::cout << "In Base" << std::endl; }
	virtual void showmore() const { std::cout << "More In Base" << std::endl; };
	virtual ~Base() {}

	// example of a static field
	static int count;				// static data member
	static void addCount() { ++count; }		// static member function
};

int Base::count = 0;


class Derived1 : public Base {
public:
	Derived1() { addCount(); }
	void show() const { std::cout << "In Derived 1" << std::endl; }
};

class Derived2 : public Base {
public:
	Derived2() { addCount(); }
	void show() const { std::cout << "In Derived 2" << std::endl; }
};

class Derived3 : public Base {
public:
	Derived3() { addCount(); }
	void show() const override; 
};

void Derived3::show() const { std::cout << "In Derived 3" << std::endl; }


void someMethod(const Base & obj) {
	obj.show();
}


int main() {
	Base * bp[4];
	bp[0] = new Base();
	bp[1] = new Derived1();
	bp[2] = new Derived2();
	bp[3] = new Derived3();

	for (size_t i = 0; i < 4; i++) {
		bp[i]->show();
		std::cout << bp[i]->count << std::endl;
	}
	someMethod(*bp[1]);

	std::cin.get();
}

// In order for each derived class to get their own static variable, you'll need to 
// declare another static variable with a different name:
class Base {
    static int staticVarInst;
public:
    virtual int & staticVar() { return staticVarInst; }
}
class Derived: public Base {
    static int derivedStaticVarInst;
public:
    virtual int & staticVar() { return derivedStaticVarInst; }
}

// Can "achieve dynamic binding with a static function, if wrap it in a non-static function
class Base {
public:
     static void print() { cout << "base class static function" << endl; }
     virtual void dynamic_print() { Base::print(); }
};

class Derived : public Base {
public:
     static void print() { cout << "derived class static function" << endl; }
     virtual void dynamic_print() { Derived::print(); }
};

