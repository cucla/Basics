// The derived function Derived::hidden_foo() hides all members with the same name from the base class. 
// So you can only use the base class member via scope resolution. To avoid hiding -> 'using'

class Base {
public:
	void not_virtual_foo() { std::cout << "base" << std::endl; }
	virtual void virtual_foo() { std::cout << "base virtual" << std::endl; }

	void hidden_foo() { std::cout << "base hidden foo" << std::endl; }
};

class Derived : public Base {
public:
	void not_virtual_foo() { std::cout << "derived" << std::endl; }
	void virtual_foo() { std::cout << "derived virtual" << std::endl; }

	using Base::hidden_foo;
	void hidden_foo(int param) { std::cout << "derived hidden foo -> " << param << std::endl; }
};


int main() 
{
	Derived bar;
	bar.not_virtual_foo();			// "derived"
	bar.Base::not_virtual_foo();		// "base";   using a qualified-id

	Base* bar2 = new Derived;
	bar2->not_virtual_foo();		// "base"
	//bar2->Derived::not_virtual_foo();	// error

	bar2->virtual_foo();			// "derived virtual"
	bar2->Base::virtual_foo();		// "base virtual";  using a qualified-id


	// Base::hidden_foo() isn't directly usable from derived without the 'using' declaration
	bar.hidden_foo();			// "base hidden foo"
	bar.hidden_foo(4);			// "derived hidden foo -> "
}
