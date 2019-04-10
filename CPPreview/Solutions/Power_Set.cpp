/* Generate all subsets from [1, 3, 1] -> 
 * sort if repeated elements !!!
 */


void powerSet(std::vector<int> & candidates, int idx, std::vector<int> & tmp, std::set<std::vector<int>> & res) {

	if (idx >= candidates.size()) {
		res.insert(tmp);
		return;
	}
	// include
	tmp.push_back(candidates[idx]);
	powerSet(candidates, idx + 1, tmp, res);
	
	// exclude
	tmp.pop_back();
	powerSet(candidates, idx + 1, tmp, res);
}


int main() 
{
	std::vector<int> candidates{ 1, 3, 1 };    // 1 1 3
	std::sort(candidates.begin(), candidates.end());

	std::set<std::vector<int>> res;
	std::vector<int> tmp;
	powerSet(candidates, 0, tmp, res);

	for (auto vect : res) {
		for (auto el : vect)
			std::cout << el << ' ';
		std::cout << std::endl;
	}

	std::cin.get();
}

{}
1
1 1
1 1 3
1 3
3

	
/* When Power Set is used to find subset with maximum product,
 * however, linear time approach exists: https://www.techiedelight.com/maximum-product-subset-problem/
 */
	
void maxProduct(std::vector<int> & comb, int & res) {
	int product = 1;
	for (int j : comb) product = product * j;

	if (comb.size())
		res = std::max(res, product);
}

void maxProduct(std::vector<int> & candidates, int idx, std::vector<int> & comb, int & res) {
	if (idx == 0) {
		maxProduct(comb, res);
		return;
	}

	comb.push_back(candidates[idx - 1]);
	maxProduct(candidates, idx - 1, comb, res);

	comb.pop_back();
	maxProduct(candidates, idx - 1, comb, res);
}

int main() 
{
	std::vector<int> candidates{ -6, 4, -5, 8, -10, 0, 8 };

	int res = 1;
	std::vector<int> comb;
	maxProduct(candidates, candidates.size(), comb, res);

	std::cout << res << std::endl;

	std::cin.get();
}
