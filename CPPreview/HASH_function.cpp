/* To be able to use std::unordered_map with a user-defined key-type, you need to define 2 things:
 *
 * A hash function -> specialize the std::hash template for your key-type
 * A comparison function for equality -> to deal with collisions; implement this either 
   as a class that overrides operator(), or as a specialization of std::equal, or by overloading 
   operator==() for your key type
 *
 * A better hash function?
 * For a real good one you need to take into account the distribution of possible values of all fields and 
 * define a hash function that projects that distribution to a space of possible results as wide and evenly 
 * distributed as possible
 * - the XOR/bit-shifting method
*/


// 1: class with operator==(), specialized std::hash<Node> template in common namespace
//		std::unordered_map<Node, int> m
// 2: class with operator==(), custom HashFunction template
//		std::unordered_map<Node, int, HashFunction<Node>> m
// 3: using lambda expressions
//		std::unordered_map<Node, int, decltype(hash), decltype(equal)> m(8, hash, equal)


// 1: class with operator==(), specialized std::hash<Node> template in common namespace
class Node {
public:
	Node() {}
	Node(int A, std::string B) : a{ A }, b{ B } {}

	bool operator==(const Node& i) const {
		if (i.a == this->a && i.b == this->b) return true;
		else return false;
	}

	void print(std::ostream & os = std::cout) const {
		os << "NODE: " << a << b << "\n";
	}

//private:
	int a;
	std::string b;
};

// Template Specialization: a special behavior for a Node type in a template class std::hash
template <>
struct std::hash<Node> {
	std::size_t operator()(const Node& k) const {
		using std::size_t;
		using std::hash;
		using std::string;

    // WAY 1:
		return ((hash<int>()(k.a) ^ (hash<string>()(k.b) << 1)) >> 1);

		// WAY 2: Compute individual hash values
		//size_t res = 17;
		//res = res * 31 + hash<int>()(k.a);
		//res = res * 31 + hash<string>()(k.b);
		//return res;
	}
};

int main() {
	std::unordered_map<Node, int> m = {
		{ { 10, "-ten" }, 1 },
		{ { 100, "-hundred" }, 2 },
		{ { 1000, "-thousand" }, 3 }
	};

	for (auto el : m) {
		std::cout << el.second << std::endl;
		el.first.print(); 
	}
}

/*
1
NODE: 10-ten
2
NODE: 100-hunrded
3
NODE: 1000-thousand
*/


// 2: class with operator==(), custom HashFunction template
class Node {
public:
	Node() {}
	Node(int A, std::string B) : a{ A }, b{ B } {}

	bool operator==(const Node& i) const {
		if (i.a == this->a && i.b == this->b) return true;
		else return false;
	}

	void print(std::ostream & os = std::cout) const {
		os << "NODE: " << a << b << "\n";
	}

//private:
	int a;
	std::string b;
};

template<class Key>
class HashFunction; // leave entirely unimplemented

template<>
class HashFunction<Node> {
public:
	size_t operator()(const Node& n) const {
		size_t res = 17;
		res = res * 31 + int_hash(n.a);
		res = res * 31 + str_hash(n.b);
		return res;
	}
private:
	std::hash<int> int_hash;             // To avoid constructing the std::hash all the time
	std::hash<std::string> str_hash;

};

int main() {
	std::unordered_map<Node, int, HashFunction<Node>> m = {
		{ { 10, "-ten" }, 1 },
		{ { 100, "-hundred" }, 2 },
		{ { 1000, "-thousand" }, 3 }
	};

	for (auto el : m) {
		std::cout << el.second << std::endl;
		el.first.print(); 
	}
}

/*
1
NODE: 10-ten
2
NODE: 100-hunrded
3
NODE: 1000-thousand
*/


// 3: using lambda expressions
class Node {
public:
	Node() {}
	Node(int A, std::string B) : a{ A }, b{ B } {}

	void print(std::ostream & os = std::cout) const {
		os << "NODE: " << a << b << "\n";
	}

//private:
	int a;
	std::string b;
};


int main() {
	auto hash = [](const Node& n) {
		size_t res = 17;
		res = res * 31 + std::hash<int>()(n.a);
		res = res * 31 + std::hash<std::string>()(n.b);
		return res;
	};

	auto equal = [](const Node& n1, const Node& n2) {
		return n1.a == n2.a && n1.b == n2.b;
	};

	std::unordered_map<Node, int, decltype(hash), decltype(equal)> m(8, hash, equal);

	Node n1{ 10, "-ten" };
	Node n2{ 100, "-hunrded" };
	Node n3{ 1000, "-thousand" };

	m[n1] = 1; 
	m[n2] = 2;
	m[n3] = 3;

	for (auto el : m) {
		std::cout << el.second << std::endl;
		el.first.print(); 
	}
}

/*
1
NODE: 10-ten
2
NODE: 100-hunrded
3
NODE: 1000-thousand
*/




