#include <iostream>
#include <cstdlib>
#include <ctime>

class Node {
public:
	int date;
	Node *next;

	explicit Node(int date) {
		this->date = date;
		this->next = nullptr;
	}
};

void function(Node *&Input, Node *&Output_1, Node *&Output_2, bool (*pf)(int)) {
	Node *throughOut1 = nullptr;
	Node *throughOut2 = nullptr;
	Node *throughInput;

	while (Input != nullptr) {
		throughInput = Input;
		Input = Input->next;
		throughInput->next = nullptr;
		if ((*pf)(throughInput->date)) {
			if (throughOut1 == nullptr) {
				Output_1 = throughInput;
				throughOut1 = Output_1;
			} else {
				throughOut1->next = throughInput;
				throughOut1 = throughOut1->next;
			}
		} else {
			if (throughOut2 == nullptr) {
				Output_2 = throughInput;
				throughOut2 = Output_2;
			} else {
				throughOut2->next = throughInput;
				throughOut2 = throughOut2->next;
			}
		}
	}
}


bool isEven(int value) {
	return value % 2 == 0;
}

bool isMultipleOf3(int value) {
	return value % 3 == 0;
}

bool isLeapYear(int value) {
	return value % 4 == 0 and value % 100 != 0 or value % 400 == 0;
}

void fillList(Node *&HeadInput, int tam) {
	srand((int) time(0));
	HeadInput = new Node((rand() % 999) + 1);
	Node *tmp = HeadInput;
	for (int i = 0; i < tam - 1; i++) {
		Node *x = new Node((rand() % 999) + 1);
		tmp->next = x;
		tmp = tmp->next;
	}
}

void printList(const std::string& Name, Node *headList) {
	std::cout << Name << ": ";
	if (headList == nullptr) {
		std::cout << "Lista vacia" << std::endl;
		return;
	}
	for (Node *i = headList; i != nullptr; i = i->next) {
		std::cout << i->date << " ";
	}
	std::cout << std::endl;
}

int main() {
	int tam;
	int op;
	Node *HeadInput = nullptr;
	Node *HeadOutput_1 = nullptr;
	Node *HeadOutput_2 = nullptr;
	bool (*pFunction)(int);

	do {
		std::cout << "Introduzca tamaño de la lista: ";
		std::cin >> tam;
		fillList(HeadInput, tam);
		printList("Input", HeadInput);
		printList("Output1", HeadOutput_1);
		printList("Output2", HeadOutput_2);
		std::cout << "1. Es numero par" << std::endl;
		std::cout << "2. Es multiplo de 3" << std::endl;
		std::cout << "3. Es un año bisiesto" << std::endl;
		std::cout << "4. Salir" << std::endl;
		std::cout << "Elija una opcion: " << std::endl;
		std::cin >> op;
		switch (op) {
			case 1:
				pFunction = isEven;
				break;
			case 2:
				pFunction = isMultipleOf3;
				break;
			case 3:
				pFunction = isLeapYear;
				break;
			default:
				return 0;
		}

		function(HeadInput, HeadOutput_1, HeadOutput_2, pFunction);
		std::cout << "____________________________" << std::endl;

		printList("Input", HeadInput);
		printList("Output1", HeadOutput_1);
		printList("Output2", HeadOutput_2);
		std::cout << "\n\n\n\n";
	} while (true);
}