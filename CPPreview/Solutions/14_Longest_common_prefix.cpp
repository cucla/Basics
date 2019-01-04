//LeetCode 14
//Write a function to find the longest common prefix string amongst an array of strings
//{ "leetcode", "leet", "lee", "le" }

/* Divide and conquer
  1. pass l & r indices to recursive function
  2. collect results to strings and pass them to next utility function
 */


std::string commonPrefix(std::string left, std::string right) {
	std::string prefix;
	int l = std::min(left.size(), right.size());

	for (int i = 0; i < l; i++) {
		if (left[i] == right[i])
			prefix.push_back(left[i]);
		else
			return prefix;
	}
	return prefix;
}

std::string lcp(std::vector<std::string> & strs, int l, int r) {
	if (l == r) 
		return strs[l];
	else {
		int mid = (l + r) / 2;
		std::string lcpLeft = lcp(strs, l, mid);
		std::string lcpRight = lcp(strs, mid + 1, r);
		return commonPrefix(lcpLeft, lcpRight);
	}
}

std::string longestCommonPrefix(std::vector<std::string> & strs) {   // "leetcode", "leet", "lee", "le"
	if (strs.size() == 0)
		return "";
	return lcp(strs, 0, strs.size() - 1);
}
