//LeetCode 784
//Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  
//Return a list of all possible strings we could create.

/*
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]
*/

std::vector<std::string> letterCasePermutation2(std::string s) {
	std::vector<int> ind;
	for (int i = 0; i < s.size(); ++i) {
		if (isalpha(s[i])) ind.push_back(i);
	}
	const int n = 1 << ind.size();

	std::vector<std::string> ans;
	for (int x = 0; x < n; ++x) {  // 16
		for (int i = 0, y = x; i < ind.size(); ++i, y >>= 1) {

			std::cout << std::bitset<8>(y) << std::endl;

			char & c = s[ind[i]];

			std::cout << std::bitset<8>(y & 1) << std::endl;

			if (y & 1) c = toupper(c);
			else c = tolower(c);
		}
		ans.push_back(s);
	}
	return ans;
}

