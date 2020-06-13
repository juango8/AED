#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode {
	CBinNode(int _v) {
		value = _v;
		nodes[0] = nodes[1] = 0;
	}

	int value;
	CBinNode *nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree {
public:
	CBinTree();

	virtual ~CBinTree();

	bool Find(int x, CBinNode **&p);

	bool Insert(int x);

	bool Remove(int x);

	CBinNode **Rep(CBinNode **p);

	void InOrder(CBinNode *n);

	void Print();

	virtual bool criteria(int, int);
private:
	CBinNode *m_root;
};

CBinTree::CBinTree() { m_root = 0; }

CBinTree::~CBinTree() {
	// ?
}

bool CBinTree::Find(int x, CBinNode **&p) {
	for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[criteria((*p)->value, x)]));
	return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
	CBinNode **p;
	if (Find(x, p)) return 0;
	*p = new CBinNode(x);
	return 0;
}

bool CBinTree::Remove(int x) {
	CBinNode **p;
	if (!Find(x, p)) return 0;
	if ((*p)->nodes[0] && (*p)->nodes[1]) {
		CBinNode **q = Rep(p);
		(*p)->value = (*q)->value;
		p = q;
	}
	CBinNode *t = *p;
	*p = (*p)->nodes[!(*p)->nodes[0]];
	delete t;
	return 0;
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

bool CBinTree::criteria(int, int) {
	return false;
}

class TreeUpward : public CBinTree {
	bool criteria(int a, int b) {
		return a < b;
	}
};
class TreeDownward : public CBinTree {
	bool criteria(int a, int b) {
		return a > b;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	TreeUpward treeUpward;
	TreeDownward treeDownward;

	treeUpward.Insert(50);
	treeUpward.Insert(30);
	treeUpward.Insert(60);
	treeUpward.Insert(80);
	treeUpward.Insert(55);
	treeUpward.Insert(11);
	treeUpward.Insert(33);
	treeUpward.Insert(5);
	treeUpward.Insert(14);
	treeUpward.Insert(31);
	treeUpward.Insert(48);
	treeUpward.Print();

	treeUpward.Remove(31);
	treeUpward.Print(); //case 0
	treeUpward.Remove(14);
	treeUpward.Print(); //case 0

	treeUpward.Remove(11);
	treeUpward.Print(); //case 1, left
	treeUpward.Remove(33);
	treeUpward.Print(); //case 1, right

	treeUpward.Remove(50);
	treeUpward.Print(); //case 2

	treeUpward.Remove(60);
	treeUpward.Print();
	treeUpward.Remove(48);
	treeUpward.Print();
	treeUpward.Remove(55);
	treeUpward.Print();
	treeUpward.Remove(5);
	treeUpward.Print();
	treeUpward.Remove(80);
	treeUpward.Print();

	treeUpward.Remove(30);
	treeUpward.Print();

	treeDownward.Insert(50);
	treeDownward.Insert(30);
	treeDownward.Insert(60);
	treeDownward.Insert(80);
	treeDownward.Insert(55);
	treeDownward.Insert(11);
	treeDownward.Insert(33);
	treeDownward.Insert(5);
	treeDownward.Insert(14);
	treeDownward.Insert(31);
	treeDownward.Insert(48);
	treeDownward.Print();

	treeDownward.Remove(31);
	treeDownward.Print(); //case 0
	treeDownward.Remove(14);
	treeDownward.Print(); //case 0

	treeDownward.Remove(11);
	treeDownward.Print(); //case 1, left
	treeDownward.Remove(33);
	treeDownward.Print(); //case 1, right

	treeDownward.Remove(50);
	treeDownward.Print(); //case 2

	treeDownward.Remove(60);
	treeDownward.Print();
	treeDownward.Remove(48);
	treeDownward.Print();
	treeDownward.Remove(55);
	treeDownward.Print();
	treeDownward.Remove(5);
	treeDownward.Print();
	treeDownward.Remove(80);
	treeDownward.Print();

	treeDownward.Remove(30);
	treeDownward.Print();
}