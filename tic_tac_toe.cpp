#include "games.h"
#include "info.h"
#include "player.h"
#include "misc.h"

#include <iostream>

constexpr char Empty{ ' ' };

// To store how the player won (the taken places that made them win)
struct VictorySet {
	int singleIndex0{ 0 };
	int singleIndex1{ 0 };
	int singleIndex2{ 0 };
	bool valid{ true };
};

// [0-8] General index for the board
inline static int toSingleIndex(int row, int column) {
	return (row * 3) + column;
}

// It checks if singleIndex is in the range [0-8];
inline static bool isValidSingleIndex(int singleIndex) {
	return (singleIndex >= 0 && singleIndex <= 8);
}

// [0-2] Vertical index
inline static int toRow(int singleIndex) {
	return (singleIndex / 3);
}

// [0-2] Horizontal index
inline static int toColumn(int singleIndex) {
	return (singleIndex % 3);
}

// It checks if a place is already marked by other player
inline static bool isTaken(char board[3][3], int singleIndex) {
	return board[toRow(singleIndex)][toColumn(singleIndex)] != Empty;
}

// It draws only a portion of the board (i0, i1, i2 places); useful to show how the winner won the game.
static void subdrawBoard(char board[3][3], int i0, int i1, int i2) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (toSingleIndex(i, j) == i0 || toSingleIndex(i, j) == i1 || toSingleIndex(i, j) == i2) {
				std::cout << "[" << board[i][j] << "]";
			} else {
				std::cout << "   ";
			}
		}
		std::cout << '\n';
	}
}

// It draws the entire board
static void drawBoard(char board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << "[" << board[i][j] << "]";
		}
		std::cout << '\n';
	}
}

// It collects input from the current player or random generates it if the player is the computer itself.
static void getInput(char board[3][3], const Player& player) {
	
	int place{ 0 };
	bool validMove{ false };

	std::cout << player.name << ", where will you place your symbol [0-8]: ";

	if (isComputer(player)) {
		do {
			place = toSingleIndex(nextInteger(0, 3), nextInteger(0, 3));
			validMove = (isTaken(board, place) ? false : true);
		} while (!validMove);
		std::cout << place << "\n";
	} else {
		do {
			place = inputInt();
			if (!isValidSingleIndex(place)) {
				std::cout << "This position is not valid.\n";
				validMove = false;
			} else if (isTaken(board, place)) {
				std::cout << "This place is already taken.\n";
				validMove = false;
			} else {
				validMove = true;
			}
		} while (!validMove);
	}

	board[toRow(place)][toColumn(place)] = player.symbol;

}

// It returns the symbol's owner
static const Player* whoHasThisSymbol(char symbol, const Player& p1, const Player&  p2) {
	if (p1.symbol == symbol) {
		return &p1;
	} else if (p2.symbol == symbol) {
		return &p2;
	}
	return nullptr;
}

// It tests all the possibilities for victory and stores how it occurred in a VictorySet
static VictorySet findVictorySet(char board[3][3]) {

	// Horizontal tests
	for (int row = 0; row < 3; ++row) {
		if (board[row][0] != Empty && (board[row][0] == board[row][1] && board[row][1] == board[row][2])) {
			return VictorySet{ toSingleIndex(row, 0), toSingleIndex(row, 1), toSingleIndex(row, 2), true };
		}
	}

	// Vertical tests
	for (int column = 0; column < 3; ++column) {
		if (board[0][column] != Empty && (board[0][column] == board[1][column] && board[1][column] == board[2][column])) {
			return VictorySet{ toSingleIndex(0, column), toSingleIndex(1, column), toSingleIndex(2, column), true };
		}
	}

	// Diagonal tests
	if (board[1][1] != Empty) {
		// Primary diagonal test
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			return VictorySet{ toSingleIndex(0, 0), toSingleIndex(1, 1), toSingleIndex(2, 2), true };
		}
		// Secondary diagonal test
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			return VictorySet{ toSingleIndex(0, 2), toSingleIndex(1, 1), toSingleIndex(2, 0), true };
		}
	}

	return VictorySet{ 0, 0, 0, false };

}

// It returns the winner
static const Player* checkVictory(char board[3][3], const Player& p1, const Player& p2) {
	VictorySet victorySet{ findVictorySet(board) };
	if (victorySet.valid) {
		return whoHasThisSymbol(board[toRow(victorySet.singleIndex0)][toColumn(victorySet.singleIndex0)], p1, p2);
	}
	return nullptr;
}

// It tests if there is at least one available place at the board; useful to check for a draw
static bool isBoardComplete(char board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == Empty)
				return false;
		}
	}
	return true;
}

// Tic Tac Toe game loop and main controller
Info runTicTacToe(const Player& p1, const Player& p2) {
	
	Info info{ nullptr, nullptr };

	const Player* winner{ nullptr };
	const Player* turn{ &p1 };

	char board[3][3]{
		{Empty, Empty, Empty},
		{Empty, Empty, Empty},
		{Empty, Empty, Empty}
	};

	do {

		header("Tic Tac Toe");

		drawBoard(board);
		getInput(board, *turn);

		winner = checkVictory(board, p1, p2);
		if (winner != nullptr) { // A winner has been found.

			header("Tic Tac Toe");

			VictorySet set{ findVictorySet(board) };
			subdrawBoard(board, set.singleIndex0, set.singleIndex1, set.singleIndex2);

			if (!isComputer(*winner)) {
				std::cout << "Well done, " << winner->name << "! You win the game.\n";
			} else {
				std::cout << "Well done, " << winner->name << "! I win the game.\n";
			}

			info.winner = winner;
			info.loser = &(winner == &p1 ? p2 : p1);

			break;

		} else if (isBoardComplete(board)) { // It's a draw.

			header("Tic Tac Toe");

			drawBoard(board);
			std::cout << "DRAW! Nobody wins.\n";

			break;

		}

		// otherwise, the game continues...
		turn = &(turn == &p1 ? p2 : p1);

	} while (true);

	return info;

}