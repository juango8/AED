//
// Created by juango on 12/06/20.
//

#include <iostream>

class Node {
public:
	int date;
	Node *nodes[2]{};

	explicit Node(int date) {
		this->date = date;
		nodes[0] = nullptr;
		nodes[1] = nullptr;
	}
};

class BTree {
public:
	Node *root;

	BTree() {
		this->root = nullptr;
	}

	static Node **rep(Node **p) {
		p = &((*p)->nodes[1]);
		while ((*p)->nodes[0])
			p = &((*p)->nodes[0]);
		return p;
	}

	bool find(int x, Node **&p) {
		p = &(this->root);
		while (*p && (*p)->date != x)
			p = &((*p)->nodes[(*p)->date < x]);
		return *p != nullptr;
	}

	bool insert(int x) {
		Node **p;
		if (find(x, p))
			return false;
		*p = new Node(x);
		return true;
	}

	bool remove(int x) {
		Node **p;
		if (!find(x, p))
			return false;
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			Node **q = rep(p);
			(*p)->date = (*q)->date;
			p = q;
		}
		auto t = *p;
		*p = (*p)->nodes[!(*p)->nodes[0]];
		delete t;
		return true;
	}

	void InOrden(Node *k) {
		if (!k)
			return;
		InOrden(k->nodes[0]);
		std::cout << k->date;
		InOrden(k->nodes[1]);
	}
	void PreOrden(Node *k) {
		if (!k)
			return;
		std::cout << k->date;
		InOrden(k->nodes[0]);
		InOrden(k->nodes[1]);
	}
	void PostOrden(Node *k) {
		if (!k)
			return;
		InOrden(k->nodes[0]);
		InOrden(k->nodes[1]);
		std::cout << k->date;
	}
};

int main() {
	BTree test;
	test.insert(5);
	test.insert(1);
	test.insert(2);
	test.insert(9);
	test.insert(8);
	test.insert(7);
	test.insert(3);
	test.InOrden(test.root);
	std::cout<<std::endl;
	test.remove(5);
	test.InOrden(test.root);
	std::cout<<std::endl;
	test.remove(9);
	test.InOrden(test.root);
	std::cout<<std::endl;
	test.remove(2);
	test.InOrden(test.root);
	std::cout<<std::endl;
	return 0;
}
