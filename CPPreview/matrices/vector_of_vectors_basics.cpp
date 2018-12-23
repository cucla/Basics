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

	std::vector<std::vector<int>> matrix2{
		{ 1, 2 },
		{ 3, 4 },
		{ 5, 6 } };
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
		transform(v.begin(), v.end(), scalars.begin(),
			v.begin(), std::plus<int>());
		}
	);
	prettyPrint(transpose);
	/*
	101 103 105
	102 104 106
	*/


	std::cin.get();
}

