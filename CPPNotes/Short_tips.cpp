/* 1. Array Sum / Vector sum
 * 2. Count elements == to my own parameter 'myMax' (lambda with count_if)
 * 3. Convert decimal to binary (& vice verca)
 * 4. Pointer to 2D array
 * 5. Search sequence for the first number, smaller than a given value
 * 6. Array of functions
 */
 
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
//--------------------------------------------------------------------------------------------

// 2. Count elements == to my own parameter 'myMax' (lambda with count_if)--------------------
std::vector<int> ar({ 3, 2, 1, 3 });
auto myMax = *std::max_element(ar.begin(), ar.end());
auto myCount = std::count_if(ar.begin(), ar.end(), [myMax](int i) { return i == myMax; });
//--------------------------------------------------------------------------------------------

// 3. Convert decimal to binary (& viceverca)-------------------------------------------------
void convertToBinary(unsigned int n) {
	if (n / 2 != 0) {
		convertToBinary(n / 2);
	}
	printf("%d", n % 2);
}

void convertToDecimal(unsigned int n) {
	long factor = 1;
	long total = 0;

	while (n != 0)
	{
		total += (n % 10) * factor;
		n /= 10;
		factor *= 2;
	}
	printf("%d", total);
}
//--------------------------------------------------------------------------------------------

// 4. Pointer to 2D array---------------------------------------------------------------------
int ** magicSquare = new int *[MAX_SIZE];
for (int i = 0; i < MAX_SIZE; ++i) {
	magicSquare[i] = new int[MAX_SIZE];
}
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
