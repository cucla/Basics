int main() 
{
	std::stack<int, std::vector<int>> myStack;
	myStack.push(10);
	myStack.push(20);
	myStack.push(30);

	int * end = &myStack.top() + 1;         // address of the last element
	int * begin = end - myStack.size();
	std::vector<int> stack_contents(begin, end);


	std::cin.get();
}

