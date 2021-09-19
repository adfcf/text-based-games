#include "games.h"
#include "info.h"
#include "player.h"
#include "misc.h"

#include <iostream>

// Header of the game. It prints every time the game is updated.
static void header() {
	clearScreen();
	std::cout << "Tic Tac Toe\n";
	bigDivision();
}

// Battleship game loop and main controller
Info runBattleship(const Player* const p1, const Player* const p2) {

	Info info{ nullptr, nullptr };

	const Player* winner{ nullptr };
	const Player* turn{ p1 };

	do {

		header();

		turn = (turn == p1 ? p2 : p1);

	} while (true);

	return info;

}