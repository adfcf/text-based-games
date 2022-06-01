#include "games.h"
#include "info.h"
#include "player.h"
#include "misc.h"

#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <set>

constexpr char Unknown{ '-' };

constexpr int MaxWords = 30;

constexpr char words[][MaxWords]{
	"measurement",
	"recommendation",
	"employment",
	"childhood",
	"signature",
	"society",
	"perspective",
	"village",
	"imagination",
	"communication",
	"complaint",
	"possibility",
	"independence",
	"administration",
	"significance",
	"appearance",
	"economics",
	"hangman",
	"application",
	"maintenance",
	"consequence",
	"appointment",
	"distributable",
	"unconstitutionally",
	"inspector",
	"imagination",
	"description",
	"birthday",
	"environment",
	"temperature"
};

static bool isValid(char letter) {
	return (letter >= 'A' && letter <= 'Z');
}

static void drawWord(const std::string& known) {
	for (int i = 0; i < known.size(); ++i) {
		std::cout << ' ' << known.at(i) << ' ';
	}
	std::cout << "\n\n";
}

static char getInput(const Player& player) {

	char letter{};

	std::cout << player.name << ", pick a letter: ";

	if (isComputer(player)) {
		do {
			letter = (char) nextInteger('A', 'Z' + 1);
		} while (!isValid(letter));
		std::cout << letter << "\n";
	}
	else {
		do {
			letter = toupper(inputChar());
			if (!isValid(letter)) {
				std::cout << "Enter a valid letter which wasn't picked yet!\n";
			}
		} while (!isValid(letter));
	}

	return letter;

}

bool processLetter(std::string& known, const char* selectedWord, char letter) {
	bool atLeastOne{ false };
	for (int i = 0; i < known.size(); ++i) {
		if ((known[i] == Unknown) && (letter == toupper(selectedWord[i]))) {
			known[i] = letter;
			atLeastOne = true;
		}
	}
	return atLeastOne;
}

bool complete(const std::string& word) {
	for (auto c : word) {
		if (c == Unknown) 
			return false;
	}
	return true;
}

Info runHangman(const Player& firstPlayer, const Player& secondPlayer) {

	Info info{};

	const char* selectedWord = words[nextInteger(MaxWords)];

	std::string knownLetters{};
	for (int i = 0; i < std::strlen(selectedWord); ++i) {
		knownLetters.append(std::string{Unknown});
	}

	const Player* turn{ &firstPlayer };

	do {

		header("Hangman");
		drawWord(knownLetters);

		char input{ getInput(*turn) };
		if (processLetter(knownLetters, selectedWord, input)) {
			std::cout << "'" << input << "' is in this word.\n";
		}
		else {
			std::cout << "'" << input << "' is NOT in this word.\n";
		}

		drawWord(knownLetters);

		char yn{ (char) toupper(inputChar("Do you know the word? [Y/N] ")) };
		if (yn == 'Y') {
			auto word{ inputStr("Enter it: ")};
			if (word.compare(selectedWord) == 0) {

				std::cout << "Correct, the word was " << selectedWord << "! " << turn->name << " wins!\n";

				info.winner = turn;
				info.loser = (turn == &firstPlayer ? &secondPlayer : &firstPlayer);

				break;
			} else {

				turn = (turn == &firstPlayer ? &secondPlayer : &firstPlayer);
				std::cout << "Incorrect, the word was " << selectedWord << "! " << turn->name << " wins!\n";

				info.loser = turn;
				info.winner = (turn == &firstPlayer ? &secondPlayer : &firstPlayer);

				break;

			}
		}

		if (complete(knownLetters)) {
			std::cout << "It's a Draw\n";
			info.winner = nullptr;
			info.loser = nullptr;
			break;
		}

		turn = (turn == &firstPlayer ? &secondPlayer : &firstPlayer);

	} while (true);

	return info;

}