#include <iostream>
using namespace std;

enum Message { on, off, ack };
Message messageArray[10] = { on,off,off,ack,ack,ack,ack,on,off,off };

class Context;

class State {
protected:
	Context* context = nullptr;
public:
	void setContext(Context* context) {
		this->context = context;
	}
	virtual ~State() {}
	virtual void action(const int&) = 0;
};

class Context {
private:
	State* state;
public:
	Context(State* initState) : state(nullptr) {
		this->setState(initState);
	}
	~Context() {
		delete state;
	}
	void setState(State* state) {
		if (this->state != nullptr)
			delete this->state;
		this->state = state;
		this->state->setContext(this);
	}
	void request(const int& index) {
		this->state->action(index);
	}
};

class StateA : public State {
public:
	void action(const int& index) override;
};

class StateB : public State {
public:
	void action(const int& index) override;
};

class StateC : public State {
public:
	void action(const int& index) override;
};

void StateA::action(const int& index) {
	if (messageArray[index] == on) {
		cout << "A, on ==> A" << endl;
	}
	else if (messageArray[index] == off) {
		cout << "A, off ==> B" << endl;
		this->context->setState(new StateB);
	}
	else if (messageArray[index] == ack) {
		cout << "A, ack ==> C" << endl;
		this->context->setState(new StateC);
	}
}

void StateB::action(const int& index) {
	if (messageArray[index] == on) {
		cout << "undefined combo" << endl;
	}
	else if (messageArray[index] == off) {
		cout << "B, off ==> A" << endl;
		this->context->setState(new StateA);
	}
	else if (messageArray[index] == ack) {
		cout << "B, ack ==> C" << endl;
		this->context->setState(new StateC);
	}
}

void StateC::action(const int& index) {
	if (messageArray[index] == on) {
		cout << "undefined combo" << endl;
	}
	else if (messageArray[index] == off) {
		cout << "undefined combo" << endl;
	}
	else if (messageArray[index] == ack) {
		cout << "C, ack ==> B" << endl;
		this->context->setState(new StateB);
	}
}

int main() {
	
	Context *context = new Context(new StateB);
	for (int index = 0; index < 10; index++) {
		context->request(index);
	}

	delete context;

	return 0;
}
