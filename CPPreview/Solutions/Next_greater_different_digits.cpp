int nextNum(int num) {
	string res = "";
	set<int> used;

	string tmp = to_string(num);              // "3025"
	for (int i = 0; i < tmp.size(); ++i) {    // '3' '0' '2' '5'
		used.insert(tmp[i] - '0');        // 3 0 2 5
	}
	if (used.size() == 10) return -1;
	if (used.size() == 9 && used.count(0) == 1) return -1;

	// find first digit  !!! 9 not handled
	int d = (tmp[0] - '0') + 1;
	while (used.count(d) != 0) ++d;
	if (d == 10) {
		d = 1;
		while (used.count(d) != 0) ++d;
	}
	tmp += '*';
	res += to_string(d);

	// find rest of the digits
	for (int i = 1; i < tmp.size(); ++i) {
		int next_d = 0;
		while (used.count(next_d) != 0) ++next_d;
		res += to_string(next_d);
	}
	long long ans = stoi(res);

	return ans;
}




int main()
{
	int num1 = 2;
	int num2 = 901;
	int num3 = 3025;

	cout << nextNum(num1) << endl;  // 3
	cout << nextNum(num2) << endl;  // 2222
	cout << nextNum(num3) << endl;  // 4111

	std::cin.get();
}
