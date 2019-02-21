/* 1. Array Sum / Vector sum
 * 2. Count elements == to my own parameter 'myMax' (lambda with count_if)
 * 3. Remove non-consecutive duplicates from Container
 * 4. Int to char/char to int
 * 5. Search sequence for the first number, smaller than a given value
 * 6. Array of functions
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
  
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

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
