/* The underlying container of std::stack is accessible as protected member c. Hence:
 */
template<typename T, typename Container = deque<T>>
struct myStack : std::stack<T> {
	typedef std::stack<T> Stack;
	using Stack::stack;
	using Stack::c;
};

int main() 
{
	myStack<int, std::deque<int>> s;
	s.push(1);
	s.push(2);

	std::deque<int> d;
	std::cout << (typeid(s.c) == typeid(d)) << '\n';  		// 1

	std::deque<int>::iterator it = s.c.begin();			// can print stack contents
	while (it != s.c.end())
		std::cout << ' ' << *it++;


	std::cin.get();
}
