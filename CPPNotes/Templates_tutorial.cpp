
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

// non-type template arguments with array 
// not yet -> need to pass array size
template<typename T>
T Sum1(T * parr, int size) {
	T sum{};
	for (int i = 0; i < size; i++)
		sum += parr[i];
	return sum;
}
// yes -> no need to pass array size | pass ref to array
template<typename T, int size>
T Sum2(T (&parr)[size]) {
	T sum{};
	for (int i = 0; i < size; i++)
		sum += parr[i];
	return sum;
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
	
	// non-type template arguments
	int arr[]{ 3, 1, 9, 7 };	// int(&aref)[4] = arr; is a reference to array
	int sum1 = Sum1(arr, 4);
	int sum2 = Sum2(arr);
}



// Variardic templates - pass different types & different number of parameters
// base case
void Print() { std::cout << std::endl; }

template<typename T, typename...Params>
void Print(T a, Params... args) {
	std::cout << sizeof...(args); // (1, 2.5, "4", 44) > 1 is a | 2.5, "4", 44 are args (total 3)
	std::cout << a;
	Print(args...);  // stops when reaches Print(); see base case 
}

int main() 
{
	Print(1, 2.5, "4", 44);
}



// CLASS TEMPLATES
// simple Stack class
class Stack {
	int _buffer[512];
	int _top{ -1 };
public:
	void Push(int el) { _buffer[++_top] = el; }
	void Pop() { --_top; }
	int Top() const { return _buffer[_top]; }
	bool IsEmpty() { return _top == -1; }
};

// class template
template<typename T, int size>
class Stack {
	T _buffer[size];
	int _top{ -1 };
public:
	void Push(const T & el) { _buffer[++_top] = el; }
	void Pop();   			// define method outside the class
	const T & Top() const { return _buffer[_top]; }
	bool IsEmpty() { return _top == -1; }
	
	// factory function
	static Stack Create();  // 'Stack' as a short-hand definition
};

template<typename T, int size>		// define method outside the class
void Stack<T, size>::Pop() { --_top; }

// factory function defined outside
template<typename T, int size>
Stack<T, size> Stack<T, size>::Create() {  // 'Stack<T, size>' full definition
	return Stack<T, size>();
}

int main() 
{
	Stack<int, 10> s;
	Stack<int, 10> s = Stack<int, 10>::Create();  // using factory function
}



// EXPLICIT SPECIALIZATION WITH CLASS TEMPLATES
template<typename T, int col>
class PrettyPrinter {
	T * _data;
public:
	PrettyPrinter(T * input) : _data(input) {}
	void Print() { 
		std::cout << col << std::endl;
		std::cout << "|" << *_data << "|" << std::endl; }
	T * GetData() { return _data; }
};

// PARTIAL SPECIALIZATION for non-type parameter int col
// EXPLICIT SPECIALIZATION : whole class for char *
template<>
class PrettyPrinter<char *, 30> {
	char * _data;
public:
	PrettyPrinter(char * input) : _data(input) {}
	void Print() { 
		std::cout << 30 << std::endl;
		std::cout << "|" << _data << "|" << std::endl; }
	char * GetData() { return _data; }
};

// EXPLICIT SPECIALIZATION : only member function for vector
template<>
void PrettyPrinter<std::vector<int>, 40>::Print() { 
	std::cout << 40 << std::endl;
	for(const auto &x : * _data)
		std::cout << "|" << x << "|" << " "; 
	}

int main() 
{
	int a = 4;
	float b = 4.1f;
	PrettyPrinter<int, 10> p1(&a);
	PrettyPrinter<float, 20> p2(&b);
	p1.Print();
	p2.Print();

	char * c{ "Hello world" };
	PrettyPrinter<char *, 30> p3(c);
	p3.Print();

	std::vector<int> d{ 1, 2, 3, 4, 5 };
	PrettyPrinter<std::vector<int>, 40> p4(&d);
	p4.Print();
}




/* Understand template type deduction
 *
 * ================================================
 * template<typename T>
 * void f(ParamType param);		// (ex.   void f(const T& param);   )
 * ------------------------------------------------
 * f(expr);                    		// call f with some expression
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
 * template<typename T>
 * void f(T* param);      
 * ------------------------------------------------
 * f(&x);                  // int x = 27;		T is int, param's type is int*
 * f(px);                  // const int *px = &x;	T is const int, param's type is const int*
 * ================================================
 *
 * Case 2: ParamType is a Universal Reference (T&&)
 *
 * Array Arguments:
 * ================================================
 *				// const char name[] = "J. P. Briggs";
 * template<typename T>
 * void f(T param);      	// template with by-value parameter | void f(int param[]); | void f(int * param);
 * ------------------------------------------------
 * f(name);			// name is array, but T deduced as const char *
 * ================================================
 *** Functions can declare parameters that are references to arrays!
 * template<typename T>
 * void f(T& param);      	// template with by-reference parameter
 * ------------------------------------------------
 * f(name);			// the type deduced for T is the actual type of the array! 
 *				// it includes the size of the array, here, T is deduced to be const char [13]
 *
