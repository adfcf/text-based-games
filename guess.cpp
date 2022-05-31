#include "games.h"
#include "info.h"
#include "player.h"
#include "misc.h"

#include <iostream>

// Guess game loop controller
Info runGuess(const Player& firstPlayer, const Player& secondPlayer) {

	Info info{ nullptr, nullptr };

	header("Guess");

	const int a{ inputInt("Choose 'a': ") };
	const int b{ inputInt("Choose 'b': ") };

	const int number{ nextInteger(a, b) };
	std::cout << "\n- It was picked an integer number between " << a << " and " << b << ". Who guesses it first wins!\n\n";

	const Player* turn{ &firstPlayer };
	int guess{};

	do {

		std::cout << turn->name << ", your guess: ";
		if (!isComputer(*turn)) {
			guess = inputInt();
		} else {
			guess = nextInteger(a, b);
			std::cout << guess << '\n';
		}

		if (guess > number) {
			std::cout << "it's a bit smaller...\n\n";
		} else if (guess < number) {
			std::cout << "it's a bit bigger...\n\n";
		} else {

			std::cout << "THAT'S RIGHT! IT'S " << number << "\n";
			std::cout << turn->name << " wins!\n";
			bigDivision();

			info.winner = turn;
			info.loser = &((turn == &firstPlayer) ? secondPlayer : firstPlayer);

			break;

		}

		turn = &((turn == &firstPlayer) ? secondPlayer : firstPlayer);

	} while (true);

	return info;

}