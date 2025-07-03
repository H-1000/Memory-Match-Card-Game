#ifndef PENALTYCARD_H
#define PENALTYCARD_H

#include "Card.h"

class PenaltyCard : public Card {
public:
    PenaltyCard(int cardNo, bool facedUp = false) : Card(cardNo, facedUp) {}
    int getPoints() const override { return -1; }
};

#endif