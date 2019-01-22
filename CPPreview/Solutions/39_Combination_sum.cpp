//LeetCode 39
/*
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all 
unique combinations in candidates where the candidate numbers sums to target.
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
*/

void combinationSum2(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
	if (!target) {
		res.push_back(combination);
		return;
	}
	for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
		combination.push_back(candidates[i]);
		combinationSum2(candidates, target - candidates[i], res, combination, i);
		combination.pop_back();
	}
}

std::vector<std::vector<int> > combinationSum(std::vector<int> &candidates, int target) {
	std::sort(candidates.begin(), candidates.end());
	std::vector<std::vector<int> > res;
	std::vector<int> combination;
	combinationSum2(candidates, target, res, combination, 0);
	return res;
}


int main() {

	std::vector<int> v{ 2, 3, 5 };
	auto finalResult = combinationSum(v, 8); 

	std::cin.get();
}
