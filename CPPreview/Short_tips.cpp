// FIX:      https://www.onixs.biz/fix-dictionary/4.2/app_d.html 
// Memory:   https://isocpp.org/wiki/faq

/* http://www.gotw.ca/gotw/
 *
 * 1. Array Sum / Vector sum
 * 2. Count elements == to my own parameter 'myMax' (lambda with count_if)
 * 3. Remove non-consecutive duplicates from Container
 * 4. Int to char/char to int
 * 5. Search sequence for the first number, smaller than a given value
 * 6. Array of functions, function pointer vector
 * 7. std::find_if vs std::find
 * 8. trim spaces in a string using std::find_if()
 * 9. MAP: select by value + custom comparator
 * 10. decltype() to deduce the type for std::find_if()
 * 11. Find element, that satisfies v[i] <= x < v[i + 1], using std::adjacent_find()
 * 12. Functor + std::for_each
 * 13. std::transform with std::back_inserter
 * 14. Rotate vector to the right 
 * 15. Intersection of two arrays
 * 16. Check if a string is a palindrome
 * 17. Split string into words (by whitespace)
 * 18. Negate vector
 * 19. Set both elements to 0 in binary array
 */
 
//--------------------------------------------------------------------------------------------
int * pia = new int[10];
int * pia = new int[10]();
int * pia = new int[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// 1. Array Sum-------------------------------------------------------------------------------
int myArr[] = { 1, 10, 100, 1000 };

int sum = 0;
std::for_each(std::begin(myArr), std::end(myArr), [&sum](int a) { return sum += a; });
int sum2 = std::accumulate(std::begin(myArr), std::end(myArr), 0);

// 1. VectorSum-------------------------------------------------------------------------------
std::vector<int> myVector;
for (int i = 1; i <= 5; i++) myVector.push_back(i);

int sum = 0;
std::for_each(myVector.begin(), myVector.end(), [&sum](int a) { return sum += a; });
int sum2 = std::accumulate(myVector.begin(), myVector.end(), 0);  //0.0f for floats

// 2. Count elements == to my own parameter 'myMax' (lambda with count_if)--------------------
std::vector<int> ar({ 3, 2, 1, 3 });
auto myMax = *std::max_element(ar.begin(), ar.end());
auto myCount = std::count_if(ar.begin(), ar.end(), [myMax](int i) { return i == myMax; });

// 3. Remove non-consecutive duplicates from Container----------------------------------------
	std::string s = "wwxwwm";
	std::set<char> seen;
	s.erase(std::remove_if(s.begin(), s.end(), [&seen](char c) { return !seen.insert(c).second; }), s.end());
	std::cout << s;   // "wxm"

// 4. Int to char/char to int-----------------------------------------------------------------
	
  // int to char
	int i = 7;	
	char ch = i + '0';                            // '7'

	// char to int, saving the order
	char f = 'f', g = 'g';
	int fi = f - 'a', gi = g - 'a';
	std::cout << fi << " " << gi << std::endl;   // 5  6

// 5. Search sequence for the first number, smaller than a given value------------------------
std::vector<int> scores({ 100, 50, 40, 20, 10 });
std::vector<int> alice({ 5, 25, 50, 120 });

auto locateRanking = [](const auto & _scores, int _newScore) {
	auto itr = std::lower_bound(std::begin(_scores), std::end(_scores), _newScore, std::greater<int>());
	return std::distance(std::begin(_scores), itr) + 1;
};
for (auto newScore : alice) {
	std::cout << locateRanking(scores, newScore) << std::endl;
}

// 6. Array of functions + function pointer vector--------------------------------------------
typedef int(*FunctionPrt)(int);

int utopianTree(int n) {
	int initialHeight = 1;

	FunctionPrt functions[] = {
		[](int initialHeight) { return initialHeight * 2; },
		[](int initialHeight) { return initialHeight + 1; }
	};

	for (int cycles = 0, i = 0; cycles < n; i = (i + 1) % 2, ++cycles) {
		initialHeight = functions[i](initialHeight);
	}
	return initialHeight;
}
// -------------------------------------------------------------------------------------------
std::vector<int(*)(const char*)> processors;
processors.push_back(std::atoi);
processors.push_back(reinterpret_cast<int(*)(const char*)>(std::strlen));

const char data[] = "1.23";

for (std::vector<int(*)(const char*)>::iterator it = processors.begin();
	it != processors.end(); ++it)
	std::cout << (*it)(data) << std::endl;

// 7. std::find_if vs std::find---------------------------------------------------------------
struct Interval {
	Interval(int a, int b) : start(a), end(b) {}
	int start;
	int end;
	bool operator==(const Interval & rhs) const { return start == rhs.start; }  // for std::find
};

int main() { 
	std::vector<Interval> iv{ { 2,1 },{ 3,0 },{ 4,1 },{ 5,1 } };
	Interval toFind{ 4,1 };

	auto it = std::find_if(iv.begin(), iv.end(), [&toFind](const Interval & k) {return k.start == toFind.start; });
	
        // can use std::find directly with "toFind" with appropriate == overload:
	auto it = std::find(iv.begin(), iv.end(), toFind); }

// 8. trim spaces in a string using std::find_if()--------------------------------------------
std::string s{ "      with spaces    " };
s.erase( s.begin(), std::find_if(s.begin(), s.end(), [](char c) { return !isspace(c); } ));        // left trim
s.erase(std::find_if(s.rbegin(), s.rend(), [](char c) { return !isspace(c); }).base(), s.end());   // right trim

// 9. MAP: select by value + custom comparator------------------------------------------------
// select 'first' item in a map that equals to some VALUE, not KEY
template <typename Key, typename Value>
struct check_x {
	check_x(int x) : x_(x) {}
	bool operator()(const std::pair<Key, Value> & v) const {
		return v.second == x_;
	}
private:
	int x_;
};

// custom comparator for 'mymap2' (in descending order by KEY)
template <typename Key>
struct Compare {
	bool operator()(const Key & lhs, const Key & rhs) const {
		return lhs > rhs;
	}
};

int main() 
{ 
	std::map<char, int> mymap{ {'c',1},{'d',2},{'e',2},{'a',3},{'b',1} };
	auto r = std::find_if(mymap.begin(), mymap.end(), check_x<char, int>(2));
	std::cout << r->first << " => " << r->second << '\n';

	std::map<char, int, Compare<char>> mymap2{ { 'c',1 },{ 'd',2 },{ 'e',2 },{ 'a',3 },{ 'b',1 } };
	for (std::map<char, int>::iterator it = mymap2.begin(); it != mymap2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

// 10. decltype() to deduce the type for std::find_if()---------------------------------------
int num = 2;
std::vector<std::pair<int, std::string>> v{ {1, "one"}, {2, "two"}, {3, "three"} };
auto r = std::find_if(v.begin(), v.end(), [&](const decltype(*v.begin()) & el) { return el.first == num; });

std::cout << r->first << " " << r->second << std::endl;

// 11. Find element, that satisfies v[i] <= x < v[i + 1]--------------------------------------
const std::vector<double> v{ 1.5, 3.1, 12.88, 32.4 };

const auto x = 13.0;
auto it = std::adjacent_find(v.begin(), v.end(), [x](double lhs, double rhs) { return lhs <= x && x < rhs; });
if (it != v.end()) {
	std::cout << *it << " " << *(it + 1) << std::endl;
}
// OUTPUT: 12.88, 32.4

// 12. Functor + std::for_each----------------------------------------------------------------
/* std::for_each accepts the functor by value, that means it modifies a local copy. 
The assignment gets that local copy back so you can actually see the modified version.

This is important as your functor has mutable state that you are interested in, 
in particular evenodd.even_sum and evenodd.odd_sum.
*/
struct EvenOdd {
	int evens = 0;
	int odds = 0;
	void operator()(int x) {
		if (x % 2 == 0) evens += x;
		else odds += x;
	} };

int main() 
{ 
	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	EvenOdd functorObj;
	functorObj = std::for_each(v.begin(), v.end(), functorObj);

	std::cout << functorObj.evens << std::endl;  // 30
	std::cout << functorObj.odds << std::endl;   // 25
}
//--------------------------------------------------------------------------------------------
class CalculateAverage {
private:
   std::size_t num;
   double sum;
public:    
   CalculateAverage() : num (0) , sum (0) { }
   void operator()(int elem) {
      num++;
      sum += elem; }
   operator double () const { return sum / num; }   // conversion operator
};

int main()
{
    vector<int> values { 1,2,3,4,5 };
    int average = std::for_each(values.begin(), values.end(), CalculateAverage());   // OUTPUT: 3
}

// 13. std::transform with std::back_inserter-------------------------------------------------
std::vector<std::string> names = {"hi", "test", "foo"};
std::vector<std::size_t> name_sizes;

std::transform(names.begin(), names.end(), std::back_inserter(name_sizes), 
	       [](const std::string & name) { return name.size(); });

// 14. Rotate vector to the right-------------------------------------------------------------
	std::vector<int> nums{ 1, 2, 3, 4, 5, 6, 7 };
	std::rotate(nums.rbegin(), nums.rbegin() + 2 % nums.size(), nums.rend());
// 6 7 1 2 3 4 5
//--------------------------------------------------------------------------------------------

// 15. Intersection of two arrays-------------------------------------------------------------
	std::vector<int> first{ 5, 10, 10, 15, 20, 25 };
	std::vector<int> second{ 10, 10, 20, 30, 40, 50 };

	auto it = std::set_intersection(first.begin(), first.end(), 
		                       second.begin(), second.end(), first.begin());
	first.resize(it - first.begin());
// 10 10 20

// 16. Check if a string is a palindrome------------------------------------------------------
if (input == std::string(input.rbegin(), input.rend())) {
    cout << input << " is a palindrome";
}

bool isPalindrome(string X, int i, int j) {
	while (i <= j)
		if (X[i++] != X[j--]) return false;
	return true;
}

// 17. Split string into words (by whitespace)------------------------------------------------
#include <sstream>

	std::string s = "  inc 3 6 ";
	std::istringstream iss(s);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

	for (auto el : tokens) std::cout << "*" << el << "*" << std::endl;

*inc*
*3*
*6*

	std::string s1 = "  push 2 ";
	std::string s2 = "  pop ";
	std::string s3 = "  inc 3 6 "; 
	for (auto el : {s1, s2, s3})
		if (el.find("pop") != std::string::npos)
			std::cout << "*" << el << "*" << std::endl;

*  pop *

// 18. Negate vector--------------------------------------------------------------------------
std::transform(arr.begin(), arr.end(), arr.begin(), std::negate<int>());

// 19. Set both elements to 0 in binary array-------------------------------------------------
// if arr is : [0, 1] or [1, 0] or [0, 0]
arr[!arr[0]] = arr[arr[0]];
arr[!arr[1]] = arr[arr[1]];
arr[!arr[0]] = arr[!arr[1]];

arr[arr[1]] = 0;
arr[arr[1]] = arr[arr[0]];

arr[0] = arr[1] = arr[0] & arr[1];
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
