//
// Created by juango on 7/06/20.
//

#include <iostream>

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

template<class T>
class List {
public:
	Node<T> *ptr_head;

	List() {
		this->ptr_head = nullptr;
	}

	~List() {
		Node<T> *current = this->ptr_head;
		while (current != nullptr) {
			Node<T> *temp = current->next;
			delete current;
			current = temp;
		}
		this->ptr_head = nullptr;
	}

	bool find(T x, Node<T> **&p) {
		for (p = &ptr_head; (*p) && (*p)->date < x; p = &((*p)->next)) {}
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
		if (this->ptr_head == nullptr) {
			std::cout << "Lista vacia." << std::endl;
			return;
		}
		for (Node<T> *x = ptr_head; x != nullptr; x = x->next)
			std::cout << x->date << " -> ";
		std::cout << std::endl;
	}
};

int main() {
	List<int> L;
	int op, x;

	do {
		std::cout << "\n \n \n \n \n \n \n";
		L.print();
		std::cout << "\n1.- Ingresar nuevo valor." << std::endl;
		std::cout << "2.- Eliminar un valor." << std::endl;
		std::cout << "3.- Imprimir la lista." << std::endl;
		std::cout << "4.- Salir." << std::endl;
		std::cout << "Elija una opcion: ";
		std::cin >> op;
		switch (op) {
			case 1:
				std::cout << "Ingrese el nuevo valor de la lista" << std::endl;
				std::cin >> x;
				L.insert(x);
				break;
			case 2:
				std::cout << "Elimine un valor de la lista" << std::endl;
				std::cin >> x;
				L.remove(x);
				break;
			case 3:
				std::cout << "Los valores de la lista son:" << std::endl;
				L.print();
				break;
			case 4:
				std::cout << "Programa terminado." << std::endl;
				return 0;
			default:
				break;
		}
	} while (true);
}
