/* Let A be a set of 4 sets:
  A1 {1, 2, 3}
  A2 {2, 3, 4}
  A3 {1, 3, 5}
  A4 {2, 3}
                                                          INTERSECTION!
  Cardinality of union of sets: |A1| + |A2| + |A3| + |A4| - |A1A2| - |A1A3| - |A1A4| - |A2A3| - |A2A4| - |A3A4| + |A1A2A3| 
                                + |A1A2A4| + |A1A3A4| + |A2A3A4| - |A1A2A3A4|
 */


int intersectionCardinality(std::vector<std::vector<int>> & sets, std::vector<int> & indices) {
	std::unordered_map<int, int> myMap;
	for (auto idx : indices) {
		for (auto el : sets[idx]) {
			if (myMap.find(el) != myMap.end())
				++myMap[el];
			else
				myMap.emplace(el, 1);
		}
	}
	int count = 0;
	for (auto el : myMap) {
		if (el.second == indices.size())
			++count;
	}
	return count;
}


int main() 
{
	std::vector<std::vector<int>> sets{ {1, 2, 3}, {2, 3, 4}, {1, 3, 5}, {2, 3} };

	int result = 0;
	for (int i = 0; i < (1 << sets.size()); i++) {   //for 4 elements -> 16 subsets

		std::vector<int> idx;
		for (int j = 0; j < sets.size(); j++) {
			if (i & (1 << j))
				idx.push_back(j);
		}
		int cardinality = intersectionCardinality(sets, idx);
		if (idx.size() % 2 == 1) 
			result += cardinality;
		else 
			result -= cardinality;
	}
	std::cout << result << std::endl;

	std::cin.get();
}
