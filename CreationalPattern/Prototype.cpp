#include <iostream>
#include <string>
using namespace std;

class FederalFraudvillian {
protected:
	string party;

public:
	FederalFraudvillian(string pp = "Democrat") : party(pp) {}
	virtual ~FederalFraudvillian() {}
	virtual void partyLine() = 0;
	virtual FederalFraudvillian* clone() const = 0;

};

class President : public FederalFraudvillian {
public:
	void partyLine() {
		cout << party << ": speak no evil" << endl;
	}
	FederalFraudvillian* clone() const override {
		return new President(*this);
	}
};

class AttorneyGeneral : public FederalFraudvillian {
public:
	void partyLine() { 
		cout << party << ": see no evil" << endl; 
	}
	FederalFraudvillian* clone() const override {
		return new AttorneyGeneral(*this);
	}
};

class MinorityPartyCongressPerson : public FederalFraudvillian {
public:
	void partyLine() {
		cout << party << ": hear no evil" << endl; 
	}
	FederalFraudvillian* clone() const override {
		return new MinorityPartyCongressPerson(*this);
	}
};

int main() {
	FederalFraudvillian* moralMisfits[10];
	President* P = new President;
	AttorneyGeneral* AG = new AttorneyGeneral;
	MinorityPartyCongressPerson* MPCP = new MinorityPartyCongressPerson;
	int in, total = 0;

	cout << "President(1) AG(2) MPCP(3) Go(0): ";
	cin >> in;
	
	while (in) {
		if (in == 1)	  moralMisfits[total++] = P->clone();
		else if (in == 2) moralMisfits[total++] = AG->clone();
		else			  moralMisfits[total++] = MPCP->clone();
		cout << "President(1) AG(2) MPCP(3) Go(0): ";
		cin >> in;
	}
	
	for (int i = 0; i < total; i++) {
		moralMisfits[i]->partyLine();
	}
	for (int i = 0; i < total; i++) {
		delete moralMisfits[i];
	}

	delete P;
	delete AG;
	delete MPCP;

	return 0;
}

// no compiler directive -
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 2
// President(1) AG(2) MPCP(3) Go(0): 3
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 0
// Republican: speak no evil
// Republican: see no evil
// Republican: hear no evil
// Republican: speak no evil
// -DDEMOCRAT -
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 2
// President(1) AG(2) MPCP(3) Go(0): 3
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 0
// Democrat: speak no evil
// Democrat: see no evil
// Democrat: hear no evil
// Democrat: speak no evil