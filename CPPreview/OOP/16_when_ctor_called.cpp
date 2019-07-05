using namespace std;


class Foo {
public:
	Foo() { printf("constructor \n"); };
	Foo(const Foo& other) { printf("copy constructor \n"); };
	Foo(Foo&&) noexcept { printf("move constructor \n"); };

	Foo& operator=(const Foo& other) {
		printf("copy assignment operator \n");
		return *this;
	};
	Foo& operator=(Foo&&) {
		printf("move assignment operator \n");
		return *this;
	};
};

class Bar {
public:
	explicit Bar(Foo f) { printf("Bar constructor \n"); }
};


int main() 
{
	Foo var;			// ctor
	Foo arr[2];			// ctor x2
	vector<Foo> vect(2);		// ctor x2

	Bar b(var);			// 1. copy ctor, to generate instance of Foo class
					// 2. Bar ctor

	Foo jar(var);			// copy ctor
	Foo car = var;			// copy ctor
	car = arr[1];			// copy assignment operator
	Foo star = std::move(jar);	// move ctor
	Foo costar(std::move(star));	// move ctor

	Foo* varptr;			// nothing
	varptr = new Foo;		// ctor
	Foo* darr = new Foo[2];		// ctor x2	

	Foo a;				// ctor
	Foo* aptr = &a;			// nothing
					// no need to call 'delete' on a pointer that wasn't initialized with 'new'

	// "unique_ptr to an array", NOT array of std::unique_ptr
	std::unique_ptr<Foo[]> my_array1(new Foo[2]);			// ctor x2, calls 'delete[]'
	// std::shared_ptr<Foo[]> my_array2(new Foo[2]);		// calls 'delete', in C++17 calls 'delete[]'
	// must supply a custom deleter:
	std::shared_ptr<Foo> my_array3(new Foo[2], [](Foo* p) { delete[] p; });
	std::shared_ptr<Foo> my_array4(new Foo[2], std::default_delete<Foo[]>());
	// my_array4.get()[0]  , to get element

	unique_ptr<Foo> my_array2[3];
	for (auto& p : my_array2)	// ctor x3	
		p = make_unique<Foo>();
	
	Foo* varptr2;			// nothing
	varptr2 = varptr;		// nothing
	varptr2 = new Foo;			// ctor
	varptr2 = new Foo(darr[0]);		// copy ctor

	
	delete varptr;
	delete[] darr;
	delete varptr2;

	std::cin.get();
}
