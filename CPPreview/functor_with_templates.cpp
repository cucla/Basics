#include "stdafx.h"
#include "iostream"
#include <vector>
#include <functional>


/* [ 1 ]
 * Return the max value in a vector v
 * Comparable objects must provide operator< and operator=
 */
template <typename Comparable>
const Comparable & findMax(const std::vector<Comparable> & v) {
	int maxIndex = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[maxIndex] < v[i])
			maxIndex = i;
	}
	return v[maxIndex];
}

/* [ 2 ]
 * If we have array of pointers to objects, they no longer know how to compare themselves
 * Pass functor along with the vector/array
 * Here, 'IsLessComparator' works with int
 * Object class type has operator=
 */
template <typename Object, typename Comparator>
const Object & findMax(const std::vector<Object> & v, Comparator cmp) {
	int maxIndex = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (cmp.isLessThan(v[maxIndex], v[i]))
			maxIndex = i;
	}
	return v[maxIndex];
}

class IsLessComparator {
public:
	bool isLessThan(const int & lhs, const int & rhs) const{
		return (lhs - rhs) < 0;
	}
};

// works as 'cmp(v[maxIndex], v[i])' in 'findmax'
class IsLessComparator2 {
public:
	bool operator()(const int & lhs, const int & rhs) const {
		return (lhs - rhs) < 0;
	}
};

/--------------------------------------------------------------------------------
/* [ 3 ]
 * Generic 'findMax', using default ordering via std::less
 */
template <typename Object, typename Comparator>
const Object & findMax(const std::vector<Object> & v, Comparator cmp) {
	int maxIndex = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (cmp(v[maxIndex], v[i]))
			maxIndex = i;
	}
	return v[maxIndex];
}

template <typename Object>
const Object & findMax(const std::vector<Object> & v) {
	return findMax(v, std::less<Object>{ });
}
/--------------------------------------------------------------------------------


int main()
{
	std::cout << findMax<int>({ 33, 4, 12 }) << std::endl;                        //[1]
	std::cout << findMax<int>({ 33, 4, 12 }, IsLessComparator{ }) << std::endl;   //[2]
	//---------------------------------------------------------------------------------
	std::cout << findMax<int>({ 33, 4, 12 }) << std::endl;                        //[3]


	std::cin.get();
}

