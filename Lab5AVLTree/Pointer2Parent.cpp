//
// Created by juango on 14/07/20.
//

#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
struct nodo {
    T valor;
    nodo *next;
    nodo *before;

    explicit nodo(T _valor, nodo *_next = nullptr, nodo *_before = nullptr) {
        valor = _valor;
        next = _next;
        before = _before;
    };
};

template<typename T>
class pila {
    nodo<T> *top = nullptr;
public:
    friend class BTree;

    //indica si la pila esta vacia
    bool vacio() {
        return top == nullptr;
    }

    //agrega un elemento
    void push(T elemento) {
        if (vacio()) {
            auto *temp = new nodo<T>(elemento);
            this->top = temp;
        } else {
            auto *temp = new nodo<T>(elemento, this->top);
            this->top->before = temp;
            this->top = temp;
        }
    }

    //retira un elemento y devuelve su valor
    T pop() {
        if (!vacio()) {
            nodo<T> *temp = this->top;
            this->top->next->before = nullptr;
            this->top = this->top->next;
            temp->next = nullptr;
            return temp->valor;
        }
        return NULL;
    }

    ~pila() {
        nodo<T> *current = this->top;
        while (current != nullptr) {
            nodo<T> *temp = current->next;
            delete current;
            current = temp;
        }
        this->top = nullptr;
    }
};

class Node {
public:
    int date;
    Node *nodes[2]{};
    Node *parent;
    int height;

    explicit Node(int date) {
        this->date = date;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        this->parent = nullptr;
        this->height = 0;
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

    explicit Tupla(Node *value, int state) {
        this->value = value;
        this->state = state;
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

    bool find(int x, Node **&p, Node **&parent) {
        for (p = &(this->root); *p and (*p)->date != x; p = &((*p)->nodes[(*p)->date < x])){
            parent = p;
        }
        return *p != nullptr;
    }

    bool remove(int x) {
        Node **p;
        Node **parent;
        if (!find(x, p, parent))
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
        Node **parent = nullptr;
        if (find(x, p, parent))
            return false;
        *p = new Node(x);
        if (parent)
            (*p)->parent = (*parent);
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

    void Level() const {
        pila<Tupla *> stackStates;
        int level = 0;
        stackStates.push(new Tupla(this->root, level));
        nodo<Tupla *> *iterator = stackStates.top;
        int num_empty = 0;
        while (num_empty != pow(2, level)) {
            if (iterator->valor->state == level) {
                num_empty = 0;
                level++;
            }
            Tupla *temp;
            if (iterator->valor->value == nullptr or iterator->valor->value->nodes[0] == nullptr) {
                num_empty++;
                temp = new Tupla(nullptr, level);
                stackStates.push(temp);
            } else {
                temp = new Tupla(iterator->valor->value->nodes[0], level);
                stackStates.push(temp);
            }
            if (iterator->valor->value == nullptr or iterator->valor->value->nodes[1] == nullptr) {
                num_empty++;
                temp = new Tupla(nullptr, level);
                stackStates.push(temp);
            } else {
                temp = new Tupla(iterator->valor->value->nodes[1], level);
                stackStates.push(temp);
            }
            iterator = iterator->before;
        }
        nodo<Tupla *> *tmp = stackStates.top;
        int levelTemp = tmp->valor->state;
        string asd;
        for (; tmp; tmp = tmp->next) {
            if (levelTemp == tmp->valor->state) {
                asd.erase(0, pow(2, (level - tmp->valor->state - 1)) - 1);
                asd = "\n" + asd;
                asd = string(pow(2, (level - tmp->valor->state)) - 1, ' ') + asd;
                levelTemp--;
            }
            if (tmp->valor->value)
                asd = string(pow(2, (level - levelTemp)) - 1, ' ') + to_string(tmp->valor->value->date) + asd;
            else
                asd = string(pow(2, (level - levelTemp)) - 1, ' ') + "_" + asd;
        }
        asd.erase(0, pow(2, (level)) - 1);
        cout << asd << endl;
    }
};


int main() {
    BTree T;
    int op, x;

    do {
        std::cout << "\n1.- Ingresar nuevo valor." << std::endl;
        std::cout << "2.- Eliminar un valor." << std::endl;
        std::cout << "3.- Recorrer el arbol." << std::endl;
        std::cout << "4.- Niveles." << std::endl;
        std::cout << "5.- Salir." << std::endl;
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
                T.Level();
                std::cout << "cada \"_\" significa un espacio null." << std::endl;
                break;
            case 5:
                std::cout << "Programa terminado." << std::endl;
                return 0;
            default:
                break;
        }
    } while (true);
}
