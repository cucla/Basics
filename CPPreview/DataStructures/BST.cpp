#include "stdafx.h"
#include <iostream>


template<typename Comparable>
class BinarySearchTree {
public:
	BinarySearchTree() { root = nullptr; }
	BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr } {
		root = clone(rhs.root);
	}
	BinarySearchTree(BinarySearchTree && rhs) noexcept : root{ rhs.root } {
		rhs.root = nullptr;
	}
	BinarySearchTree & operator=(const BinarySearchTree & rhs) {
		BinarySearchTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	BinarySearchTree & operator=(BinarySearchTree && rhs) noexcept {
		std::swap(root, rhs.root);
		return *this;
	}
	~BinarySearchTree() { makeEmpty(); }

	bool isEmpty() const { return root == nullptr; }
	bool contains(const Comparable & x) const { return contains(x, root); }
	const Comparable & findMin() const { 
		auto res = findMin(root);
		if (res) 
			return res->element;
	};
	const Comparable & findMax() const {
		auto res = findMax(root);
		if (res)
			return res->element;
	};
	void printTree(std::ostream & os = std::cout) const {
		printTree(root, os);
	}

	void makeEmpty() { makeEmpty(root); }
	void insert(const Comparable & x) { insert(x, root); }
	void insert(Comparable && x) { insert(x, root); }
	void remove(const Comparable & x) { remove(x, root); }

private:
	struct BinaryNode {
		Comparable element;
		BinaryNode * left;
		BinaryNode * right;
		BinaryNode(const Comparable & x, BinaryNode * lt, BinaryNode * rt) :
			element{ x }, left{ lt }, right{ rt } {}
		BinaryNode(Comparable && x, BinaryNode * lt, BinaryNode * rt) :
			element{ std::move(x) }, left{ lt }, right{ rt } {}
	};
	BinaryNode * root;

	bool contains(const Comparable & x, BinaryNode * r) const;
	BinaryNode * findMin(BinaryNode * r) const;
	BinaryNode * findMax(BinaryNode * r) const;
	void insert(const Comparable & x, BinaryNode * & r);
	void insert(Comparable && x, BinaryNode * & r);
	void remove(const Comparable & x, BinaryNode * & r);
	void makeEmpty(BinaryNode * & r);
	BinaryNode * clone(BinaryNode * r) const;
	void printTree(BinaryNode * r, std::ostream & os) const;
};

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode * r, std::ostream & os) const {
	if (r == nullptr)
		return;	
	os << "[";
	printTree(r->left, os);
	os << r->element << " ";
	printTree(r->right, os);
	os << "]";
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * r) const {
	if (r == nullptr) 
		return false;
	else if (x < r->element)
		return contains(x, r->left);
	else if (r->element < x)
		return contains(x, r->right);
	else 
		return true;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode * r) const {
	if (r == nullptr) 
		return nullptr; 
	if (r->left == nullptr)
		return r;
	return findMin(r->left);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * r) const {
	if (r != nullptr) {
		while (r->right != nullptr) 
			r = r->right;
	}
	return r;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode * & r) {
	if (!r)
		r = new BinaryNode{ x, nullptr, nullptr };
	else if (x < r->element)
		insert(x, r->left);
	else if (r->element < x)
		insert(x, r->right);
	else
		;  // duplicate do nothing
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode * & r) {
	if (r == nulltpr)
		r = new BinaryNode{ std::move(x), nullptr, nullptr };
	else if (x < r->element)
		insert(std::move(x), r->left);
	else if (r->element < x)
		insert(std::move(x), r->right);
	else
		;  // duplicate do nothing
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode * & r) {
	if (r == nullptr) 
		return;
	if (x < r->element) 
		remove(x, r->left);
	else if (r->element < x)
		remove(x, r->right);
	else {
		if (r->left != nullptr && r->right != nullptr) {
			r->element = findMin(r->right)->element;
			remove(r->element, r->right);
		}
		else {
			BinaryNode * oldNode = r;
			r = (r->left != nullptr) ? r->left : r->right;
			delete oldNode;
		}
	}
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * & r) {
	if (r != nullptr) {
		makeEmpty(r->left);
		makeEmpty(r->right);
		delete r;
	}
	r = nullptr;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone(BinaryNode * r) const {
	if (r == nullptr)
		return nullptr;
	else
		return new BinaryNode{ r->element, clone(r->left), clone(r->right) };
}



int main() {
	
	BinarySearchTree<int> t;
	t.insert(20);
	t.insert(25);
	t.insert(15);
	t.insert(10);
	t.insert(30);
	t.printTree();
	std::cout << std::endl;
	t.remove(20);
	t.printTree();
	std::cout << std::endl;
	t.remove(25);
	t.printTree();
	std::cout << std::endl;
	t.remove(30);
	t.printTree();
	std::cout << std::endl;


	std::cin.get();
}

