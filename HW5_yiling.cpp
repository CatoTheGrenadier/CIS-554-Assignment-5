//HW5 Yi Ling
// SUID: 9254508221  NetID:yiling



//HW5 Due: 11:59pm, Wednesday, Nov. 8
/*

For the class triangle, implement construcotr, copy constructor,
move constructor, copy assignment,
move assignment, destructor, FirtThreeRow.
Also, implement operator<< to allow cout of triangle object.
See the sample screehshot for output requirement

Only smart pointers are allowed.

No raw pointers allowed.
No extra helper functions allowed.
No external structures allowed.

*/

#include <iostream>
#include <memory>
using namespace std;

class node {
public:
	int value;
	shared_ptr<node> Lchild;
	shared_ptr<node> Rchild;
	weak_ptr<node> next;
	node(int i) : value(i) {}
	node() {  }

};

class triangle {
public:
	shared_ptr<node> top;
	triangle(int n, int m);//constructor, n levels with node being random values in 0 ... m-1
	triangle() { cout << "Default Constructor\n\n"; }
	triangle(const triangle& t);//copy constructor
	void operator=(const triangle& t); //copy assignment
	~triangle();//destructor
	triangle(triangle&& t);//move constructor
	void operator=(triangle&& t);//move assignment
	triangle FirstThreeRow();//return a triagle which is the first three rows of *this.
	//Assume the triangle *this have three or more than three rows.
};

triangle::triangle(int n, int m) { //constructor
	top = make_shared<node>(rand() % m);
	weak_ptr<node> next_in_line{ top };
	weak_ptr<node> next_tail{ top };
	weak_ptr<node> next_head{ top };
	for (int level = 1; level < n; level++) {
		for (int i = 0; i < level; i++) {
			if (i == 0) {
				next_in_line.lock()->Lchild = make_shared<node>(rand() % m);
				next_in_line.lock()->Rchild = make_shared<node>(rand() % m);
				next_in_line.lock()->Lchild->next = next_in_line.lock()->Rchild;
				next_head = next_in_line.lock()->Lchild;
				next_tail = next_in_line.lock()->Rchild;
			}else {
				next_in_line.lock()->Lchild = next_tail.lock();
				next_in_line.lock()->Rchild = make_shared<node>(rand() % m);
				next_tail.lock()->next = next_in_line.lock()->Lchild;
				next_in_line.lock()->Lchild->next = next_in_line.lock()->Rchild;
				next_tail = next_in_line.lock()->Rchild;
			}
			if (i != level - 1) {
				next_in_line = next_in_line.lock()->next;
			}
		}
		next_in_line.lock()->next = next_head;
		next_in_line = next_head;
	}
	next_tail.lock()->next = top;
	cout << "Constructor\n" << endl;
}

triangle::triangle(const triangle& t) :triangle{ 1,10 } { //copy constructor
	cout << "Copy Constructor\n" << endl;
	this->~triangle();
	top = make_shared<node>(t.top->value);
	weak_ptr<node> next_in_line_1{ t.top->next };
	weak_ptr<node> next_in_line_2{ top };
	weak_ptr<node> next_tail{ top };
	weak_ptr<node> next_head{ top };
	int level{ 1 };
	while (1) {
		for (int i = 0; i < level; i++) {
			if (i == 0) {
				next_in_line_2.lock()->Lchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_in_line_2.lock()->Rchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_in_line_2.lock()->Lchild->next = next_in_line_2.lock()->Rchild;
				next_head = next_in_line_2.lock()->Lchild;
				next_tail = next_in_line_2.lock()->Rchild;
			}
			else {
				next_in_line_2.lock()->Lchild = next_tail.lock();
				next_in_line_2.lock()->Rchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_tail.lock()->next = next_in_line_2.lock()->Lchild;
				next_in_line_2.lock()->Lchild->next = next_in_line_2.lock()->Rchild;
				next_tail = next_in_line_2.lock()->Rchild;
			}
			if (i != level - 1) {
				next_in_line_2 = next_in_line_2.lock()->next;
			}
		}
		next_in_line_2.lock()->next = next_head;
		next_in_line_2 = next_head;
		if (next_in_line_1.lock() == t.top) {
			break;
		}
		level += 1;
	}
	next_tail.lock()->next = top;
}

void triangle::operator=(const triangle& t) {  //copy assignment
	triangle temporary{ t };
	cout << "Copy Assignment\n" << endl;
	top.reset();
	top = make_shared<node>(temporary.top->value);
	weak_ptr<node> next_in_line_1{ temporary.top->next };
	weak_ptr<node> next_in_line_2{ top };
	weak_ptr<node> next_tail{ top };
	weak_ptr<node> next_head{ top };
	int level{ 1 };
	while (1) {
		for (int i = 0; i < level; i++) {
			if (i == 0) {
				next_in_line_2.lock()->Lchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_in_line_2.lock()->Rchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_in_line_2.lock()->Lchild->next = next_in_line_2.lock()->Rchild;
				next_head = next_in_line_2.lock()->Lchild;
				next_tail = next_in_line_2.lock()->Rchild;
			}
			else {
				next_in_line_2.lock()->Lchild = next_tail.lock();
				next_in_line_2.lock()->Rchild = make_shared<node>(next_in_line_1.lock()->value);
				next_in_line_1 = next_in_line_1.lock()->next;
				next_tail.lock()->next = next_in_line_2.lock()->Lchild;
				next_in_line_2.lock()->Lchild->next = next_in_line_2.lock()->Rchild;
				next_tail = next_in_line_2.lock()->Rchild;
			}
			if (i != level - 1) {
				next_in_line_2 = next_in_line_2.lock()->next;
			}
		}
		next_in_line_2.lock()->next = next_head;
		next_in_line_2 = next_head;
		if (next_in_line_1.lock() == temporary.top) {
			break;
		}
		level += 1;
	}
	next_tail.lock()->next = top;
	return;
}

triangle::~triangle() { //destructor
	top.reset();
	cout << "Destructor\n" << endl;
}

triangle::triangle(triangle&& t) { //move constructor
	top = t.top;
	t.top.reset();
	cout << "Move Constructor\n" << endl;
}

void triangle::operator=(triangle&& t) { //move assignment
	top.reset();
	top = t.top;
	t.top.reset();
	cout << "Move Assignment\n" << endl;
	return;
}

triangle triangle::FirstThreeRow() { //return a triagle which is the first three rows of *this.
	triangle new_triangle(*this);
	
	weak_ptr<node> loop_2{ new_triangle.top };
	for (int i = 0; i < 3; i++) {
		loop_2 = loop_2.lock()->next;
	}
	for (int i = 0; i < 3; i++) {
		loop_2.lock()->Lchild.reset();
		loop_2.lock()->Rchild.reset();
		if (i != 2) { 
			loop_2 = loop_2.lock()->next; 
		}
	}
	loop_2.lock()->next = new_triangle.top;
	cout << "FirstThreeRows\n" << endl;
	return new_triangle;
}

ostream& operator<<(ostream& str, const triangle& c) {
	int level{ 1 };
	weak_ptr<node> next_in_line{ c.top };
	while (1) {
		for (int i = 0; i < level; i++) {
			str << next_in_line.lock()->value << " ";
			next_in_line = next_in_line.lock()->next;
		}
		str << "\n";
		if (next_in_line.lock() == c.top) {
			break;
		}
		level += 1;
	}
	return str;
}

int main() {

	triangle T1(7, 10);
	cout << T1 << "\n\n";
	
	triangle T2{ T1 };
	cout << T2 << "\n\n";
	triangle T3;
	T3 = T2;
	cout << T3 << "\n\n";

	T3 = T2.FirstThreeRow();
	cout << T3 << "\n\n";


	return 0;
}