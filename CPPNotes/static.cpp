#include "stdafx.h"
#include <iostream>
#include <cstdio>

class S {
public:
	int static_value() {
		static int x = 7;
		return ++x;
	}
};

int & func(int & x) {
	++x;
	return x;
}

const int & func2(const int & x) {
	static int y = x;
	++y;
	return y;
}


int main() 
{
	// static act like global in a class
	S a;
	S b;
	printf("a.static_value() is %d\n", a.static_value());	// 8
	printf("a.static_value() is %d\n", a.static_value());	// 9
	printf("b.static_value() is %d\n", b.static_value());	// 10
	printf("b.static_value() is %d\n", b.static_value());	// 11

	// passing a reference
	int i = 5;
	printf("i is %d\n", func(i));	// 6
	printf("i is %d\n", func(i));	// 7
	printf("i is %d\n", func(i));	// 8
	printf("original is %d\n", i);	// 8 original

	i = 5;
	printf("i is %d\n", func2(i));	// 6
	printf("i is %d\n", func2(i));	// 7
	printf("i is %d\n", func2(i));	// 8
	printf("original is %d\n", i);	// 5 original



	std::cin.get();
}
