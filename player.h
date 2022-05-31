#pragma once
#include <string>

struct Player {
	std::string name{};
	char symbol{ 0 };
	int id{ 0 };
	int victories{ 0 };
	int defeats{ 0 };
	int draws{ 0 };
};