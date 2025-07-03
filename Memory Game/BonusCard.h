#ifndef BONUSCARD_H
#define BONUSCARD_H

#include "Card.h"

class BonusCard : public Card {
public:
    BonusCard(int cardNo, bool facedUp = false) : Card(cardNo, facedUp) {}
    int getPoints() const override { return 1; }
};

#endif