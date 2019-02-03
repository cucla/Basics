/*  Find the k’th smallest element in an unsorted array; all elements are distinct:
Input: arr[] = {7, 10, 4, 3, 20, 15}
       k = 3
Output: 7
 */
 
 Method #1: QuickSelect
 
 int quickSelect(std::vector<int> & v, int left, int right, int k) {
	int sz = right - left + 1;
	int pivot = v[sz + left - 1];
	int l = left - 1, m = left;
	for (; m < (sz + left); ++m) {
		if (v[m] <= pivot) {
			++l;
			int tmp = v[l];
			v[l] = v[m];
			v[m] = tmp;
		}
	}
	if (k == l + 1) return pivot;
	else if (k < (l + 1)) quickSelect(v, 0, (l - 1), k);
	else if (k > (l + 1)) quickSelect(v, (l + 1), right, k);
}

int main() 
{	 
	int k = 4;
	std::vector<int> v{ 7, 10, 4, 3, 20, 15 };
	int r = quickSelect(v, 0, v.size() - 1, k);
	std::cout << r << std::endl;

	std::cin.get();
}
