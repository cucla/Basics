//LeetCode 119
//Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle

std::vector<int> getRow(int rowIndex) {
	std::vector<int> A(rowIndex + 1, 0);
	A[0] = 1;
	for (int i = 1; i<rowIndex + 1; i++)
		for (int j = i; j >= 1; j--)
			A[j] += A[j - 1];
	return A;
}

/*  add previous number:
    1 0 0 0
    1 1 0 0
    1 2 1 0
    1 3 3 1
 */
