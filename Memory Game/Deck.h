#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
#include <vector>
#include <map>
#include <algorithm>
#include <random>

class Deck {
private:
    std::vector<Card*> cards;
    std::map<Card*, std::pair<int, int>> cardPositions;
    std::mt19937 rng;

    void initializeCardPositions();

public:
    Deck();
    ~Deck();

    void shuffle();
    void displayGrid() const;
    bool isEmpty() const;
    void removeCard(Card* card);
    Card* getCard(int x, int y);
    std::pair<int, int> getCardPosition(Card* card) const;
};

#endif