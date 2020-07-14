#include <iostream>

using namespace std;

template<typename T>
struct nodo {
	T valor;
	nodo *next;

	nodo(T _valor, nodo *_next = nullptr) {
		valor = _valor;
		next = _next;
	};
};

template<typename T>
class pila {
	nodo<T> *top = nullptr;
public:
	bool vacio();           //indica si la pila esta vacia
	void push(T elemento);  //agrega un elemento
	T pop();                //retira un elemento y devuelve su valor
    [[maybe_unused]] void print();           //imprime el contenido de la pila
	~pila();
};

template<typename T>
bool pila<T>::vacio() {
	if (top)
		return false;
	else
		return true;
}

template<typename T>
[[maybe_unused]] void pila<T>::print() {
	nodo<T> *tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->valor << endl;
	cout << "base" << endl;
}

template<typename T>
void pila<T>::push(T elemento) {
	//TO DO
	if (vacio()) {
		nodo<T> *temp = new nodo<T>(elemento);
		this->top = temp;
	} else {
		nodo<T> *temp = new nodo<T>(elemento, this->top);
		this->top = temp;
	}
}

template<typename T>
T pila<T>::pop() {
	//TO DO
	if (!vacio()) {
		nodo<T> *temp = this->top;
		this->top = this->top->next;
		temp->next = nullptr;
		return temp->valor;
	}
	return NULL;
}

template<typename T>
pila<T>::~pila() {
	//TO DO;
	nodo<T> *current = this->top;
	while (current != nullptr) {
		nodo<T> *temp = current->next;
		delete current;
		current = temp;
	}
	this->top = nullptr;
}

int main() {
	pila<int> intPila;
	pila<char> charPila;
	cout << "hola";

	intPila.push(1);
	intPila.push(2);
	intPila.push(3);

	intPila.print();
	cout << endl;
	cout << "sale: " << intPila.pop() << endl;
	intPila.print();
	cout << endl;

	charPila.push('A');
	charPila.push('B');
	charPila.push('C');

	charPila.print();
	cout << endl;
	cout << "sale: " << charPila.pop() << endl;
	charPila.print();
	cout << endl;

	charPila.print();

}