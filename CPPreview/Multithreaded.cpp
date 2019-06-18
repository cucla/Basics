// PPT : https://home.deib.polimi.it/fornacia/lib/exe/fetch.php?media=teaching:aos:2017:aos_l4_multithreading_cpp.pdf
// good tutorial: https://baptiste-wicht.com/posts/2012/03/cp11-concurrency-tutorial-part-2-protect-shared-data.html

// 1. Intro
// 2. Waiting for a thread to complete (.join()), class thread_guard
// 3. .detach() threads, reusing the same function
// 4. Passing arguments
// 5. Transferring ownership of a thread
// 6. Spawn number of threads
// 7. Tasks, [see 3 to compare examples]
// 8. Shared Memory and Shared Resources
// 9. Thread-safe stack
// 10. Avoid deadlock where you need to acquire two or more locks together

// 11. Producer-consumer scenario
// 12. Compute a single function in parallel for > 1 different initial values

// -------------------------------------------------------------------------------------------
#include <thread>
    unsigned int c = std::thread::hardware_concurrency();
    std::cout << " number of cores: " << c << endl;


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

	background_task t;			// function object is copied into the storage belonging to the new thread
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
}					// holding reference to local variable, which is destroyed, undefined behavior

void good1() {
	int some_local_state = 0;
	background_task bt(some_local_state);
	std::thread t(bt);
	try {   
		//do_something_in_current_thread();   
	}
	catch (...) {
		t.join();			// to ensure the thread complete before good1() exits
		throw;
	}
	t.join();
}

// RAII - Resource Acquisition Is Initialization
// provide a class that does the join() in its destructor
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
	thread_guard g(my_thread);	// when func exits, local objects are destroyed in reverse order of construction
					// thread_guard is destroyed first, thread is joined
	
	do_something_in_current_thread();
}


// 3. .detach() threads, reusing the same function -------------------------------------------
/* Because the new thread is doing the same operation as the current thread but on a different
file, you can reuse the same function (edit_document) with the newly chosen filename
as the supplied argument. */

void edit_document(std::string const & filename) {
	open_document_and_display_gui(filename);
	while(!done_editing()) {
		user_command cmd = get_user_input();
		if(cmd.type == open_new_document) {
			std::string const new_name = get_filename_from_user();
			std::thread t(edit_document, new_name);
			t.detach();
		}
		else {
			process_user_input(cmd);
		}
	}
}


// 4. Passing arguments -----------------------------------------------------------------------
/* by default the arguments are copied into internal storage, where they can be accessed by the newly 
created thread, even if the corresponding parameter in the function is expecting a reference */

void f1(int i, std::string const & s);

std::thread t(f1, 3, ”hello”); 
t.detach();

void not_oops(int some_param) {
	char buffer[1024];				// when passing pointer to local var to thread
	std::thread t(f1, 3, std::string(buffer));  	// cast to string
	t.detach(); 
}

// Using a function pointer
void f2(const std::vector<int> & v, long long & acm, int b, int e) {
    acm = 0;
    for (int i = b; i < e; ++i)  acm += v[i];
}

long long acm1 = 0, acm2 = 0;
std::thread t1(f2, std::ref(v), std::ref(acm1), 0, v.size() / 2);        // std::ref to pass by reference
std::thread t2(f2, std::ref(v), std::ref(acm2), v.size() / 2, v.size());
t1.join();
t2.join();
std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;

// Using Functors
struct CAccumulatorFunctor3 {
    void operator()(const std::vector<int> & v, int b, int e) {
        _acm = 0;
        for (unsigned int i = beginIndex; i < endIndex; ++i)  _acm += v[i];
    }
    long long _acm;
};

CAccumulatorFunctor3 accumulator1 = CAccumulatorFunctor3();     // can store its return value in a member variable
CAccumulatorFunctor3 accumulator2 = CAccumulatorFunctor3();
std::thread t1(std::ref(accumulator1), std::ref(v), 0, v.size() / 2);
std::thread t2(std::ref(accumulator2), std::ref(v), v.size() / 2, v.size());
t1.join();
t2.join();
std::cout << accumulator1._acm + accumulator2._acm << endl;

// Using Lambda Functions
long long acm1 = 0, acm2 = 0;
std::thread t1([&acm1, &v] {
    for (unsigned int i = 0; i < v.size() / 2; ++i)  acm1 += v[i];
});
std::thread t2([&acm2, &v] {
    for (unsigned int i = v.size() / 2; i < v.size(); ++i)  acm2 += v[i];
});
t1.join();
t2.join();
std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;

// pass a member function pointer with suitable object pointer
struct X {
	void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work, &my_x);		// will invoke my_x.do_lengthy_work() on the new thread
t.join();

// pass function that takes pointer to void
void func(void* data) {
  MyClass* c = static_cast<MyClass*>(data);        	// Conversion from MyClass* -> void* is implicit
  ...
}

int main() {
  MyClass c;
  start_thread(&func, &c)  				// func(&c) will be called
      .join();
}

// use std::move to transfer ownership of a dynamic object into a thread
void process_big_object(std::unique_ptr<big_object>);
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object, std::move(p));	// the ownership of the big_object is transferred first into 
							// internal storage for the newly created thread and
							// then into process_big_object


// 5. Transferring ownership of a thread ------------------------------------------------------
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

// 6. Spawn number of threads -----------------------------------------------------------------
void do_work(unsigned id) {
	std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

void f() {
	std::vector<std::thread> threads;
	for(unsigned i = 0; i < 20; ++i) 
		threads.push_back(std::thread(do_work, i));
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

// 7. Tasks -----------------------------------------------------------------------------------
// tasks are defined and created using std::async
// returned value is a std::future, get its values by calling __.get()

auto f1 = [](std::vector<int> & v, unsigned int left, unsigned int right) {
    long long acm = 0;
    for (unsigned int i = left; i < right; ++i)  acm += v[i];
    return acm;
};
auto t1 = std::async(f1, std::ref(v), 0, v.size() / 2);
auto t2 = std::async(f1, std::ref(v), v.size() / 2, v.size());

long long acm1 = t1.get();
long long acm2 = t2.get();
std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;

// 8. Shared Memory and Shared Resources ------------------------------------------------------
// std::lock_guard
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex; 		// the accesses in 2 functions is mutually exclusive
				// list_contains() will never see the list partway through a modification
void add_to_list(int new_value) {
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}
bool list_contains(int value_to_find) {
	std::lock_guard<std::mutex> guard(some_mutex);       
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

/* Don’t pass pointers and references to protected data outside the scope of the lock, whether by
returning them from a function, storing them in externally visible memory, or passing them as
arguments to user-supplied functions. */
// Here Mutex won't work, because 'unprotected->do_something()' modifies 'data' while it is 'locked'
class some_data {
public:
	void do_something();
private:
	int a;
	std::string b;
};

class data_wrapper {
public:
	template<typename Function>       // allows supply user-defined function
	void process_data(Function func) {
		std::lock_guard<std::mutex> l(m);
		func(data);
	}
private:
	some_data data;
	std::mutex m;
};

some_data * unprotected;
void malicious_function(some_data& protected_data) { unprotected = &protected_data; }
data_wrapper x;

void foo() {
	x.process_data(malicious_function);
	unprotected->do_something();
}


// 9. Thread-safe stack -----------------------------------------------------------------------
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception {
	const char* what() const throw();
};

template<typename T>
class threadsafe_stack {
private:
	std::stack<T> data;
	mutable std::mutex m;
public:
	threadsafe_stack(){}
	threadsafe_stack(const threadsafe_stack & other) {
		std::lock_guard<std::mutex> lock(other.m);
		data=other.data;
	}
	threadsafe_stack & operator=(const threadsafe_stack&) = delete;
	
	void push(T new_value) {
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop() {
		std::lock_guard<std::mutex> lock(m);
		if(data.empty()) throw empty_stack();
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}
	void pop(T & value) {
		std::lock_guard<std::mutex> lock(m);
		if(data.empty()) throw empty_stack();
		value=data.top();
		data.pop();
	}
	bool empty() const {
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};


// 10. Avoid deadlock where you need to acquire two or more locks together --------------------
class some_big_object;
void swap(some_big_object & lhs, some_big_object & rhs);

class X {
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const & sd): some_detail(sd) {}
	friend void swap(X& lhs, X& rhs) {
		if(&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		swap(lhs.some_detail, rhs.some_detail);
	}
};

// 11. Producer-consumer scenario -------------------------------------------------------------
#include <chrono>
#include <mutex>
#include <thread>
#include <future>

using namespace std;
static mutex theLock;

void produce(int * data) {
	for (int i = 1; i <= 5; ++i) {
		{
			lock_guard<mutex> lock(theLock);
			*data = i;
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
int main() 
{
	int data = 0;
	int val = 0;
	thread t(produce, &data);
	do {
		{
			lock_guard<mutex> lock(theLock);
			if (data != 5) data += 12;
			val = data;
		}
	} while (val != 5);
	t.join();
}

// 12. Compute a single function in parallel for > 1 different initial values -----------------
#include <chrono>
#include <mutex>
#include <thread>
#include <future>

using namespace std;

int myComputation(int x) {
	for (unsigned i = 0; i < 99999999; ++i) {
		x++;
	}
	return x;
}
int main() 
{
	packaged_task<int(int)> task1(&myComputation);
	packaged_task<int(int)> task2(&myComputation);

	future<int> val1 = task1.get_future();
	future<int> val2 = task2.get_future();

	thread t1(move(task1), 0);
	thread t2(move(task2), 5);

	bool s1 = false, s2 = false;
	do {
		s1 = val1.wait_for(chrono::milliseconds(50)) == future_status::ready;
		s2 = val2.wait_for(chrono::milliseconds(50)) == future_status::ready;
		cout << "Value 1 is " << (s1 ? "" : "not ") << "ready" << endl;
		cout << "Value 2 is " << (s2 ? "" : "not ") << "ready" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
	} while (!s1 || !s2);

	t1.join();
	t2.join();

	cout << "Value 1: " << val1.get() << endl;
	cout << "Value 2: " << val2.get() << endl;

	std::cin.get();
}

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
