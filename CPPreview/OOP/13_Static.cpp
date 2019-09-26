// 1. Intro
// 2. Static variable for a function call
// 3. Static variable 
// 4. Static method
// 5. Non-member function in the same namespace
// 6. Class as a template parameter
// 7. 'Static constructor' in C++


// 1. Intro ----------------------------------------------------------------------
/* Statically allocated means that the variable is allocated at compile-time, not at run-time. 
Once per program. In C, this can be a global variable at the file scope or a static variable in 
a function. Space for them will be allocated when the binary is loaded into memory. Variables on 
the stack (i.e., local variables in functions that do not have the static keyword) are allocated 
when the function is called */

static int x; //internal linkage
              //non-static storage - each translation unit will have its own copy of x
              //NOT A TRUE GLOBAL!

int y;        //static storage duration (can be used with extern)
              //actual global
              //external linkage
struct X {
   static int x;     //static storage duration - shared between class instances 
};

void foo() {
   static int x;     //static storage duration - shared between calls
}


// 2. Static variable for a function call ----------------------------------------
void func() {
    static int x = 0; 
    /* x is initialized only once across five calls of func() and the variable will get incremented 
       five times after these calls. The final value of x will be 5. */
  
    x++;
    printf("%d\n", x); 
}

int main() 
{ 
    func(); // prints 1
    func(); // prints 2
    func(); // prints 3
    func(); // prints 4
    func(); // prints 5
    
    std::cin.get();
}

// 3. Static variable ------------------------------------------------------------
class A {                                   // In a header file 
private:      
  static const string RECTANGLE;
};

const string A::RECTANGLE = "rectangle";    // In one of the implementation files

A a, b; &a.RECTANGLE == &b.RECTANGLE == &A::RECTANGLE;   // address of all three names above is the same


class A {                                   // Starting from C++17
private:      
  inline static const string RECTANGLE = "rectangle";
};


// 4. Static method --------------------------------------------------------------
// There is no "static class" in C++. The nearest concept would be a class with only static methods

class BitParser {                                       // BitParser.h
 public:
  static bool getBitAt(int buffer, int bitIndex);
 private:
  BitParser() {}          // Disallow creating an instance of this object
};

bool BitParser::getBitAt(int buffer, int bitIndex) {    // BitParser.cpp
  bool isBitSet = false;
  // .. determine if bit is set
  return isBitSet;
}


// 5. Non-member function in the same namespace ----------------------------------
// When there's no need for an object don't use a class

namespace BitParser {                                   // BitParser.h
    bool getBitAt(int buffer, int bitIndex);
}

namespace BitParser {                                   // BitParser.cpp
    bool getBitAt(int buffer, int bitIndex) {
        //get the bit :)
    }
}


// 6. Class as a template parameter ----------------------------------------------
/* When are classes static methods are actually better than namespaces with non-member functions?
When you need to group together functions and feed that group to a template:  */

namespace alpha {
   void foo() ;
   void bar() ;
}

struct Beta {
   static void foo() ;
   static void bar() ;
};

template <typename T>
struct Gamma {
   void foobar() {
      T::foo() ;
      T::bar() ;
   }
};

Gamma<alpha> ga ; // compilation error
Gamma<Beta> gb ;  // ok
gb.foobar() ;     // ok !!!


// 7. 'Static constructor' in C++ ------------------------------------------------
// WAY 1: write a separate ordinary class to hold the static data and then make a static instance of that ordinary class
class StaticStuff {
     std::vector<char> letters_;
public:
     StaticStuff() {
         for (char c = 'a'; c <= 'z'; c++)
             letters_.push_back(c);
     }
};

class Elsewhere{
    static StaticStuff staticStuff;         // constructor runs once, single instance
};

// WAY 2:
class MyClass {
    public:
        static vector<char> a;

        static class _init {
          public:
            _init() { for(char i='a'; i<='z'; i++) a.push_back(i); }
        } _initializer;
};

vector<char> MyClass::a;                // in the .cpp
MyClass::_init MyClass::_initializer;


// 1. Static variable ------------------------------------------------------------
// 1. Static variable ------------------------------------------------------------

