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



//LeetCode 113
/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
Note: A leaf is a node with no children.

[5,4,8,11,null,13,4,7,2,null,null,5,1]
22
Return:
[
   [5,4,11,2],
   [5,8,4,5]
]
*/

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


void util(TreeNode* root, int sum, vector<int>& dump, vector<vector<int>>& ans) {
	if (!root) return;

	dump.push_back(root->val);

	if (!root->left && !root->right && root->val == sum)
		ans.push_back(dump);
	util(root->left, sum - root->val, dump, ans);
	util(root->right, sum - root->val, dump, ans);

	dump.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
	vector<vector<int>> ans;
	vector<int> dump;
	util(root, sum, dump, ans);
	return ans;
}

int main() 
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(-2);
	root->right = new TreeNode(-3);
	root->left->left = new TreeNode(1);
	root->left->right = new TreeNode(3);
	root->right->left = new TreeNode(-2);
	root->left->left->left = new TreeNode(-1);

	auto r = pathSum(root, 2);
}


// 473. Matchsticks to Square
/* Find out a way you can make one square by using up all given matchsticks. 
 * You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 */

using namespace std;

bool util(vector<int>& nums, vector<int>& sides, int i) {
	if (i == -1)
		return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3];

	for (int k = sides.size() - 1; k >= 0; --k) {
		if (sides[k] < nums[i]) continue;

		// OPTIMIZATION:
		// With 4 sides in a square, we can check if we have encountered the same length with the current match length before
		int j = k;
		while (++j < sides.size())
			if (sides[k] == sides[j]) break;
		if (j != sides.size()) continue;

		sides[k] -= nums[i];
		if (util(nums, sides, i - 1)) return true;
		sides[k] += nums[i];

	}
	return false;
}

bool makesquare(vector<int>& nums) {
	if (nums.size() < 4) return false;

	int sum = accumulate(nums.begin(), nums.end(), 0);
	if (sum % 4 != 0) return false;

	sort(nums.begin(), nums.end());
	int side = sum / 4;
	vector<int> sides(4, side);

	return util(nums, sides, nums.size() - 1);
}
