#include <iostream>

class Node {
public:
	int date;
	Node *next;

	explicit Node(int date) {
		this->date = date;
		this->next = nullptr;
	}
};

bool eraseMultiplies(Node **&HeadInput, int num) {
	Node **temp = HeadInput;
	if (num == 0 or num == 1)
		return false;
	while (*temp != nullptr) {
		if ((*temp)->date % num == 0) {
			*temp = (*temp)->next;
		} else
			temp = &((*temp)->next);
	}
	return true;
}

void fillList(Node *&HeadInput, int tam) {
	HeadInput = new Node(1);
	Node *tmp = HeadInput;
	for (int i = 2; i < tam + 1; i++) {
		Node *x = new Node(i);
		tmp->next = x;
		tmp = tmp->next;
	}
}

void printList(const std::string &Name, Node *headList) {
	std::cout << Name << ": ";
	if (headList == nullptr) {
		std::cout << "Lista vacia" << std::endl;
		return;
	}
	for (Node *i = headList; i != nullptr; i = i->next)
		std::cout << i->date << " ";
	std::cout << std::endl;
}

int main() {
	int tam;
	int num;
	Node *HeadInput = nullptr;
	Node **test;
	test = &HeadInput;

	std::cout << "Introduzca numero: ";
	std::cin >> tam;
	fillList(HeadInput, tam);
	do {
		printList("Lista", HeadInput);
		std::cout << "Introduzca numero a eliminar: ";
		std::cin >> num;
	} while (eraseMultiplies(test, num));
	std::cout << "Lista vacia" << std::endl;

	return 0;
}