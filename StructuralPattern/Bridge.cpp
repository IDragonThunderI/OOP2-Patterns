#include <iostream>
using namespace std;

class Implementation {
public:
	virtual ~Implementation() {}
	virtual void push(int) = 0;
	virtual int pop() = 0;
	virtual int isEmpty() = 0;
	virtual int isFull() = 0;
};

class ArrayImplementation : public Implementation {
private:
	int* _array;
	int _sp;
	int _size;

public:
	ArrayImplementation(int size = 10) {
		_array = new int[size];
		_size = size;
		_sp = 0;
	}
	~ArrayImplementation() {
		delete _array;
	}
	void push(int val) override {
		if (!isFull())
			_array[_sp++] = val;
	}
	int pop() override {
		if (isEmpty()) return 0;
		else return _array[--_sp];
	}
	int isEmpty() override {
		return _sp == 0 ? 1 : 0;
	}
	int isFull() override { 
		return _sp == _size ? 1 : 0; 
	}
};

class Node {
private:
	int _value;
	Node* _next;

public:
	Node(int val, Node* next) {
		_value = val;
		_next = next;
	}
	int getValue() {
		return _value;
	}
	Node* getNext() {
		return _next;
	}
};

class ListImplementation : public Implementation {
private:
	Node* _head;

public:
	ListImplementation() {
		_head = NULL;
	}
	~ListImplementation() {
		Node* current, * previous;
		current = _head;
		while (current) {
			previous = current;
			current = current->getNext();
			delete previous;
		}
	}
	void push(int val) override {
		Node* temp = new Node(val, _head);
		_head = temp;
	}
	int pop() override {
		if (isEmpty()) return 0;
		Node* temp = _head;
		int val = _head->getValue();
		_head = _head->getNext();
		delete temp;
		return val;
	}
	int isEmpty() override {
		return _head ? 0 : 1;
	}
	int isFull() override {
		return 0;
	}
};

class Stack {
protected:
	Implementation* implementation;

public:
	Stack(Implementation* implement) : implementation(implement) {}
	~Stack() {
		delete implementation;
	}
	void push(int val) {
		implementation->push(val);
	}
	int pop() {
		return implementation->pop();
	}
	int isEmpty() {
		return implementation->isEmpty();
	}
	int isFull() {
		return implementation->isFull();
	}
};

int main() {
	Stack* stack1 = new Stack(new ArrayImplementation);
	Stack* stack2 = new Stack(new ListImplementation);

	for (int i = 1; i < 16; i++) {
		stack1->push(i);
		stack2->push(i);
	}

	cout << "Array stack: ";
	for (int i = 1; i < 18; i++) {
		cout << stack1->pop() << " ";
	}
	cout << endl;

	cout << "List stack: ";
	for (int i = 1; i < 18; i++) {
		cout << stack2->pop() << " ";
	}
	cout << endl;

	delete stack1;
	delete stack2;

	return 0;
}

// Array stack: 10 9 8 7 6 5 4 3 2 1 0 0 0 0 0 0 0
// List stack: 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 0
