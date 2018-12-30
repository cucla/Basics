#include "stdafx.h"
#include "iostream"
#include <list>


// no error checks

template<typename Object>
class myList {
private:
	struct Node {
		Node(const Object & d = Object{},
			Node * p = nullptr,
			Node * n = nullptr)
			: data{ d }, prev{ p }, next{ n } {}

		Node(Object && d,
			Node * p = nullptr,
			Node * n = nullptr)
			: data{ std::move(d) }, prev{ p }, next{ n } {}

		Object data;
		Node * prev;
		Node * next;
	};

public:
	class const_iterator {
	public:
		const_iterator() : _current{ nullptr } {}

		const Object & operator*() const { return retrieve(); }
		const_iterator & operator++() {
			_current = _current->next;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const const_iterator & rhs) const {
			return _current == rhs._current;
		}
		bool operator!=(const const_iterator & rhs) const {
			return !(*this == rhs);
		}

	protected:
		// to determine if itr is to the correct list
		// const myList<Object> * theList;
		// const_iterator(const myList<Object> & lst, Node * n) : theList{ &lst }, _current{ n } {}
		Node * _current;
		const_iterator (Node * n) : _current{ n } {}
		Object & retrieve() const { return _current->data; }

		friend class myList<Object>;
	};
	class iterator : public const_iterator {
	public:
		iterator() {}

		Object & operator*() { return const_iterator::retrieve(); }
		const Object & operator*() const { return const_iterator::operator*(); }

		iterator & operator++() {
			this->_current = this->_current->next;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
	protected:
		iterator(Node * n) : const_iterator{ n } {}

		friend class myList<Object>;
	};

public:
	myList(int initialSize = 0) { 
		init(); 
		for (int i = 0; i < initialSize; i++) {
			auto a = new Object{};
			push_back(*a);
		}
	}
	myList(const myList & rhs) {
		init();
		for (auto x : rhs)
			push_back(x);
	}
	myList(myList && rhs) noexcept :
		_size{rhs._size},
		_head{rhs._head},
		_tail{rhs._tail}
	{
		rhs._size = 0;
		rhs._head = nullptr;
		rhs._tail = nullptr;
	}
	myList & operator= (const myList & rhs) {
		myList copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	myList & operator= (myList && rhs) noexcept {
		std::swap(_size, rhs._size);
		std::swap(_head, rhs._head);
		std::swap(_tail, rhs._tail);
		return *this;
	}
	~myList() { 
		clear(); 
		delete _head;
		delete _tail;
	}

	const_iterator begin() const { return { _head->next }; }
	const_iterator end() const { return { _tail }; }
	iterator begin() { return { _head->next }; }
	iterator end() { return { _tail }; }

	Object & front() { return *begin(); }
	Object & back() { return *--end(); }
	const Object & front() const { return *begin(); }
	const Object & back() const { return *--end(); }

	int size() const { return _size; }
	bool empty() const { return size() == 0; }

	// insert x before the itr
	iterator insert(iterator itr, const Object & x) {
		Node * p = itr._current;
		++_size;
		return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
	}
	iterator insert(iterator itr, Object && x) {
		Node * p = itr._current;
		++_size;
		return { p->prev = p->prev->next = new Node{ std::move(x), p->prev, p } };
	}

	// erase item at itr
	iterator erase(iterator itr) {
		Node * p = itr._current;
		--_size;
		iterator toReturn{ p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		return toReturn;
	}
	iterator erase(iterator from, iterator to) {
		for (iterator itr = from; itr != to;)
			itr = erase(itr);
		return to;
	}

	void push_front(const Object & item) { insert(begin(), item); }
	void push_front(Object && item) { insert(begin(), std::move(item)); }
	void push_back(const Object & item) { insert(end(), item); }
	void push_back(Object && item) { insert(end(), std::move(item)); }
	void pop_front() { erase(begin()); }
	void pop_back() { erase(--end()); }

	void clear() {
		while (!empty())
			pop_front();
	}

	void print(std::ostream & os = std::cout) const {
		const_iterator itr = begin();
		while (itr != end()) {
			os << itr._current->data << " ";
			++itr;
		}
	}

private:
	Node * _head;
	Node * _tail;
	int _size;

	void init() {
		_head = new Node{};
		_tail = new Node{};
		_head->next = _tail;
		_tail->prev = _head;
		_size = 0;
	}
};

template<typename Object>
std::ostream & operator<< (std::ostream & out, const myList<Object> & rhs) {
	rhs.print(out);
	return out;
}


void printLst(const std::list<int> & l) {
	for (auto el : l) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

int main() {
	std::list<int> libL01;					printLst(libL01);
	std::list<int> libL02(5);				printLst(libL02);
	std::list<int> libL03(5, 100);				printLst(libL03);
	std::list<int> libL04 = libL03;				printLst(libL04);
	std::list<int> libL05(libL03);				printLst(libL05);
	std::list<int> libL06{ 1, 2, 3, 4, 5, 6 };		printLst(libL06);
	std::list<int> libL07 = { 1, 2, 3, 4, 5, 6 };		printLst(libL07);


	std::cout << "myList: " << std::endl;
	myList<int> lst01;					std::cout << lst01 << std::endl;
	myList<int> lst02(5);					std::cout << lst02 << std::endl;
	myList<int> lst03 = lst02;				std::cout << lst03 << std::endl;
	myList<int> lst04(lst02);				std::cout << lst04 << std::endl;



	std::cin.get();
}
