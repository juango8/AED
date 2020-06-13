//
// Created by juango on 7/06/20.
//
#include <iostream>

template<class T>
class Node {
public:
	T date;
	Node *next;
	Node *before;

	explicit Node(T date) {
		this->date = date;
		this->next = nullptr;
		this->before = nullptr;
	}
};

template<class T>
class List {
public:
	Node<T> *ptr_head;
	Node<T> *ptr_tail;

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
		this->ptr_tail = nullptr;
	}

	bool insert(T x) {
		auto *nNode = new Node<T>(x);

		if (!this->ptr_head) {
//			si esta vacia
			this->ptr_head = this->ptr_tail = nNode;
		} else if (x < this->ptr_head->date) {
//			si es antes de la cabeza
			nNode->next = this->ptr_head;
			this->ptr_head->before = nNode;
			this->ptr_head = nNode;
		} else if (x > this->ptr_tail->date) {
//			si es despues de la cola
			this->ptr_tail->next = nNode;
			nNode->before = this->ptr_tail;
			this->ptr_tail = nNode;
		} else {
//			si es entre la cabeza y la cola
			Node<T> *ptr_temp = this->ptr_head;

			while (ptr_temp != nullptr and ptr_temp->date < x) {
				ptr_temp = ptr_temp->next;
			}
			if (ptr_temp->date == x)
				return false;
			ptr_temp->before->next = nNode;
			nNode->next = ptr_temp;
			nNode->before = ptr_temp->before;
			ptr_temp->before = nNode;
			ptr_temp = nullptr;
			delete ptr_temp;
		}
		nNode = nullptr;
		delete nNode;
		return true;
	}

	bool remove(T x) {
		Node<T> *ptr_temp;

		if (this->ptr_head->date == x and this->ptr_tail->date == x) {
			ptr_temp = this->ptr_head;
			this->ptr_head = nullptr;
			this->ptr_tail = nullptr;
			delete ptr_temp;
		} else if (x == this->ptr_head->date) {
			ptr_temp = this->ptr_head;
			this->ptr_head = this->ptr_head->next;
			ptr_temp->next = nullptr;
			this->ptr_head->before = nullptr;
			delete ptr_temp;
		} else if (x == this->ptr_tail->date) {
			ptr_temp = this->ptr_tail;
			this->ptr_tail = this->ptr_tail->before;
			ptr_temp->before = nullptr;
			this->ptr_tail->next = nullptr;
			delete ptr_temp;
		} else {
			ptr_temp = this->ptr_head;

			while (ptr_temp != nullptr and ptr_temp->date != x)
				ptr_temp = ptr_temp->next;
			if (ptr_temp == nullptr)
				return false;
			ptr_temp->before->next = ptr_temp->next;
			ptr_temp->next = nullptr;
			ptr_temp->before->next->before = ptr_temp->before;
			ptr_temp->before = nullptr;
			delete ptr_temp;
		}
		return true;
	}

	void print() {
		if (this->ptr_head == nullptr) {
			std::cout << "Lista vacia." << std::endl;
			return;
		}
		std::cout << "next: ";
		for (Node<T> *x = ptr_head; x != nullptr; x = x->next)
			std::cout << x->date << " <-> ";
		std::cout << std::endl;
		std::cout << "befo: ";
		for (Node<T> *x = ptr_tail; x != nullptr; x = x->before)
			std::cout << x->date << " <-> ";
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
				break
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