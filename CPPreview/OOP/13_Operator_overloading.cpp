/* To overload a function means to provide other functions with the same name but different parameter types. 
 * Operators can also be overloaded. Many operators have a corresponding function that can be overloaded 
 * called operator??, where ?? is the operator itself.
 *
 * There are two ways to overload a binary operator like << (binary because it takes two operands, one on the 
 * left side and one on the right, left << right). One is to make it a member of the type of left and give it 
 * a single parameter of the type of right. The other is to make it a non-member function with two parameters, 
 * one the type of left and the other the type of right.
 */
 
std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    // Insert everything you want into `os` : os << ...
    return os;
}
Movie m;
cout << m; 
