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

    ~BTree() {
        DestructorRecursive(this->root);
    }

    void DestructorRecursive(Node* temp){
        if (!temp)
            return;
        DestructorRecursive(temp->nodes[0]);
        DestructorRecursive(temp->nodes[1]);
        delete temp;
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
        PreOrden(k->nodes[0]);
        PreOrden(k->nodes[1]);
	}

	void PostOrden(Node *k) {
		if (!k)
			return;
        PostOrden(k->nodes[0]);
        PostOrden(k->nodes[1]);
		std::cout << k->date;
	}

	void Reverse(Node *k) {
        if (!k)
            return;
        Reverse(k->nodes[1]);
        std::cout << k->date;
        Reverse(k->nodes[0]);
    }
};

int main() {
    BTree T;
    int op, x;

    do {
        std::cout << "\n1.- Ingresar nuevo valor." << std::endl;
        std::cout << "2.- Eliminar un valor." << std::endl;
        std::cout << "3.- Recorrer el arbol." << std::endl;
        std::cout << "4.- Salir." << std::endl;
        std::cout << "Elija una opcion: ";
        std::cin >> op;
        switch (op) {
            case 1:
                std::cout << "Ingrese el nuevo valor de la lista" << std::endl;
                std::cin >> x;
                T.insert(x);
                break;
            case 2:
                std::cout << "Elimine un valor de la lista" << std::endl;
                std::cin >> x;
                T.remove(x);
                break;
            case 3:
                std::cout << "1.- In Orden." << std::endl;
                std::cout << "2.- Post Orden." << std::endl;
                std::cout << "3.- Pre Orden." << std::endl;
                std::cout << "4.- Reverse." << std::endl;
                std::cout << "5.- Salir al menu principal." << std::endl;
                std::cin >> x;
                switch (x) {
                    case 1:
                        T.InOrden(T.root);
                        std::cout<<std::endl;
                        break;
                    case 2:
                        T.PostOrden(T.root);
                        std::cout<<std::endl;
                        break;
                    case 3:
                        T.PreOrden(T.root);
                        std::cout<<std::endl;
                        break;
                    case 4:
                        T.Reverse(T.root);
                        std::cout<<std::endl;
                    default:
                        break;
                }
                break;
            case 4:
                std::cout << "Programa terminado." << std::endl;
                return 0;
            default:
                break;
        }
    } while (true);
}
