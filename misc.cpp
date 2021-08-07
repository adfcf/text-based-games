#include "misc.h"

#include <iostream>
#include <cstdlib>

void seed() {
	std::srand(std::time(nullptr));
}

int inputInt(const char* message) {
	int input;
	std::cout << message;
	std::cin >> input;
	return input;
}

int inputInt() {
	return inputInt("");
}

char inputChar(const char* message) {
	char input;
	std::cout << message;
	std::cin >> input;
	return input;
}

char inputChar() {
	return inputChar("");
}

std::string inputStr(const char* message) {
	std::string input;
	std::cout << message;
	std::cin >> input;
	return input;
}

std::string inputStr() {
	return inputStr("");
}

bool isComputer(const Player* const player) {
	return (player->id == 0);
}

int nextInteger(int inclusiveMin, int exclusiveMax) {
	return inclusiveMin + (std::rand() % (exclusiveMax - inclusiveMin));
}

int nextInteger(int exclusiveMax) {
	return nextInteger(0, exclusiveMax);
}

void smallDivision() {
	std::cout << "-----------------\n";
}

void bigDivision() {
	std::cout << "----------------------------------\n";
}

void biggestDivision() {
	std::cout << "--------------------------------------------------------------------\n";
}

void clearScreen() {
	std::system("cls");
}

void notYet() {
	std::cout << "Not Implemented Yet!\n";
}
