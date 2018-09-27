/* Since the destruction order of deque<T> is unspecified by the standard
 * you should do one of two things: 
 * 1. provide a new container that destroys its elements last to first:
 */
template <class T>
struct my_deque : std::deque<T>
{
    using std::deque<T>::deque;
    ~my_deque() { while (!this->empty()) this->pop_back(); }
};

template <class T>
using my_stack = std::stack<T, my_deque<T>>;

/* 2. provide your own implementation of stack whose destructor pops all the elements:
 */
template <class T, class Container = std::deque<T>>
struct ordered_stack : std::stack<T, Container>
{
    using std::stack<T, Container>::stack;
    ~ordered_stack() {
        while (!this->empty()) { this->pop(); }
    }
};

