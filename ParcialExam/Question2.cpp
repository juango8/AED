#include <iostream>

template<class T>
class Node {
public:
	T date;
	Node *next;

	Node(T date) {
		this->date = date;
		this->next = nullptr;
	}
};

template<class T>
void mixin(Node<T>* ptr_head, int lenght){
	int mixinTime = rand() % 20;
	for (int i = 0; i < mixinTime; i++){
		int temporal = rand() % lenght + 1;
		Node<T>* temp = ptr_head->next;
		Node<T>* temp1 = ptr_head;
		for (int j = 0; j < temporal; j++)
			temp1 = temp1->next;
		if (temp && temp1){
			T temp3 = temp->date;
			temp->date = temp1->date;
			temp1->date = temp3;
		}
	}
}

template<class T>
class List {
public:
	Node<T> *ptr_head;
	int lenght;

	List() {
		this->ptr_head = nullptr;
		this->lenght = 0;
	}
	bool find(T x, Node<T>**& p){
		for(p = &ptr_head; (*p) && (*p)->date != x; p = &((*p)->next) ){}
		return (*p) && ((*p)->date == x);
	}
	bool insert(T x){
		Node<T>** p;
		if (find(x, p))
			return false;
		auto* temp = new Node<T>(x);
		temp->next = *p;
		*p = temp;
		this->lenght++;
		mixin(ptr_head, lenght);
		return true;
	}
	bool remove(T x){
		Node<T>** p;
		if (!find(x, p))
			return false;
		Node<T>* temp = *p;
		*p = (*p)->next;
		delete temp;
		this->lenght--;
		return true;
	}
	void print(){
		for (Node<T>* x = ptr_head; x != nullptr; x = x->next)
			std::cout << x->date << " -> ";
		std::cout<<std::endl;
	}
};

int main(){
	List<int> test;
	Node<int>** temp;
	test.insert(5);
	test.insert(8);
	test.insert(9);
	test.insert(10);
	test.insert(11);
	test.insert(12);
	test.insert(13);
	test.insert(15);
	test.print();
	test.remove(5);
	test.remove(15);
	test.remove(11);
	test.print();
	std::cout << test.find(9,temp) << std::endl;
	return 0;
}