//
// Created by juango on 12/06/20.
//

#include <iostream>

template<class T>
class Less {
public:
	inline bool operator()(T a, T b) {
		return a < b;
	}
};

template<class T>
class Greater {
public:
	inline bool operator()(T a, T b) {
		return a > b;
	}
};

template<class T>
class Node {
public:
	T date;
	Node *next;

	explicit Node(T date) {
		this->date = date;
		this->next = nullptr;
	}
};

template<class T, class C>
class List {
public:
	Node<T> *ptr_head;
	C cmp;

	List() {
		this->ptr_head = nullptr;
	}

	bool find(T x, Node<T> **&p) {
		for (p = &ptr_head; (*p) && cmp((*p)->date,x); p = &((*p)->next)) {}
		return (*p) && ((*p)->date == x);
	}

	bool insert(T x) {
		Node<T> **p;
		if (find(x, p))
			return false;
		auto *temp = new Node<T>(x);
		temp->next = *p;
		*p = temp;
		return true;
	}

	bool remove(T x) {
		Node<T> **p;
		if (!find(x, p))
			return false;
		Node<T> *temp = *p;
		*p = (*p)->next;
		delete temp;
		return true;
	}

	void print() {
		for (Node<T> *x = ptr_head; x != nullptr; x = x->next)
			std::cout << x->date << " -> ";
		std::cout << std::endl;
	}
};

int main() {
	List<int, Greater<int>> test;
	test.insert(9);
	test.insert(1);
	test.insert(5);
	test.insert(15);
	test.print();
	test.remove(5);
	test.print();
	List<int, Less<int>> test1;
	test1.insert(9);
	test1.insert(1);
	test1.insert(5);
	test1.insert(15);
	test1.print();
	test1.remove(5);
	test1.print();
	return 0;
}
