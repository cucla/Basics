// Struct Interface + list of objects + std::for_each()

struct Interface {
	virtual void run() = 0;
};

struct A : public Interface {
	void run() { std::cout << "I run class A" << std::endl; }
};

struct B : public Interface {
	void run() { std::cout << "I run class B" << std::endl; }
};

int main() 
{ 
	A a;
	B b;

	std::list<Interface *> lst;
	lst.push_back(&a);
	lst.push_back(&b);

	std::for_each(lst.begin(), lst.end(), [](Interface * obj) { obj->run(); });
}
