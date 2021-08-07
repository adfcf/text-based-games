#pragma once

#include "player.h"
#include "info.h"

Info runTicTacToe(const Player* const firstPlayer, const Player* const secondPlayer);

Info runBattleship(const Player* const firstPlayer, const Player* const secondPlayer);

Info runHangman(const Player* const firstPlayer, const Player* const secondPlayer);

Info runGuess(const Player* const firstPlayer, const Player* const secondPlayer);

Info runMinesweeper(const Player* const player);

Info runDungeon(const Player* const player);

Info runWhatIsMyAge(const Player* const player);

Info runSnake(const Player* const player);