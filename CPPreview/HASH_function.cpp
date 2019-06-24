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


int main() 
{
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
