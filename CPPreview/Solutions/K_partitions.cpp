/* Partition to K Equal Sum Subsets
 *
 * Given an array of integers nums and a positive integer k, find whether it's possible to divide this array 
 * into k non-empty subsets whose sums are all equal and they completely cover the set. Print them!
 *
 * Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 * Output: True
 * Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 *
 */

using namespace std;

bool checkSum(vector<int> & sumLeft, int k) {
	int r = true;
	for (int i = 0; i < k; i++) 
		if (sumLeft[i] != 0) r = false;
	return r;
}

bool subsetSum(vector<int> & S, int n, vector<int> & sumLeft, vector<int> & A, int k) {
	if (checkSum(sumLeft, k)) return true;
	if (n < 0) return false;

	bool res = false;

	for (int i = 0; i < k; i++) {
		if (!res && (sumLeft[i] - S[n]) >= 0) {
			A[n] = i + 1;
			sumLeft[i] = sumLeft[i] - S[n];
			res = subsetSum(S, n - 1, sumLeft, A, k);
			sumLeft[i] = sumLeft[i] + S[n];
		}
	}
	return res;
}

void partition(vector<int> & S, int k) {
	if (S.size() < k) {
		std::cout << "k-Partition of set S is not Possible";
		return;
	}

	int sum = std::accumulate(S.begin(), S.end(), 0);

	vector<int> A(S.size());
	vector<int> sumLeft(k, sum / k);

	bool res = !(sum % k) && subsetSum(S, S.size() - 1, sumLeft, A, k);

	if (!res) {
		std::cout << "k-Partition of set S is not Possible";
		return;
	}

	// print all k-partitions
	for (int i = 0; i < k; i++) {
		std::cout << "Partition " << i << " is: ";
		for (int j = 0; j < S.size(); j++)
			if (A[j] == i + 1)
				std::cout << S[j] << " ";
		std::cout << std::endl;
	}
}

int main() 
{
	vector<int> S{ 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };
	int k = 5;

	partition(S, k);
  
	std::cin.get();
}
