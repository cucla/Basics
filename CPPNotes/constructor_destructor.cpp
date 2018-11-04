#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const string unk = "unknown";
const string clone_prefix = "clone-";

// -- interface --
class Animal {
public:
	Animal();   // default constructor
	Animal(const string & type, const string & name, const string & sound);

	Animal(const Animal &); // copy constructor
	Animal & operator=(const Animal &); // copy operator
	~Animal();  // destructor
	void print() const;
private:
	string _type = "";
	string _name = "";
	string _sound = "";
};


Animal::Animal() : _type(unk), _name(unk), _sound(unk) {
	puts("default constructor");
}

Animal::Animal(const string & type, const string & name, const string & sound)
	: _type(type), _name(name), _sound(sound) {
	puts("constructor with arguments");
}

Animal::Animal(const Animal & a) {
	puts("copy constructor");
	_name = clone_prefix + a._name;
	_type = a._type;
	_sound = a._sound;
}

Animal::~Animal() {
	printf("destructor: %s the %s\n", _name.c_str(), _type.c_str());
}

void Animal::print() const {
	printf("%s the %s says %s\n", _name.c_str(), _type.c_str(), _sound.c_str());
}

Animal & Animal::operator=(const Animal & o) {
	puts("assignment operator");
	if (this != &o) {
		_name = clone_prefix + o._name;
		_type = o._type;
		_sound = o._sound;
	}
	return *this;
}

int main(int argc, char ** argv) {
	Animal a;
	a.print();

	const Animal b("goat", "bob", "baah");
	b.print();

	puts("\nVia pointer:");
	Animal * prtA = new (nothrow) Animal; //default constructor is called
	prtA->print();
	Animal * prtA2 = new (nothrow) Animal("goat2", "bob2", "baah2");
	prtA2->print();
	//delete prtA2
	Animal * prtA3 = new (nothrow) Animal[3]; //array of objects, initialized via default constructor
	//delete[] ptrA3;

	const Animal c = b;
	c.print();

	a = c;
	a.print();

	std::cin.get();
}


