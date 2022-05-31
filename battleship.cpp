#include "games.h"
#include "info.h"
#include "player.h"
#include "misc.h"

#include <iostream>
#include <cmath>

constexpr char Empty{ ' ' };

constexpr char Unknown{ '~' };

inline static int toSingleIndex(int i, int j, int dimension) {
	return j * dimension + i;
}

inline static bool isInsideTheBounds(int singleIndex, int length) {
	return (singleIndex >= 0 && singleIndex < length);
}

inline static bool isUnknown(char* visibleBoard, int position) {
	return visibleBoard[position] == Unknown;
}

inline static int totalShipsByLength(int length) {
	return (((int) std::sqrt(length)) * 2);
}

void drawBoard(char* board, int dimension) {
	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j) {
			std::cout << "(" << board[toSingleIndex(j, i, dimension)] << ")";
		}
		std::cout << '\n';
	}
}

static void locateShips(char* hiddenBoard, const int length, char s1, char s2) {

	int position{};
	int totalShips{ 0 };

	const int max = totalShipsByLength(length);

	for (totalShips = 0; totalShips < max; ) {
		position = nextInteger(length);
		if (hiddenBoard[position] == Empty) {
			hiddenBoard[position] = ((totalShips % 2 == 0) ? s1 : s2);
			++totalShips;
		}
	}

}

static int getInput(char* visibleBoard, int length, const Player& player) {

	int target{};
	bool valid{};

	std::cout << player.name << ", where will you attack [0-" << (length - 1) << "]\n";

	if (isComputer(player)) {
		do {
			target = nextInteger(length);
		} while (!isUnknown(visibleBoard, target));
		std::cout << target << "\n";
	} else {
		do {
			valid = false;
			target = inputInt();
			if (!isInsideTheBounds(target, length)) {
				std::cout << "This position is out of the bounds.\n";
			} else if (!isUnknown(visibleBoard, target)) {
				std::cout << "There is nothing to do at this place anymore.\n";
			} else {
				valid = true;
			}
		} while (!valid);
	}

	return target;

}

static bool processAttack(const Player& attacker, char* hiddenBoard, char* visibleBoard, int target) {

	visibleBoard[target] = hiddenBoard[target];

	std::cout << attacker.name;
	if (hiddenBoard[target] == Empty) {
		std::cout << " missed the cannonball!\n";
		return false;
	} else if (hiddenBoard[target] == attacker.symbol) {
		std::cout << ", you attacked one of your ships!\n";
		return false;
	} else {
		std::cout << ", you sank one of your opponent's ship!\n";
	}

	return true;

}

static const Player* check(const Player* p1, const Player* p2, char* visibleBoard, int length) {

	int p1Score = 0;
	int p2Score = 0;

	for (int i = 0; i < length; ++i) {
		if (visibleBoard[i] == p2->symbol) {
			++p1Score;
		} else if (visibleBoard[i] == p1->symbol) {
			++p2Score;
		}
	}

	if (p1Score >= (totalShipsByLength(length) / 2))
		return p1;
	if (p2Score >= (totalShipsByLength(length) / 2))
		return p2;

	return nullptr;

}

// Battleship game loop and main controller
Info runBattleship(const Player& p1, const Player& p2) {

	Info info{ nullptr, nullptr };

	const Player* winner{ nullptr };
	const Player* turn{ &p1 };

	// preparation

	dimensionSelect:
	int input = inputInt("Enter the dimension of the board [3-10] ");
	if (input < 3 || input > 10)
		goto dimensionSelect;

	const int dimension{ input };
	const int length{ dimension * dimension };

	char* visibleBoard = new char[length];
	for (int i = 0; i < length; ++i)
		visibleBoard[i] = Unknown;

	char* hiddenBoard = new char[length];
	for (int i = 0; i < length; ++i)
		hiddenBoard[i] = Empty;

	locateShips(hiddenBoard, length, p1.symbol, p2.symbol);

	do {

		header("Battleship");

		drawBoard(visibleBoard, dimension);
		bigDivision();

		processAttack(*turn, hiddenBoard, visibleBoard, getInput(visibleBoard, length, *turn));
		inputStr();

		winner = check(&p1, &p2, visibleBoard, length);
		if (winner) {
			drawBoard(visibleBoard, dimension);
			std::cout << "Game over! " << winner->name << " sank their opponent's fleet.\n";
		}

		turn = &(turn == &p1 ? p2 : p1);

	} while (!winner);

	info.loser = turn;
	info.winner = winner;

	delete[] hiddenBoard;
	delete[] visibleBoard;

	return info;

}