// Vitrual inheritance to solve DIAMOND PROBLEM

#include<iostream>
using namespace std;
class A {
public:
    A()                { cout << "A::A() "; }
    A(int x) : m_x(x)  { cout << "A::A(" << x << ") "; }
    int getX() const   { return m_x; }
private:
    int m_x = 42;
};

class B : public A {
public:
    B(int x):A(x)   { cout << "B::B(" << x << ") "; }
};

class C : public A {
public:
    C(int x):A(x) { cout << "C::C(" << x << ") "; }
};

class D : public C, public B  {
public:
    D(int x, int y): C(x), B(y)   {
        cout << "D::D(" << x << ", " << y << ") "; }
};

int main()  {
    cout << "Create b(2): " << endl;
    B b(2); cout << endl << endl;

    cout << "Create c(3): " << endl;
    C c(3); cout << endl << endl;

    cout << "Create d(2,3): " << endl;
    D d(2, 3); cout << endl << endl;

    //cout << "d.getX() = " << d.getX() << endl;            // error: request for member 'getX' is ambiguous
    //cout << "d.A::getX() = " << d.A::getX() << endl;      // error: 'A' is an ambiguous base of 'D'

    cout << "d.B::getX() = " << d.B::getX() << endl;
    cout << "d.C::getX() = " << d.C::getX() << endl;
}

/*
Lets go through output. Executing B b(2); creates A(2) as expected, same for C c(3);:

Create b(2): 
A::A(2) B::B(2) 

Create c(3): 
A::A(3) C::C(3) 
D d(2, 3); needs both B and C, each of them creating its own A, so we have double A in d:

Create d(2,3): 
A::A(2) C::C(2) A::A(3) B::B(3) D::D(2, 3) 

Still it's possible to call methods directly for chosen parent class:
d.B::getX() = 3
d.C::getX() = 2
*/

// Now lets add virtual inheritance. Using same code sample with the following changes:

class B : virtual public A
...
class C : virtual public A
...
cout << "d.getX() = " << d.getX() << endl;          //uncommented
cout << "d.A::getX() = " << d.A::getX() << endl;    //uncommented
...

/*
Lets jump to creation of d:

Create d(2,3): 
A::A() C::C(2) B::B(3) D::D(2, 3) 
You can see, A is created with default constructor ignoring parameters passed from constructors of B and C. As ambiguity is gone, all calls to getX() return the same value:

d.getX() = 42
d.A::getX() = 42
d.B::getX() = 42
d.C::getX() = 42
But what if we want to call parametrized constructor for A? It can be done by explicitly calling it from constructor of D:

D(int x, int y, int z): A(x), C(y), B(z)
*/
