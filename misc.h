#pragma once
#include "player.h"

// Random numbers
int nextInteger(int inclusiveMin, int exclusiveMax);
int nextInteger(int exclusiveMax);
void seed();

// User input
int inputInt(const char* message);
int inputInt();
char inputChar(const char* message);
char inputChar();
std::string inputStr(const char* message);
std::string inputStr();

// Screen related
void header(const char* gameName);
void smallDivision();
void bigDivision();
void biggestDivision();
void clearScreen();

// Other
bool isComputer(const Player* const player);
void notYet();

