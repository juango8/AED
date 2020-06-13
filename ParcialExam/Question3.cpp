#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode {
	explicit CBinNode(int _v) {
		value = _v;
		nodes[0] = nodes[1] = nullptr;
	}

	int value;
	CBinNode *nodes[2]{};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree {
public:
	CBinTree();

	~CBinTree();

	bool Find(int x, CBinNode **&p);

	bool Insert(int x);

	bool Remove(int x);

	static CBinNode **Rep(CBinNode **p);

	void InOrder(CBinNode *n);

	void Print();

private:
	CBinNode *m_root;
};

CBinTree::CBinTree() { m_root = nullptr; }

CBinTree::~CBinTree() {
	// ?
}

bool CBinTree::Find(int x, CBinNode **&p) {
	for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
	return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
	CBinNode **p;
	if (Find(x, p)) return false;
	*p = new CBinNode(x);
	return false;
}

bool CBinTree::Remove(int x) {
	CBinNode **p;
	if (!Find(x, p)) return false;
	if ((*p)->nodes[0] && (*p)->nodes[1]) {
//		cout << "2" << endl;
		CBinNode **q = Rep(p);
		(*p)->value = (*q)->value;
		p = q;
		CBinNode *t = *p;
		*p = (*p)->nodes[!(*p)->nodes[0]];
	} else if (!((*p)->nodes[0]) && !((*p)->nodes[1])) {
//		cout << "0" << endl;
		*p = nullptr;
	} else {
//		cout << "1" << endl;
		CBinNode *t = *p;
		*p = (*p)->nodes[!(*p)->nodes[0]];
	}
	delete t;
	return true;
}

CBinNode **CBinTree::Rep(CBinNode **p) {
	bool b = rand() % 2;
	for (p = &((*p)->nodes[b]); (*p)->nodes[!b]; p = &((*p)->nodes[!b]));
	return p;
}

void CBinTree::InOrder(CBinNode *n) {
	if (!n) return;
	InOrder(n->nodes[0]);
	cout << n->value << " ";
	InOrder(n->nodes[1]);
}

void CBinTree::Print() {
	InOrder(m_root);
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	CBinTree t;

	t.Insert(50);
	t.Insert(30);
	t.Insert(60);
	t.Insert(80);
	t.Insert(55);
	t.Insert(11);
	t.Insert(33);
	t.Insert(5);
	t.Insert(14);
	t.Insert(31);
	t.Insert(48);
	t.Print();

	t.Remove(31);
	t.Print(); //case 0
	t.Remove(14);
	t.Print(); //case 0

	t.Remove(11);
	t.Print(); //case 1, left
	t.Remove(33);
	t.Print(); //case 1, right

	t.Remove(50);
	t.Print(); //case 2

	t.Remove(60);
	t.Print();
	t.Remove(48);
	t.Print();
	t.Remove(55);
	t.Print();
	t.Remove(5);
	t.Print();
	t.Remove(80);
	t.Print();

	t.Remove(30);
	t.Print();
}