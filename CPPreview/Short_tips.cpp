/* 1. Array Sum / Vector sum
 * 2. Count elements == to my own parameter 'myMax' (lambda with count_if)
 * 3. Remove non-consecutive duplicates from Container
 * 4. Int to char/char to int
 * 5. Search sequence for the first number, smaller than a given value
 * 6. Array of functions
 * 7. std::find_if vs std::find
 * 8. trim spaces in a string using std::find_if()
 * 9. MAP: select by value + custom comparator
 * 10. decltype() to deduce the type for std::find_if()
 * 11. Find element, that satisfies v[i] <= x < v[i + 1], using std::adjacent_find()
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

// 6. Array of functions----------------------------------------------------------------------
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

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
