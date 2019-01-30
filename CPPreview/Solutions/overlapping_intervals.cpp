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

int maxNInt(std::vector<std::pair<int, int>> & v1) 
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

std::vector<std::pair<int, int>> mergeInt(std::vector<std::pair<int, int>> & v)
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

int totalNInt(std::vector<std::pair<int, int>> & v1) 
{
	/* find TOTAL N of overlapping intervals in 1 vector of pairs
	 * __1____2________5____
	 * [1, 2] and [2, 5] are overlapping
	 * steps: megre overlapping intervals -> filter out non-megred from original vector
	 */

	std::sort(v1.begin(), v1.end(), compPairs2);
	std::vector<std::pair<int, int>> v2 = MergeInt(v1);
	std::vector<std::pair<int, int>> v3;
	v3.reserve(std::min(v1.size(), v2.size()));
	
	auto it = std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
	return v3.size();
}

//-----------merging vector of structs------------------
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

std::vector<Interval> merge(std::vector<Interval> & ins) {
	if (ins.empty()) 
		return std::vector<Interval>{};
	std::vector<Interval> res;
	sort(ins.begin(), ins.end(), [](Interval a, Interval b) {return a.start < b.start; });
	res.push_back(ins[0]);
	for (int i = 1; i < ins.size(); i++) {
		if (res.back().end < ins[i].start) res.push_back(ins[i]);
		else
			res.back().end = std::max(res.back().end, ins[i].end);
	}
	return res;
}

//-----------inserting interval, merge if necessary---------------
std::vector<Interval> insert(std::vector<Interval> & intervals, Interval newInterval) {
	auto compare = [](const Interval & intv1, const Interval & intv2) { 
		return intv1.end < intv2.start; 
	};
	auto range = equal_range(intervals.begin(), intervals.end(), newInterval, compare);
	auto itr1 = range.first, itr2 = range.second;
	if (itr1 == itr2) {
		intervals.insert(itr1, newInterval);
	}
	else {
		itr2--;
		itr2->start = std::min(newInterval.start, itr1->start);
		itr2->end = std::max(newInterval.end, itr2->end);
		intervals.erase(itr1, itr2);
	}
	return intervals;
}

//-------------get the number of overlapping intervals, given two lists of intervals-------
/*
Example

L1: ([1,2][2,3][4,5][6,7])
L2: ([1,5][2,3][4,7][5,7])

[1,5] overlaps [1,2] [2,3] [4,5]
[2,3] overlaps [1,2] [2,3]
[4,7] overlaps [4,5] [6,7]
[5,7] overlaps [4,5] [6,7]

total = 3+2+2+2 = 9
 */
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
	if ((3 * A[ia].first - A[ia].second) <= (3 * B[ib].first - B[ib].second)) {
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

/*
Subtle moment - comparison if Compare(A[ia], B[ib]) <= 0 We should here take into account 
also flags - to correctly treat situations when endpoints only touch like [1..2][2..3] 
(you consider this situation as intersection). So both sorting and merge comparator should 
take synthetic value like this:  3 * A[ia].Value - A[ia].Flag. With such comparing start of 
interval is treated before end of interval with the same coordinate.
*/


int main() 
{	 
	// to test vector of pairs -> maxNInt, totalNInt
	std::vector<std::pair<int, int>> v1{ { 0,2 },{ 1,5 },{ 3,7 },{ 7,8 },{ 4,6 },{ 9,11 } };
	std::vector<std::pair<int, int>> v2{ { 2,4 },{ 3,6 },{ 7,8 },{ 9,14 },{ 10,16 },{ 13,15 } };

	std::cin.get();
}

