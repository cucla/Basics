/* What is the copy-and-swap idiom?
 * A way of implementing the assignment operator in terms of a swap function
 */

#include <algorithm> 
#include <cstddef> 

class dumb_array {
public:
    dumb_array(std::size_t size = 0)                              // (default) constructor
        : mSize(size)
        , mArray(mSize ? new int[mSize]() : nullptr) {}

    dumb_array(const dumb_array& other)                           // copy-constructor
        : mSize(other.mSize)
        , mArray(mSize ? new int[mSize] : nullptr),
    { std::copy(other.mArray, other.mArray + mSize, mArray); }
    
    //dumb_array& operator=(const dumb_array& other) {
        //dumb_array temp(other);
        //swap(*this, temp);
        //return *this;
    //}
    
    dumb_array& operator=(dumb_array other) {   // the parameter argument is taken by-value
         swap(*this, other); 
         return *this;
    }
    
    dumb_array(dumb_array&& other)                                // move constructor
        : dumb_array()    // initialize via default constructor, C++11 only
    { swap(*this, other); }

    ~dumb_array() { delete [] mArray; }                           // destructor

    /* We might be tempted to use std::swap instead of providing our own, but this would be impossible; 
    std::swap uses the copy-constructor and copy-assignment operator within its implementation, 
    and we'd ultimately be trying to define the assignment operator in terms of itself! */
    friend void swap(dumb_array& first, dumb_array& second) {     // friend function swap
        using std::swap;
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }
private:
    std::size_t mSize;
    int* mArray;
};


