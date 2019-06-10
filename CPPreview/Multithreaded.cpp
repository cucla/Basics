
// 1. Intro
// 2. Waiting for a thread to complete (.join())

// 1. Intro -----------------------------------------------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <thread>

void do_smth() 		{ std::cout << "Action No1" << std::endl; }
void do_smth_else() 	{ std::cout << "Action No2" << std::endl; }

struct background_task {
	void operator() () const{
		do_smth();
		do_smth_else(); } };

int main() {
	std::thread thread_two(do_smth);           // std::thread works with any callable type
	thread_two.join();

	background_task t;
	std::thread thread_three(t);
	thread_three.join();

	std::thread thread_four{ background_task() };
	thread_four.join();

	std::thread thread_five([]() {
		do_smth();
		do_smth_else(); } );
	thread_five.join();

	std::cin.get(); }


// 2. Waiting for a thread to complete (.join()) ----------------------------------------------
void do_smth(int i) { std::cout << "Action No" << i << std::endl; }

struct background_task {
	background_task(int & i) : _i(i) {}
	background_task(int &&) = delete;  // prevents rvalue binding

	void operator()() const { 
		for (unsigned j = 0; j < 1000000; ++j) do_smth(_i);
	}

	int & _i;   // will reference local object 'some_local_state'
};

void oops() {
	int some_local_state = 0;
	background_task bt(some_local_state);
	std::thread my_thread(bt);
	my_thread.detach();		// if oops() exits, my_thread may still be running
}					// holding reference to local variable, which is destroyed

void good1() {
	int some_local_state = 0;
	background_task bt(some_local_state);
	std::thread t(bt);
	try {   
		//do_something_in_current_thread();   
	}
	catch (...) {
		t.join();			// to ensure the thread complete before good() exits
		throw;
	}
	t.join();
}

// use RAII idiom and provide a class that does the join() in its destructor
class thread_guard {
public:
	explicit thread_guard(std::thread & t) : _t(t) {}
	~thread_guard() { if (_t.joinable()) _t.join(); }

	thread_guard(thread_guard const &) = delete;
	thread_guard & operator=(thread_guard const &) = delete;
private:
	std::thread & _t;
};

void good2() {
	int some_local_state = 0;
	background_task bt(some_local_state);
	std::thread my_thread(bt);
	thread_guard g(my_thread);	// when func exits, thread_guard is destroyed first, thread is joined
	//do_something_in_current_thread();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
