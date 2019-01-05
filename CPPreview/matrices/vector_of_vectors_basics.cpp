//c++ vector of vectors site:stackoverflow.com

#include "stdafx.h"
#include "iostream"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <string.h>



int getElement(std::vector<std::vector<int>> matrix, const int & row, const int & col) {
	return matrix[row][col];
}

void prettyPrint(std::vector<std::vector<int>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << getElement(matrix, i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "--------------" << std::endl;
}

int main()
{
	typedef std::vector<int>::size_type vect_size;

	int rows = 4;
	int cols = 3;
	std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
	prettyPrint(matrix);  
	/*
	0 0 0
	0 0 0
	0 0 0
	0 0 0
	*/

	for (vect_size i = 0; i < matrix.size(); i++) {
		//matrix[i][0] = 4;
		matrix[i].push_back(4);
	}
	prettyPrint(matrix);
	/*
	0 0 0 4
	0 0 0 4
	0 0 0 4
	0 0 0 4
	*/

	std::vector<std::vector<int>> matrix1{
	{ 1, 2 },
	{ 3, 4 },
	{ 5, 6 } };
	std::vector<std::vector<int>> matrix2;
	
	// copy one matrix to another
	matrix2 = matrix1;
	prettyPrint(matrix2);
	/*
	1 2
	3 4
	5 6
	*/

	// transpose matrix
	std::vector<std::vector<int>> transpose(matrix2[0].size(), std::vector<int>(matrix2.size()));
	for (vect_size i = 0; i < matrix2.size(); i++) {   
		for (vect_size j = 0; j < matrix2[i].size(); j++) {   
			transpose[j][i] = matrix2[i][j];
		}
	}
	prettyPrint(transpose);
	/*
	1 3 5
	2 4 6
	*/

	// put elements from 2D vector to 1D vector
	std::vector<int> myVector;
	for (auto v : matrix2) {
		myVector.insert(myVector.begin(), v.begin(), v.end());
	}

	// add elements of 'scalars' one by one to 'transpose'
	std::vector<int> scalars({100, 100, 100});
	//std::transform(transpose[0].begin(), transpose[0].end(), scalars.begin(), transpose[0].begin(), std::plus<int>());	
	std::for_each(transpose.begin(), transpose.end(),
		[&scalars](std::vector<int> & v) {
		std::transform(v.begin(), v.end(), scalars.begin(),
			v.begin(), std::plus<int>());
		}
	);
	prettyPrint(transpose);
	/*
	101 103 105
	102 104 106
	*/

	std::vector<std::vector<int>> v_main{
		{ 7, 2, 2, 1 },
		{ 3, 4, 4 },
		{ 5, 6, 5, 1, 1 } };
	std::for_each(v_main.begin(), v_main.end(), 
		[](std::vector<int> & v) {
		v.erase(std::unique(v.begin(), v.end()), v.end()); 
	});
	prettyPrint(v_main);
	/*
	7 2 1
	3 4
	5 6 5 1
	*/

	//resize outer vector
	v_main.resize(6, std::vector<int>(4));
	prettyPrint(v_main);
	/*
	7 2 1
	3 4
	5 6 5 1
	0 0 0 0
	0 0 0 0
	0 0 0 0
	*/

	//sort by size of each vector
	std::sort(v_main.begin(), v_main.end(), 
		[](const std::vector<int> & a, const std::vector<int> & b) { 
		return a.size() < b.size(); });
	prettyPrint(v_main);
	/*
	3 4
	7 2 1
	5 6 5 1
	0 0 0 0
	0 0 0 0
	0 0 0 0
	*/
	
	
	// verify all vectors have equal size
	std::vector<std::vector<int>> m{
		{ 2, 4, 33 },
		{ 1, 0, 14 },
		{ 9, 19, 7 }	
	};
	int sz = 3;
	auto res = std::all_of(m.begin(), m.end(), [&sz](std::vector<int> & v) { return v.size() == sz; });  	// 1
	


	std::cin.get();
}

