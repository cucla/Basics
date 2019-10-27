#include "stdafx.h"
#include <iostream>
#include <vector>


class MyClass {
public:
	MyClass() { }

	static std::vector<int> pre_creator() {
		std::vector<int> _vect = { 1, 1, 1 };
		return _vect;
	}

	static std::vector<int> & creator() {
		static auto __vect = pre_creator();
		return __vect;
	}

	std::vector<int> & my_vect = creator();
};


int main()
{
	MyClass a, b, c, d;

	for (auto el : a.my_vect) { std::cout << el << "_"; } std::cout << std::endl;
	b.my_vect[0] = 100;
	for (auto el : b.my_vect) { std::cout << el << "_"; } std::cout << std::endl;
	b.my_vect[2] = 200;
	for (auto el : c.my_vect) { std::cout << el << "_"; } std::cout << std::endl;
	for (auto el : d.my_vect) { std::cout << el << "_"; }

	std::cin.get();
}

