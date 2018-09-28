int Max(int x, int y) { return x > y ? x : y; }

/* PUT TEMPLATE DEFINITION-DECLARATION IN HEADER FILE
 * allows to make 'int Max(int x, int y)' for other types
 * template argument deduction > template is instantiation
 */
template<typename T>
T Max(T x, T y) {
	std::cout << typeid(T).name() << std::endl;
	return x > y ? x : y;
}

// 3. explicitly instantiate (ex. for char)
template char Max(char x, char y);

int main() 
{
	// 1. instantiate when calling
	auto num1 = Max(3, 8);
	auto num2 = Max(3.1f, 8.1f);
	auto char1 = Max('d', 'z');

	// override argument deduction by specifying types in template argument list
	auto num3 = Max<int>(32, 8.1f);

	// 2. instantiate when taking function pointer
	int(*fptr)(int, int) = Max;
}


