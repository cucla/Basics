#include "stdafx.h"
#include <iostream>

const int BOARDSIZE = 4;

void printSolution(int board[BOARDSIZE][BOARDSIZE]) {
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++)
			std::cout << " " << board[i][j] << " ";
		std::cout << std::endl;
	}
}

bool isSafe(int board[BOARDSIZE][BOARDSIZE], int row, int col) {
	int i, j;

	/* Check this row on left side */
	for (i = 0; i < col; i++)
		if (board[row][i])
			return false;

	/* Check upper diagonal on left side */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j])
			return false;

	/* Check lower diagonal on left side */
	for (i = row, j = col; j >= 0 && i < BOARDSIZE; i++, j--)
		if (board[i][j])
			return false;
      
	return true;
}

bool nQueenUtil(int board[BOARDSIZE][BOARDSIZE], int col) {
	if (col >= BOARDSIZE)
		return true;

	for (int i = 0; i < BOARDSIZE; i++) {
		if (isSafe(board, i, col)) {
			board[i][col] = 1;

			if (nQueenUtil(board, col + 1))
				return true;

			board[i][col] = 0; // BACKTRACK 
		}
	}
	return false;
}

bool solveNQ() {
	int board[BOARDSIZE][BOARDSIZE] = { 0 };
	if (nQueenUtil(board, 0)) {
		printSolution(board);
		return true;
	}
	return false;
}

int main() 
{
	solveNQ();
	std::cin.get();
}
