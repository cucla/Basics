class A {
public:
	A( const int & a ) : a(a) {}
	const int & value() const { return a; }
private:
	int a;
};

int operator +(const A & lhs, const A & rhs) {  	// make possible addition of two A objects
	return lhs.value() + rhs.value();
}

int main() 
{
	A one(7);
	A two(10);
	std::cout <<"one + two: " << one + two << std::endl;

	std::cin.get();
}
