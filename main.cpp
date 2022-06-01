#include "misc.h"
#include "player.h"
#include "info.h"
#include "games.h"

#include <cctype>
#include <iostream>
#include <vector>

enum class Game {
    TicTacToe,
    Battleship,
    Hangman,
    Guess,
    None
};

static void header() {
    clearScreen();
    biggestDivision();
    std::cout << "TEXT-BASED GAMES!\n";
    biggestDivision();
}

static int availableGames() {
    return static_cast<int>(Game::None);
}

static Game getUserGamePick() {

    int pick{ static_cast<int>(Game::None) };
    do {

        std::cout << "Which game do you want to play?\n\n";
        std::printf("[%d] - Tic Tac Toe\n", Game::TicTacToe);
        std::printf("[%d] - Battleship\n", Game::Battleship);
        std::printf("[%d] - Hangman\n", Game::Hangman);
        std::printf("[%d] - Guess\n", Game::Guess);
        std::printf("[%d] - None\n", Game::None);

        pick = inputInt();

    } while (pick < 0 || pick > static_cast<int>(Game::None));

    return static_cast<Game>(pick);

}

static void registerPlayers(std::vector<Player>& registeredPlayers) {

    char morePlayersNeeded{ 'N'};
    char symbol{ ' ' };
    int playerIndex{ 1 };

    std::string nickname;
    do {

        std::cout << "Enter the nickname of the player " << playerIndex << ": ";
        nickname = inputStr();
        std::cout << "Choose a default symbol for " << nickname << ": ";
        symbol = inputChar();
        registeredPlayers.push_back(Player{ nickname, symbol, playerIndex++ });

        std::cout << "Done? [Y/N] ";
        morePlayersNeeded = inputChar();

    } while (std::toupper(morePlayersNeeded) != 'Y');

    bigDivision();

}

static void showRegisteredPlayers(const std::vector<Player>& registeredPlayers) {

    std::cout << "Players who were registered:\n";

    for (const auto& player : registeredPlayers) {
        std::cout << player.id << ". " << player.name << "\n";
    }

    bigDivision();

}

static Player& selectPlayer(std::vector<Player>& registeredPlayers) {

    showRegisteredPlayers(registeredPlayers);
    int selectedPlayer{ 0 };

    do {

        std::printf("Choose one [0-%d]: ", static_cast<int>(registeredPlayers.size() - 1));
        selectedPlayer = inputInt();
    
    } while (selectedPlayer < 0 || selectedPlayer >= registeredPlayers.size());

    std::cout << registeredPlayers.at(selectedPlayer).name << " has been selected!\n";
    bigDivision();

    return registeredPlayers.at(selectedPlayer);

}

int main() {

    std::vector<Player> registeredPlayers;
    seed();

    header();

    registeredPlayers.push_back(Player{ "Computer", 'C', 0});

    registerPlayers(registeredPlayers);
    showRegisteredPlayers(registeredPlayers);

    bool playedOneGame{ false };
    char oneMoreGame{ 'N' };
    do {

        Game gamePick{ getUserGamePick() };
        clearScreen();

        switch (gamePick) {
        case Game::TicTacToe:
            std::cout << "TIC TAC TOE selected! Now choose the players who are going to play.\n";
            bigDivision();
            runTicTacToe(selectPlayer(registeredPlayers), selectPlayer(registeredPlayers));
            playedOneGame = true;
            break;
        case Game::Battleship:
            std::cout << "BATTLESHIP selected! Now choose the players who are going to play.\n";
            bigDivision();
            runBattleship(selectPlayer(registeredPlayers), selectPlayer(registeredPlayers));
            playedOneGame = true;
            break;
        case Game::Guess:
            std::cout << "GUESS selected! Now choose the players who are going to play.\n";
            bigDivision();
            runGuess(selectPlayer(registeredPlayers), selectPlayer(registeredPlayers));
            playedOneGame = true;
            break;
        case Game::Hangman:
            std::cout << "HANGMAN selected! Now choose the players who are going to play.\n";
            bigDivision();
            runHangman(selectPlayer(registeredPlayers), selectPlayer(registeredPlayers));
            playedOneGame = true;
            break;
        }

        if (playedOneGame)
            oneMoreGame = inputChar("Do you want to play another game? [Y/N]\n");

    } while (std::toupper(oneMoreGame) == 'Y');

    std::cout << "Goodbye!\n";
    return 0;

}

