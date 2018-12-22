#include "stdafx.h"
#include <iostream>
#include <utility> 
#include <math.h> 
#include <vector>
#include <string>


/* OOP
 * the Big-Five: destructor, copy constructor, move constructor,
 * copy assignment operator=, move assignment operator=
 *
 * If writing any of Big-Five, explicitly concider all others ('= default'):
 *
 * Rational(const Rational & other) : _n(other._n), _d(other._d) { }
 * Rational(Rational &&) noexcept = default;
 * Rational & operator= (const Rational &) = default;
 * Rational & operator= (Rational &&) noexcept = default;
 * ~Rational()= default;
 *
 * Alternatively, dissalow all copying and moving ('= delete'):
 *
 * Rational(const Rational & other) = delete;
 * Rational(Rational &&) noexcept = delete;
 * Rational & operator= (const Rational &) = delete;
 * Rational & operator= (Rational &&) noexcept = delete;
 */

class Rational {
public:
	Rational() { reset(); }
	Rational(const int & numerator) : _n(numerator), _d(1) { }
	Rational(const int & numerator, const int & denominator) : _n(numerator), _d(denominator) { }
	Rational(const Rational & other) : _n(other._n), _d(other._d) { }
	Rational(Rational &&) noexcept;
	Rational & operator= (const Rational &);
	Rational & operator= (Rational &&) noexcept;
	~Rational();

	void reset();
	inline int numerator() const { return _n; }
	inline int denominator() const { return _d; }
	const char * c_str() const;
private:
	int _n = 0;
	int _d = 1;
	static const int _bufsize = 128;
	mutable char * _buf = nullptr;
};

void Rational::reset() {
	_n = 0; _d = 1;
	delete[] _buf;
	_buf = nullptr;
}

Rational::Rational(Rational && other) noexcept {
	_n = std::move(other._n);
	_d = std::move(other._d);
	other.reset();
}

Rational & Rational::operator = (const Rational & rhs) {
	if (this != &rhs) {
		_n = rhs.numerator();
		_d = rhs.denominator();
	}
	return *this;
}

Rational & Rational::operator = (Rational && rhs) noexcept {
	if (this != &rhs) {
		_n = std::move(rhs.numerator());
		_d = std::move(rhs.denominator());
		rhs.reset();
	}
	return *this;
}

Rational::~Rational() {
	reset();
}

const char * Rational::c_str() const {
	if (!_buf) _buf = new char[_bufsize]();
	snprintf(_buf, _bufsize, "%d/%d", _n, _d);
	return _buf;
}

int main()
{
	Rational a = 7;			// 7/1
	Rational b{ 5, 3 };		// 5/3
	Rational c = b;			// copy ctor, because b is lvalue; move ctor in rvalue
	Rational d{ b };		// copy ctor, because b is lvalue; move ctor in rvalue

	std::cout << a.c_str() << std::endl;
	std::cout << b.c_str() << std::endl;
	std::cout << c.c_str() << std::endl;
	std::cout << d.c_str() << std::endl;

	//c = a; 				// copy assingment
	c = std::move(a);		// move assignment
	std::cout << c.c_str() << std::endl;	// 7/1
	std::cout << a.c_str() << std::endl;	// 0/1

	std::cin.get();
}

