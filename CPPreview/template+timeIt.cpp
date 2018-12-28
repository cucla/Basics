#include <chrono>

template<typename Function, typename input>
void timeIt(Function foo, input v) {
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		foo(v);
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << elapsed.count() << std::endl;
}
