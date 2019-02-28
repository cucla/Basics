/*
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
*/


int strStr(std::string haystack, std::string needle) {
	int m = haystack.size();
	int n = needle.size();
	int p = 0;

	while (true) {
		if (p + n > m) {
			return -1;
		}
		if (haystack.substr(p, n) == needle) {
			return p;
		}
		while (p++ + n - 1 < m && haystack[p] != needle[0]);
	}
}

int main()
{
	std::string haystack = "hello";
	std::string needle = "ll";

	auto r = strStr(haystack, needle);
}
