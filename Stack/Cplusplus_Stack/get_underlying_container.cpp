/* The underlying container of std::stack is accessible as protected member c. Hence:
 */
template<class T, class C>
struct cStack : std::stack<T, C> {
	typedef std::stack<T, C> Stack;
	using Stack::stack;
	using Stack::c;                   // expose as public
};

int main() 
{
	cStack<int, std::deque<int>> a;
	std::deque<int> d;
	std::cout << (typeid(a.c) == typeid(d)) << '\n';  // 1
}
