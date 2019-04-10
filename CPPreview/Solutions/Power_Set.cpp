/* Generate all subsets from [1, 3, 1] -> 
 * sort if repeated elements !!!
 */


void powerSet(std::vector<int> & candidates, int idx, std::vector<int> & tmp, std::set<std::vector<int>> & res) {

	if (idx >= candidates.size()) {
		res.insert(tmp);
		return;
	}

	tmp.push_back(candidates[idx]);
	powerSet(candidates, idx + 1, tmp, res);
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
