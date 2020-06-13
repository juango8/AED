//
// Created by juango on 8/06/20.
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
	int lenght = 0;

	List() {
		this->ptr_head = nullptr;
	}

	~List() {
		Node<T> *current = this->ptr_head;
		int i = 0;
		while (current != nullptr and i < this->lenght) {
			Node<T> *temp = current->next;
			delete current;
			current = temp;
			i++;
		}
		this->ptr_head = nullptr;
	}

	bool find(T x, Node<T> **&p) {
		int i = 0;
		for (p = &ptr_head; (*p) && (*p)->date < x && i < this->lenght; i++, p = &((*p)->next)) {}
		return (*p) && ((*p)->date == x);
	}

	bool insert(T x) {
		Node<T> **p;
		if (find(x, p))
			return false;
		auto *temp = new Node<T>(x);
		temp->next = *p;
		if (temp->next == nullptr)
			temp->next = temp;
		else if ((*p)->next == (*p)) {
			(*p)->next = temp;
			*p = temp;
		}
		*p = temp;
		this->lenght++;
		return true;
	}

	bool remove(T x) {
		Node<T> **p;
		Node<T> **p2;
		bool test = false;
		if (!find(x, p))
			return false;
		if ((*p) == this->ptr_head and this->lenght > 1) {
			test = true;
		} else if (this->lenght == 1)
			(*p)->next = nullptr;
		Node<T> *temp = *p;
		*p = (*p)->next;
		if (test) {
			int i = 0;
			for (p2 = &ptr_head; (*p2) && (*p2) != temp && i < this->lenght; i++, p2 = &((*p2)->next)) {}
			*p2 = this->ptr_head;
		}
		delete temp;
		this->lenght--;
		return true;
	}

	void print() {
		int i = 0;
		if (this->ptr_head == nullptr) {
			std::cout << "Lista vacia." << std::endl;
			return;
		}
		std::cout << ptr_head->date << " -> ";
		for (Node<T> *x = ptr_head->next; x != nullptr && i < 20; x = x->next) {
			i++;
			std::cout << x->date << " -> ";
		}
		std::cout << std::endl;
	}
};

int main() {
	List<int> L;
//	List<int, Lesser<int>> L;
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