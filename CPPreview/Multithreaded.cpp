
// 1. Intro
// 2. Waiting for a thread to complete (.join()), class thread_guard
// 3. Passing arguments
// 4. Transferring ownership of a thread
// 5. Spawn number of threads


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
	std::thread thread_two(do_smth);        // std::thread works with any callable type
	thread_two.join();			// or thread_two.detach();

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


// 3. Passing arguments -----------------------------------------------------------------------
void f(int i, std::string const & s);

std::thread t(f, 3, ”hello”);   	// arguments are copied into internal storage, even if passed by ref
t.detach();

void not_oops(int some_param) {
	char buffer[1024];				// when passing pointer to local var to thread
	std::thread t(f, 3, std::string(buffer));  	// cast to string
	t.detach(); 
}

void not_oops(int some_param) {
	string data;
	std::thread t(f, 3, std::ref(data));   		// if the thread needs to update data passed by ref
	t.join();
}

struct X {
	void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work, &my_x);		// pass a member function pointer with suitable object pointer
t.join();

void process_big_object(std::unique_ptr<big_object>);
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object, std::move(p));	// when args can't be copied


// 4. Transferring ownership of a thread ------------------------------------------------------
void some_function();
void some_other_function();
std::thread t1(some_function);
std::thread t2 = std::move(t1);  		// t1 no longer has an associated thread
t1 = std::thread(some_other_function);
std::thread t3;
t3 = std::move(t2);
t1 = std::move(t3);	// std::terminate() is called to terminate some_other_function() first

// a function that creates a thread to run in the background
// but passes back ownership of the new thread to the calling function rather than waiting
// for it to complete
std::thread foo() {
	void some_other_function(int);
	std::thread t(some_other_function, 42);
	return t;				// Returning a std::thread from a function
}

// create a thread and pass
// ownership in to some function that should wait for it to complete
void f(std::thread t);
void g() {
void some_function();
f(std::thread(some_function));
std::thread t(some_function);
f(std::move(t));
}

// compared to 'thread_guard', the new thread is passed in directly
// to the scoped_thread rather than having to create a separate named variable for it
class scoped_thread {
public:
	explicit scoped_thread(std::thread t): _t(std::move(t)) {     // uses std::move!
		if(!t.joinable()) throw std::logic_error(“No thread”); }
	~scoped_thread() { t.join(); }
	scoped_thread(scoped_thread const &) = delete;
	scoped_thread & operator=(scoped_thread const &) = delete;
private:
	std::thread _t;
};

struct background_task {
	background_task(int & i) : _i(i) {}
	background_task(int &&) = delete;  // prevents rvalue binding

	void operator()() const { 
		for (unsigned j = 0; j < 1000000; ++j) do_smth(_i);
	}
	int & _i;   // will reference local object 'some_local_state'
};

void f() {
int some_local_state;
scoped_thread t(std::thread(background_task(some_local_state)));
// do_something_in_current_thread();      // scoped_thread obj is destroyed when function exits
}

// 5. Spawn number of threads -----------------------------------------------------------------
void do_work(unsigned id);
void f() {
	std::vector<std::thread> threads;
	for(unsigned i = 0; i < 20; ++i) 
		threads.push_back(std::thread(do_work, i));
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
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
