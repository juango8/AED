//
// Created by juango on 8/06/20.
//

#include <iostream>

using namespace std;

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
	Node<T> *ptr_tail;

	List() {
		this->ptr_head = nullptr;
		this->ptr_tail = nullptr;
	}

	~List() {
		this->ptr_tail->next = nullptr;
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
			this->ptr_tail->next = this->ptr_head;
		} else if (x < this->ptr_head->date) {
//			si es antes de la cabeza
			nNode->next = this->ptr_head;
			this->ptr_head = nNode;
			this->ptr_tail->next = this->ptr_head;
		} else if (x > this->ptr_tail->date) {
//			si es despues de la cola
			this->ptr_tail->next = nNode;
			this->ptr_tail = nNode;
			this->ptr_tail->next = this->ptr_head;
		} else {
//			si es entre la cabeza y la cola
			Node<T> *ptr_temp = this->ptr_head;
			Node<T> *ptr_temp2 = nullptr;

			while (ptr_temp != nullptr and ptr_temp->date < x) {
				ptr_temp2 = ptr_temp;
				ptr_temp = ptr_temp->next;
			}
			if (ptr_temp->date == x)
				return false;
			ptr_temp2->next = nNode;
			nNode->next = ptr_temp;
			ptr_temp = ptr_temp2 = nullptr;
			delete ptr_temp;
			delete ptr_temp2;
		}
		nNode = nullptr;
		delete nNode;
		return true;
	}

	bool remove(T x) {
		Node<T> *ptr_temp;
		Node<T> *ptr_temp2 = nullptr;

		if (this->ptr_head == this->ptr_tail) {
			ptr_temp = this->ptr_head;
			this->ptr_head = nullptr;
			this->ptr_tail = nullptr;
			delete ptr_temp;
		} else if (x == this->ptr_head->date) {
			ptr_temp = this->ptr_head;
			this->ptr_head = this->ptr_head->next;
			ptr_temp->next = nullptr;
			this->ptr_tail->next = this->ptr_head;
			delete ptr_temp;
		} else if (x == this->ptr_tail->date) {
			ptr_temp = this->ptr_head;
			while (ptr_temp->next != nullptr and ptr_temp->next->date != x) {
				ptr_temp = ptr_temp->next;
			}
			this->ptr_tail = ptr_temp;
			ptr_temp = this->ptr_tail->next;
			this->ptr_tail->next = this->ptr_head;
			delete ptr_temp;
		} else {
			ptr_temp = this->ptr_head;

			while (ptr_temp != nullptr and ptr_temp->date != x) {
				ptr_temp2 = ptr_temp;
				ptr_temp = ptr_temp->next;
			}
			if (ptr_temp == nullptr)
				return false;
			ptr_temp2->next = ptr_temp->next;
			ptr_temp->next = nullptr;
			ptr_temp2 = nullptr;
			delete ptr_temp;
			delete ptr_temp2;
		}
		return true;
	}

	void print() {
		if (this->ptr_head == nullptr) {
			cout << "Lista vacia." << endl;
			return;
		}
		cout << ptr_head->date << " -> ";
		for (Node<T> *x = ptr_head->next; x != ptr_head; x = x->next) {
			cout << x->date << " -> ";
		}
		cout << endl;
	}
};

int main() {
	List<int> L;
	int op, x;

	do {
		cout << "\n \n \n \n \n \n \n";
		L.print();
		cout << "\n1.- Ingresar nuevo valor." << endl;
		cout << "2.- Eliminar un valor." << endl;
		cout << "3.- Imprimir la lista." << endl;
		cout << "4.- Salir." << endl;
		cout << "Elija una opcion: ";
		cin >> op;
		switch (op) {
			case 1:
				cout << "Ingrese el nuevo valor de la lista" << endl;
				cin >> x;
				L.insert(x);
				break;
			case 2:
				cout << "Elimine un valor de la lista" << endl;
				cin >> x;
				L.remove(x);
				break;
			case 3:
				cout << "Los valores de la lista son:" << endl;
				L.print();
				break;
			case 4:
				cout << "Programa terminado." << endl;
				return 0;
			default:
				break;
		}
	} while (true);
}



