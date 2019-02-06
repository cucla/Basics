/* Given an Array of Integers and an Integer value k, find out k sub-arrays(may be overlapping) which have k maximum sums

Input : arr = {4, -8, 9, -4, 1, -8, -1, 6}, k = 4
Output : 9 6 6 5

       *
4, -8, 9, -4, 1, -8, -1, 6        9
                         *
4, -8, 9, -4, 1, -8, -1, 6        6
       *   *  *
4, -8, 9, -4, 1, -8, -1, 6        6
*   *  *
4, -8, 9, -4, 1, -8, -1, 6        5
*/

#include "stdafx.h"
#include <iostream>

// Divide-and-conquer Solution
// Other Solution: https://www.geeksforgeeks.org/k-maximum-sum-overlapping-contiguous-sub-arrays/

int Foo(std::vector<int> & v, int left, int right, std::priority_queue<int> & pq) {
	if (left == right) {
		pq.push(v[left]);
		return v[left];
	}

	int center = (left + right) / 2;
	int leftSum = Foo(v, left, center, pq);
	int rightSum = Foo(v, center + 1, right, pq);

	pq.push(leftSum + rightSum);

	if (center != left) {
		int tmp = 0;
		for (int i = center; i > left; --i) {
			tmp += v[i];
			pq.push(tmp + rightSum);
		}
	}

	if ((center + 1) != right) {
		int tmp = 0;
		for (int j = center + 1; j < right; ++j) {
			tmp += v[j];
			pq.push(tmp + leftSum);
		}
	}

	if (center != left || (center + 1) != right) {
		int l = 0;
		for (int i = center; ; --i) {
			l += v[i];
			int r = 0;
			for (int j = center + 1; ; ++j) {
				r += v[j];
				pq.push(l + r);
				if (j == right) break;
			}
			if (i == left) break;
		}
	}

	return leftSum + rightSum;
}


int main()
{
	int k = 4;
	std::vector<int> v{ 4, -8, 9, -4, 1, -8, -1, 6 };

	std::priority_queue<int> pq;
	Foo(v, 0, v.size() - 1, pq);

	while (!pq.empty()) {
		std::cout << pq.top() << " ";
		pq.pop();
	}

	std::cin.get();
}
