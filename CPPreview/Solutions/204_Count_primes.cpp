//LeetCode 204
//Count the number of prime numbers less than a non-negative number, n

int countPrimes(int n) {
	if (n <= 2) return 0;
	std::vector<bool> passed(n, false);
	int sum = 1;
	int upper = sqrt(n);
	for (int i = 3; i<n; i += 2) {
		if (!passed[i]) {
			sum++;
			if (i>upper) continue;
			for (int j = i * i; j<n; j += i) {   // non prime numbers are formed from n * n of the first odd/prime numbers 
				passed[j] = true;            // and consecutive +n steps
			}
		}
	}
	return sum;
}
