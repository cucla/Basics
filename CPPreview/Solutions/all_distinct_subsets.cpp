/* Generate all subsets from [1, 3, 1] -> with repeated elements:
 * sort & 
 * exclude all adjacent duplicated elements along with case 2
 * case 1: consider element / case 2: don't consider element
 */


using namespace std;

// Function to print the elements of a vector
void printVector(vector<int> const &out)
{
	for (int i: out)
		cout << i << " ";
	cout << '\n';
}

// Recursive function to print all distinct subsets of S
// S	--> input set
// out  --> vector to store subset
// i	--> index of next element in set S to be processed
void findPowerSet(int S[], vector<int> &out, int i)
{
	// if all elements are processed, print the current subset
	if (i < 0)
	{
		printVector(out);
		return;
	}

	// include current element in the current subset and recurse
	out.push_back(S[i]);
	findPowerSet(S, out, i - 1);

	// exclude current element in the current subset
	out.pop_back(); // backtrack

	// remove adjacent duplicate elements
	while (S[i] == S[i-1])
		i--;

	// exclude current element in the current subset and recurse
	findPowerSet(S, out, i - 1);
}

// Program to generate all distinct subsets of given set
int main()
{
	int S[] = { 1, 3, 1 };
	int n = sizeof(S) / sizeof(S[0]);

	// sort the set
	sort(S, S + n);

	// create an empty vector to store elements of a subset
	vector<int> out;
	findPowerSet(S, out, n-1);

	return 0;
}

3 1 1
3 1
3
1 1
1
