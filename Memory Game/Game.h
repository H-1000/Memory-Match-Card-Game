#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <chrono>

class Game {
private:
    Deck* deck;
    Player* player1;
    Player* player2;
    std::chrono::high_resolution_clock::time_point startTime;

public:
    Game(Deck* deck, Player* player1, Player* player2);
    ~Game();

    Player* getPlayer1() const;
    Player* getPlayer2() const;
    Deck* getDeck() const;
    void initializeGame();
    void endGame();
    Player* whoHasTheMostPoints() const;
    void playerTurn(Player*& currentPlayer, Player*& nextPlayer);
};

#endif