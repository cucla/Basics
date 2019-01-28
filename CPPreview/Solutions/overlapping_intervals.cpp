#include "stdafx.h"
#include "iostream"


struct Comp {
	/* instead  {2, -1}  sort {2, 1}
	 *	    {2, 1}        {2, -1}
	 */
	bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) {
		if (a.first != b.first)
			return a.first < b.first;
		return a.second > b.second;
	}
} compPairs;

int MaxNInt(std::vector<std::pair<int, int>> & v1) 
{
	/* find MAX N of overlapping intervals in 1 vector of pairs
	 * __1____2________5____
	 * [1,2] and [2,5] are overlapping
	 */
	
	std::vector<std::pair<int, int>> startEnd;
	for (auto el : v1) {
		startEnd.push_back({ el.first, 1 });      // 1 for the start of the interval
		startEnd.push_back({ el.second, -1 });	  // -1 for the end of the interval
	}
	std::sort(startEnd.begin(), startEnd.end(), compPairs);
	
	int maxInt = 0, currentInt = 0;
	for (auto el : startEnd) {
		currentInt += el.second;
		maxInt = std::max(maxInt, currentInt);
	}
	return maxInt;
}

std::vector<std::pair<int, int>> MergeInt(std::vector<std::pair<int, int>> & v)
{
	/* merge overlapping intervals in 1 vector of pairs
	* __1____2________5____
	* [1,2] and [2,5] are overlapping
	*/

	std::vector<std::pair<int, int>> startEnd;
	for (auto el : v) {
		startEnd.push_back({ el.first, 1 });
		startEnd.push_back({ el.second, -1 });
	}
	std::sort(startEnd.begin(), startEnd.end(), compPairs);

	std::vector<std::pair<int, int>> result;
	std::pair<int, int> p{0,0};

	int activeInts = 0;
	for (int i = 0; i < startEnd.size(); i++) {
		int tmp = activeInts;
		activeInts += startEnd[i].second;

		if (i == 0)  
			p.first = startEnd[i].first;	// p{ 0 ,0};
		else if (startEnd[i].second > 0 && !tmp)
			p.first = startEnd[i].first;	// p{ 0 ,0};
		else if (startEnd[i].second < 0)
			p.second = startEnd[i].first;	// p{0, 0 };
		
		if (activeInts == 0) result.push_back(p);
	}
	return result;
}

struct Comp2 {
	bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) {
		if (a.first != b.first) 
			return a.first < b.first;
		return a.second < b.second;
	}
} compPairs2;

int TotalNInt(std::vector<std::pair<int, int>> & v1) 
{
	/* find TOTAL N of overlapping intervals in 1 vector of pairs
	 * __1____2________5____
	 * [1, 2] and [2, 5] are overlapping
	 */

	std::sort(v1.begin(), v1.end(), compPairs2);
	std::vector<std::pair<int, int>> v2 = MergeInt(v1);
	std::vector<std::pair<int, int>> v3;
	v3.reserve(std::min(v1.size(), v2.size()));
	
	auto it = std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
	return v3.size();
}


int main() 
{	 
	// to test vector of pairs -> MaxNInt, TotalNInt
	std::vector<std::pair<int, int>> v1{ { 0,2 },{ 1,5 },{ 3,7 },{ 7,8 },{ 4,6 },{ 9,11 } };
	std::vector<std::pair<int, int>> v2{ { 2,4 },{ 3,6 },{ 7,8 },{ 9,14 },{ 10,16 },{ 13,15 } };
	
	
	
	
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

