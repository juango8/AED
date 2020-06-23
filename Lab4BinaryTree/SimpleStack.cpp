//
// Created by juango on 23/06/20.
//

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
    friend class BTree;
    bool vacio();           //indica si la pila esta vacia
    void push(T elemento);  //agrega un elemento
    T pop();                //retira un elemento y devuelve su valor
    void print();           //imprime el contenido de la pila
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
void pila<T>::print() {
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

class Tupla {
public:
    Node *value;
    int state;

    explicit Tupla(Node *value) {
        this->value = value;
        this->state = 0;
    }

    void updateState(int newState) {
        this->state = newState;
    }
};

class BTree {
public:
    Node *root;

    BTree() {
        this->root = nullptr;
    }

    ~BTree() {
        pila<Tupla *> stackStates;
        stackStates.push(new Tupla(this->root));
        while (!stackStates.vacio()) {
            if (stackStates.top->valor->state == 0) {
                stackStates.top->valor->updateState(1);
                Node *temp = stackStates.top->valor->value->nodes[0];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 1) {
                stackStates.top->valor->updateState(2);
                Node *temp = stackStates.top->valor->value->nodes[1];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 2) {
                stackStates.top->valor->updateState(3);
                delete stackStates.top->valor->value;
            } else if (stackStates.top->valor->state == 3) {
                stackStates.pop();
            }
        }
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

    bool insert(int x) {
        Node **p;
        if (find(x, p))
            return false;
        *p = new Node(x);
        return true;
    }

    void InOrden() const {
        pila<Tupla *> stackStates;
        stackStates.push(new Tupla(this->root));
        while (!stackStates.vacio()) {
            if (stackStates.top->valor->state == 0) {
                stackStates.top->valor->updateState(1);
                Node *temp = stackStates.top->valor->value->nodes[0];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 1) {
                stackStates.top->valor->updateState(2);
                cout << stackStates.top->valor->value->date;
            } else if (stackStates.top->valor->state == 2) {
                stackStates.top->valor->updateState(3);
                Node *temp = stackStates.top->valor->value->nodes[1];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 3) {
                stackStates.pop();
            }
        }
        cout << endl;
    }

    void PreOrden() const {
        pila<Tupla *> stackStates;
        stackStates.push(new Tupla(this->root));
        while (!stackStates.vacio()) {
            if (stackStates.top->valor->state == 0) {
                stackStates.top->valor->updateState(1);
                cout << stackStates.top->valor->value->date;
            } else if (stackStates.top->valor->state == 1) {
                stackStates.top->valor->updateState(2);
                Node *temp = stackStates.top->valor->value->nodes[0];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 2) {
                stackStates.top->valor->updateState(3);
                Node *temp = stackStates.top->valor->value->nodes[1];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 3) {
                stackStates.pop();
            }
        }
        cout << endl;
    }

    void PostOrden() const {
        pila<Tupla *> stackStates;
        stackStates.push(new Tupla(this->root));
        while (!stackStates.vacio()) {
            if (stackStates.top->valor->state == 0) {
                stackStates.top->valor->updateState(1);
                Node *temp = stackStates.top->valor->value->nodes[0];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 1) {
                stackStates.top->valor->updateState(2);
                Node *temp = stackStates.top->valor->value->nodes[1];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 2) {
                stackStates.top->valor->updateState(3);
                cout << stackStates.top->valor->value->date;
            } else if (stackStates.top->valor->state == 3) {
                stackStates.pop();
            }
        }
        cout << endl;
    }

    void Reverse() const {
        pila<Tupla *> stackStates;
        stackStates.push(new Tupla(this->root));
        while (!stackStates.vacio()) {
            if (stackStates.top->valor->state == 0) {
                stackStates.top->valor->updateState(1);
                Node *temp = stackStates.top->valor->value->nodes[1];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 1) {
                stackStates.top->valor->updateState(2);
                cout << stackStates.top->valor->value->date;
            } else if (stackStates.top->valor->state == 2) {
                stackStates.top->valor->updateState(3);
                Node *temp = stackStates.top->valor->value->nodes[0];
                if (temp != nullptr)
                    stackStates.push(new Tupla(temp));
            } else if (stackStates.top->valor->state == 3) {
                stackStates.pop();
            }
        }
        cout << endl;
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
                        T.InOrden();
                        std::cout << std::endl;
                        break;
                    case 2:
                        T.PostOrden();
                        std::cout << std::endl;
                        break;
                    case 3:
                        T.PreOrden();
                        std::cout << std::endl;
                        break;
                    case 4:
                        T.Reverse();
                        std::cout << std::endl;
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
