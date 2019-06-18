// In a header file 
class A {   
private:      
  static const string RECTANGLE;
};

// In one of the implementation files
const string A::RECTANGLE = "rectangle";

// Starting from C++17
class A {   
private:      
  inline static const string RECTANGLE = "rectangle";
};
