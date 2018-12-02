/* Copy-and-swap idiom: uses copy ctor
 * 1. add method:
 * 	void Rational::swap(Rational & other) {
 *	   std::swap(_d, other._d);
 *	   std::swap(_n, other._n); }
 *
 * 2. change 'assignment' operator
 		    FROM								TO
	 Rational & Rational::operator = (const Rational & rhs) {	Rational & Rational::operator = (Rational other) {
		message("assignment");						message("copy and swap");
		if (this != &rhs) {						swap(other);
			_n = rhs.numerator();					return *this; }
			_d = rhs.denominator();
		}
		return *this; }
 *
 * 3. now, d = b; will call copy-and-swap function
 * 4. delete move assignment operator, now eigher move or copy will be used with one implementation:
 * --->		b = std::move(a); 		will use move ctor
 * --->		b = a;				will use copy ctor
 */


#include "stdafx.h"
#include <iostream>

#include <cstdio>
#include <string>
#include <memory>


void message(const char * s) {
	puts(s);
	fflush(stdout);
}

// this version has messages to show which constructor (ctor) is being called.
class Rational {
	int _n = 0;
	int _d = 1;

	static const int _bufsize = 128;
	mutable char * _buf = nullptr;

public:
	Rational() { reset(); message("default ctor"); }
	Rational(const int & numerator) : _n(numerator), _d(1) { message("int ctor"); }
	Rational(const int & numerator, const int & denominator) : _n(numerator), _d(denominator) { message("int,int ctor"); }
	Rational(const Rational & other) : _n(other._n), _d(other._d) { message("copy ctor"); }
	Rational(Rational &&) noexcept;
	~Rational();

	void reset();
	inline int numerator() const { return _n; }
	inline int denominator() const { return _d; }
	Rational & operator = (const Rational &);
	Rational & operator = (Rational &&) noexcept;
	Rational operator + (const Rational &) const;
	Rational operator - (const Rational &) const;
	Rational operator * (const Rational &) const;
	Rational operator / (const Rational &) const;
	operator std::string() const;
	std::string string() const;
	const char * c_str() const;
};

Rational::Rational(Rational && other) noexcept {
	_n = std::move(other._n);
	_d = std::move(other._d);
	other.reset();
	message("move ctor");
}

Rational::~Rational() {
	message("dtor");
	reset();
}

void Rational::reset() {
	_n = 0; _d = 1;
	delete[] _buf;
	_buf = nullptr;
}

Rational & Rational::operator = (const Rational & rhs) {
	message("assignment");
	if (this != &rhs) {
		_n = rhs.numerator();
		_d = rhs.denominator();
	}
	return *this;
}

Rational & Rational::operator = (Rational && rhs) noexcept {
	message("move assignment");
	if (this != &rhs) {
		_n = std::move(rhs.numerator());
		_d = std::move(rhs.denominator());
		rhs.reset();
	}
	return *this;
}

Rational Rational::operator + (const Rational & rhs) const {
	return Rational((_n * rhs._d) + (_d * rhs._n), _d * rhs._d);
}

Rational Rational::operator - (const Rational & rhs) const {
	return Rational((_n * rhs._d) - (_d * rhs._n), _d * rhs._d);
}

Rational Rational::operator * (const Rational & rhs) const {
	return Rational(_n * rhs._n, _d * rhs._d);
}

Rational Rational::operator / (const Rational & rhs) const {
	return Rational(_n * rhs._d, _d * rhs._n);
}

Rational::operator std::string() const {
	return string();
}

std::string Rational::string() const {
	return std::string(c_str());
}

const char * Rational::c_str() const {
	if (!_buf) _buf = new char[_bufsize]();
	snprintf(_buf, _bufsize, "%d/%d", _n, _d);
	return _buf;
}

// calls move ctor on tmp object: Rational d = f(c);
// because return obj is temporary obj with no name
Rational f(Rational o) {
	return o;
}

int main(int argc, char ** argv) {

	Rational a = 7;     // 7/1
	Rational b(5, 3);   // 5/3
	Rational c = b;     // copy ctor
	//Rational d;       // default ctor
	Rational d = std::move(c);

	// d = b; 			// assingment
	d = std::move(b);   // move assignment

	printf("a is: %s\n", a.c_str());
	printf("b is: %s\n", b.c_str());
	printf("c is: %s\n", c.c_str());
	printf("d is: %s\n", d.c_str());

	printf("%s + %s is %s\n", a.c_str(), b.c_str(), Rational(a + b).c_str());

	std::cin.get();
}
