
class Node : public std::enable_shared_from_this<Node> {
public:
	Node() {}
	Node(int A, std::string B) : a{ A }, b{ B } {}
	~Node() { std::cout << "deleting node..." << std::endl; }

	void set_data(int A, std::string&& B) { 
		a = A; b = B; 
	}

	bool operator==(const Node& node) {
		return a == node.a && b == node.b;
	}

	// to create instances of shared_ptr pointing to itself 
	// and share ownership with existing shared_ptr objects
	std::shared_ptr<Node> hand_itself_off() {
		return shared_from_this(); 
	}

	void print(std::ostream & os = std::cout) const {
		os << "NODE: " << a << ", " << b << "\n";
	}

private:
	int a;
	std::string b;
};


// enables the callee to use the object, but doesn't enable it to share ownership or extend the lifetime
// same as void process_node(Node* node)
void process_node(const Node& node) {
	node.print();
}

// PASS SMART POINTERS TO FUNCTIONS ---------------------------------------------

// 1. pass unique_ptr by value - if a function should take ownership
void grab_ownership(std::unique_ptr<Node> uniqPtr) {}
// grab_ownership(std::move(ptr));

// 2. pass unique_ptr by a non-const reference - if a function wants to reset it
void want_reset(std::unique_ptr<Node>& uniqPtr) {
	uniqPtr.reset(new Node(100, "hundred"));
}
// want_reset(ptr);

// 3. pass shared_ptr by value - if a function is part owner, increase ref count
void share(std::shared_ptr<Node> shaWid) {}
// 4. pass shared_ptr by reference - not guaranteed that the Node will stay alive 
// during the execution, but can reseat the resource
void can_reset(std::shared_ptr<Node>& shadWid) {}
// 5. pass shared_ptr by const reference - can't extend the lifetime of the 
// resource nor can reseat the resource
void cannot_reset(const std::shared_ptr<Node>& shaWid) {}

// RETURN SMART POINTERS FROM FUNCTIONS ----------------------------------------

std::unique_ptr<Node> node_factory(int A, std::string B) {
	return std::make_unique<Node>(A, B);
}


int main() 
{
	Node* ptr_node = new Node{ 1, "one" };
	std::shared_ptr<Node> ptr1(ptr_node);
	ptr1->print();

	std::shared_ptr<Node> ptr2(new Node{ 2, "two" });
	ptr2->print();

	std::shared_ptr<Node> ptr3 = std::make_shared<Node>( 3, "three" );
	ptr3->print();

	// std::enable_shared_from_this<Node> DEMO -----------------------------------
	std::shared_ptr<Node> ptr4 = std::make_shared<Node>();
	ptr4->set_data(4, "four");
	ptr4->print();
	std::shared_ptr<Node> ptr44 = ptr4->hand_itself_off();
	ptr44->print();
	// after both resets {4, "four"} resource is deleted
	ptr4.reset(); ptr44.reset();

	std::shared_ptr<Node> ptr5(nullptr);
	ptr5 = std::make_shared<Node>(5, "five");
	ptr5->print();

	// instances that take on shared ownership of an object ----------------------
	std::cout << "shared ownership" << std::endl;
	auto ptr6(ptr5);		ptr6->print();
	auto ptr7 = ptr6;		ptr7->print();
	// swap pointers as well as ref counts.
	ptr7.swap(ptr1);		ptr7->print();

	// pass 'shared_ptr<Node>' to function that takes 'const Node&' --------------
	process_node(*ptr1);

	// compare for equality (requires == in Node class)
	std::vector<std::shared_ptr<Node>> v1{ptr1, ptr2, ptr3};
	std::vector<std::shared_ptr<Node>> v2{ptr1, ptr2, ptr3};
	auto result1 = std::equal(v1.begin(), v1.end(), v2.begin(), 
		[](const std::shared_ptr<Node>& item1, const std::shared_ptr<Node>& item2)->bool {
		return (*item1 == *item2);
	});
	
	std::cout << "result1: " << result1 << std::endl;   // true
}

