#ifndef STANDARDCARD_H
#define STANDARDCARD_H

#include "Card.h"

class StandardCard : public Card {
public:
    StandardCard(int cardNo, bool facedUp = false) : Card(cardNo, facedUp) {}
    int getPoints() const override { return 1; }
};

#endif