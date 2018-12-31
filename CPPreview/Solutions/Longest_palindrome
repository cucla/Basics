// LeetCode 409
// Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters

int longestPalindrome(std::string s) {
	int _map[256] = { 0 };
	int res = 0;
	bool appender = false;
	for (auto & a : s) {
		_map[a]++;
	}
	for (auto & a : _map) {
		if (a > 0) {
			res += a / 2 * 2;
		}
	}
	return res + (res == s.length() ? 0 : 1);
}

/* 
 * Character values are stored in a computer by using ASCII codes, in 1 byte (8 bits) which provides 256 distinct codes (2^8)
 */
