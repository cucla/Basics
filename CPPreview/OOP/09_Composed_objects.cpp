#include "stdafx.h"
#include "iostream"


using namespace std;

class Battery {
public:
	Battery() { cout << "Constructor: Including Battery\n"; }
	~Battery() { cout << "Destructor : Removing Battery\n"; }
};

class Sim {
public:
	Sim() { cout << "Constructor: Including Sim\n"; }
	~Sim() { cout << "Destructor : Removing Sim\n"; }
};


class Mobile {
private:
	Battery _battery;    // composed object
	Sim _sim;            // composed object
public:
	Mobile() { cout << "Constructor: Mobile is assembled and ready to use!!!\n"; }
	~Mobile() { cout << "Destructor : Dissembling Mobile\n"; }
};


int main() {
	Mobile * device = new Mobile;
	delete device;

	std::cin.get();
}


Constructor: Including Battery
Constructor: Including Sim
Constructor: Mobile is assembled and ready to use!!!
Destructor : Dissembling Mobile
Destructor : Removing Sim
Destructor : Removing Battery


