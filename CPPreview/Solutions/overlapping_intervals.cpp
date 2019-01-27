// https://stackoverflow.com/search?q=%5Bc%2B%2B%5D+overlap+intervals
// http://www.zrzahid.com/maximum-number-of-overlapping-intervals/


#include "stdafx.h"
#include <iostream>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue> 
#include <iterator>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> 
#include <numeric>
#include <utility>


struct Comp {
	/* instead	{2, -1}  sort {2, 1}
	 *			{2, 1}        {2, -1}
	 */
	bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) {
		if (a.first != b.first) {
			return a.first < b.first;
		}
		return a.second > b.second;
	}

} compPairs;

int MaxNInt(std::vector<std::pair<int, int>> & v1) 
{
	/* find maximum N of overlapping intervals
	 * __1____2________5____
	 * [1,2] and [2,5] are overlapping
	 */
	std::vector<std::pair<int, int>> startEnd;

	for (auto el : v1) {
		startEnd.push_back({ el.first, 1 });
		startEnd.push_back({ el.second, -1 });
	}
	std::sort(startEnd.begin(), startEnd.end(), compPairs);
	int currentInt = 0;
	int maxInt = 0;
	for (auto el : startEnd) {
		currentInt += el.second;
		maxInt = std::max(maxInt, currentInt);
	}
	return maxInt;
}


int main() 
{	 
	std::vector<std::pair<int, int>> v1{ { 1,2 },{ 2,3 },{ 4,5 },{ 6,7 } };
	std::vector<std::pair<int, int>> v2{ { 1,5 },{ 2,3 },{ 4,7 },{ 5,7 } };

	std::vector<std::pair<int, int>> A{ { 1,1 },{ 2,1 },{ 2,-1 },{ 3,-1 },
										{ 4,1 },{ 5,-1 },{ 6,1 },{ 7,-1 } };
	std::vector<std::pair<int, int>> B{ { 1,1 },{ 2,1 },{ 3,-1 },{ 4,1 },
										{ 5,1 },{ 5,-1 },{ 7,-1 },{ 7,-1 } };


	int CntA = 0;
	int CntB = 0;
	int Res = 0;
	int ia = 0;
	int ib = 0;
	while ((ia < A.size()) && (ib < B.size())) {
		if ( (3 * A[ia].first - A[ia].second) <= (3 * B[ib].first - B[ib].second) ) {      
			CntA += A[ia].second;
			if (A[ia].second < 0)
				Res += CntB;
			ia++;
		}
		else {
			CntB = CntB + B[ib].second;
			if (B[ib].second < 0)
				Res += CntA;
			ib++;
		}
	}

	std::cout << Res << std::endl;


	std::cin.get();
}

