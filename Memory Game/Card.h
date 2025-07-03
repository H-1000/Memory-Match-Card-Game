#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
protected:
    int cardNo;
    bool facedUp;

public:
    Card(int cardNo = 0, bool facedUp = false) : cardNo(cardNo), facedUp(facedUp) {}
    virtual ~Card() {}

    void display() const;
    void setFacedUp(bool facedUp);
    int getCardNo() const;
    bool isFacedUp() const;
    void setCardNo(int cardNo);
    void revealCard();
    void hideCard();
    static bool matches(Card* card1, Card* card2);
    virtual int getPoints() const { return 0; }
};

#endif