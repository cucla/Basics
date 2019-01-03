#include "stdafx.h"
#include "iostream"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <string.h>
#include <tuple> 
#include <unordered_map>


std::vector<std::pair<char, int>> groupBy(std::string s) {

	std::vector<std::pair<char, int>> myMap;
	for (char ch : s) {
		int n = std::count(s.begin(), s.end(), ch);
		if (n > 0)
			myMap.push_back(std::make_pair(ch, n));
	}
	return myMap;
}

bool isLongPressedName(std::string name, std::string typed) {
	std::vector<std::pair<char, int>> myMap_name = groupBy(name);
	std::vector<std::pair<char, int>> myMap_typed = groupBy(typed);

	if (myMap_name.size() != myMap_typed.size())
		return false;

	for (auto kv : myMap_name) {
		if (kv.second > myMap_typed[kv.first])
			return false;
	}
}

int main() {

	std::string s1 = "kikcxmvzi";
	std::string s2 = "kiikcxxmmvvzz";

	std::cout << "Hi" << std::endl;


	std::cin.get();
}

