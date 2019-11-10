#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template<typename T>
std::string to_string_impl(const T & t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template<typename... T>
std::vector<std::string> to_string(const T &... param) {
	return { to_string_impl(param)... };
}

int main()
{
	const auto vect = to_string("hello", 1, 5.3);
	for (const auto & o : vect)
		std::cout << o << std::endl;

	std::cin.get();
}

hello
1
5.3
-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>


struct Boxed_value {
	friend struct Engine;

	void inbox(int v) { _iv = v; }
	void inbox(double v) { _dv = v; }
	void inbox(std::string & v) { _sv = v; }
private:
	int	_iv;
	double _dv;
	std::string _sv;
};

struct Engine {
	template<typename T>
	T unbox(Boxed_value & bv);

	template<>
	decltype(Boxed_value::_iv) unbox<decltype(Boxed_value::_iv)>(Boxed_value & bv) {
		return bv._iv;
	}
	template<>
	decltype(Boxed_value::_dv) unbox<decltype(Boxed_value::_dv)>(Boxed_value & bv) {
		return bv._dv;
	}
	template<>
	decltype(Boxed_value::_sv) unbox<decltype(Boxed_value::_sv)>(Boxed_value & bv) {
		return bv._sv;
	}
};

struct Base {
	virtual void handle(Boxed_value & bv, Engine & eng) = 0;
	virtual ~Base() = default;

protected:
	template <typename T>
	static void throw_type(Boxed_value & bv, Engine & eng) {
		std::cout << eng.unbox<T>(bv) << std::endl;
	}
};

template<typename... T>
struct Impl : Base {
	void handle(Boxed_value & bv, Engine & eng) override {
		(void)std::initializer_list<int>{ (throw_type<T>(bv, eng), 0)...};
	}
};

// Implementations, that were substituted for variardic template
//template<typename T1>
//struct Impl1 final : Base {
//	void handle(Boxed_value & bv, Engine & eng) override {
//		throw_type<T1>(bv, eng);
//	}
//};
//template<typename T1, typename T2>
//struct Impl2 final : Base {
//	void handle(Boxed_value & bv, Engine & eng) override {
//		throw_type<T1>(bv, eng);
//		throw_type<T2>(bv, eng);
//	}
//};
//template<typename T1, typename T2, typename T3>
//struct Impl3 final : Base {
//	void handle(Boxed_value & bv, Engine & eng) override {
//		throw_type<T1>(bv, eng);
//		throw_type<T2>(bv, eng);
//		throw_type<T3>(bv, eng);
//	}
//};


// Simple explanation of the above stuff:

template<typename A>
void func_a(A a) { std::cout << a << std::endl; }

template<typename... B> 
void func_b(B... b) { 
	std::cout << "Total size: " << sizeof...(b) << std::endl; 
}

/* Magic is to put a plain template function into initializer_list
 * to make it perform the action for each passed type one-by-one
 * func_b -> works fine, as it is variardic template function
 * func_a -> works with 1 argumet ( ex. func_c(10)) or in initializer_list
 */
template<typename... C>
void func_c(C... c) 
{
	func_b(c...);
	//func_a(c...);

	(void)std::initializer_list<int>{ (func_a<C>(c), 0)...};
}


int main()
{
	func_c();
	func_c(10);
	func_c('d');
	func_c(10, 2.33);
	func_c('f', 3.3);
	func_c('d', 4, "hot");

	std::cout << "*************************" << std::endl;

	int a = 77;
	double b = 88.88;
	std::string c = "some 99 strings";

	Boxed_value my_bval;
	Engine my_engine;

	my_bval.inbox(a);
	my_bval.inbox(b);
	my_bval.inbox(c);

	Impl<int, double, std::string> impl1;
	impl1.handle(my_bval, my_engine);

	// Implementations, that were substituted for variardic template
	//Impl1<int> im1_1; 
	//im1_1.handle(my_bv, my_eng);
	//Impl1<std::string> im1_2;
	//im1_2.handle(my_bv, my_eng);
	//Impl2<std::string, double> im2_1;
	//im2_1.handle(my_bv, my_eng);
	//Impl3<std::string, double, int> im3_1;
	//im3_1.handle(my_bv, my_eng);


	std::cin.get();
}

OUTPUT
Total size: 0
Total size: 1
10
Total size: 1
d
Total size: 2
10
2.33
Total size: 2
f
3.3
Total size: 3
d
4
hot
*************************
77
88.88
some 99 strings
