
int Max(int x, int y) { return x > y ? x : y; }

/* PUT TEMPLATE DEFINITION-DECLARATION IN HEADER FILE
 * allows to make 'int Max(int x, int y)' for other types
 * template argument deduction > template instantiation
 */
template<typename T>
T Max(T x, T y) {
	std::cout << typeid(T).name() << std::endl;
	return x > y ? x : y;
}

// 3. explicitly instantiate (ex. for char)
template char Max(char x, char y);		// instantiate for char

// explicit specialization for more optimal algorithm implementation
// must be defined in a .cpp file, already instantiated
template<> const char * Max(const char * x, const char * y) {
	return strcmp(x, y) > 0 ? x : y;
}

int main() 
{
	// 1. instantiate when calling
	auto num1 = Max(3, 8);			// instantiate for int
	auto num2 = Max(3.1f, 8.1f);		// instantiate for float

	// override argument deduction
	auto num3 = Max<int>(32, 8.1f);

	// 2. instantiate when taking function pointer
	int(*fptr)(int, int) = Max;		// instantiate for int
	
	// explicit specialization
	const char * a{ "A" };
	const char * b{ "B" };
	auto res = Max(a, b);
}


/* Understand template type deduction
 *
 * ================================================
 * template<typename T>
 * void f(ParamType param);	// (ex.   void f(const T& param);   )
 * ------------------------------------------------
 * f(expr);                    	// call f with some expression
 * ================================================
 * Need to deduce two types: one for T and one for ParamType (includes const, references...)
 * Type of T depends on expr and ParamType, and we have 3 cases:
 *
 * Case 1: ParamType is a Reference or Pointer, but not a Universal Reference
 * ================================================
 * template<typename T>
 * void f(T& param);      
 * ------------------------------------------------
 * f(x);                   // int x = 27;		T is int, param's type is int&
 * f(cx);                  // const int cx = 27;	T is const int, param's type is const int&
 * f(rx);                  // const int& rx = 27;	T is const int, param's type is const int&, T is deduced to be a non-reference
 * ================================================
 * template<typename T>
 * void f(const T& param);      
 * ------------------------------------------------
 * f(x);                   // int x = 27;		T is int, param's type is const int&
 * f(cx);                  // const int cx = 27;	T is int, param's type is const int&
 * f(rx);                  // const int& rx = 27;	T is int, param's type is const int&
 * ================================================
