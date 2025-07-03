#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

void Card::display() const {
    if (facedUp) {
        if (dynamic_cast<const StandardCard*>(this)) {
            std::cout << " " << cardNo << " ";
        }

    } else {
        std::cout << " * ";
    }
}

void Card::setFacedUp(bool facedUp) {
    this->facedUp = facedUp;
}

int Card::getCardNo() const {
    return cardNo;
}

bool Card::isFacedUp() const {
    return facedUp;
}

void Card::setCardNo(int cardNo) {
    this->cardNo = cardNo;
}

void Card::revealCard() {
    facedUp = true;
}

void Card::hideCard() {
    facedUp = false;
}

bool Card::matches(Card* card1, Card* card2) {
    return card1->getCardNo() == card2->getCardNo();
}

void Deck::initializeCardPositions() {
    cardPositions.clear();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cardPositions[cards[i * 4 + j]] = std::make_pair(i, j);
        }
    }
}

Deck::Deck() : rng(std::random_device{}()) {
    for (int i = 1; i <= 6; ++i) {
        cards.push_back(new StandardCard(i, false));
        cards.push_back(new StandardCard(i, false));
    }
    cards.push_back(new BonusCard(7, false));
    cards.push_back(new BonusCard(7, false));
    cards.push_back(new PenaltyCard(8, false));
    cards.push_back(new PenaltyCard(8, false));
    initializeCardPositions();
}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
    initializeCardPositions();
}

void Deck::displayGrid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cards[i * 4 + j]->display();
        }
        std::cout << std::endl;
    }
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::removeCard(Card* card) {
    auto it = std::find(cards.begin(), cards.end(), card);
    if (it != cards.end()) {
        cards.erase(it);
        cardPositions.erase(card);
    }
}

Card* Deck::getCard(int x, int y) {
    for (const auto& pair : cardPositions) {
        if (pair.second == std::make_pair(x, y)) {
            return pair.first;
        }
    }
    return nullptr;
}

std::pair<int, int> Deck::getCardPosition(Card* card) const {
    return cardPositions.at(card);
}

Player::Player(const std::string& name) : name(name), score(0) {}

int Player::displayScore() const {
    return score;
}

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& name) {
    this->name = name;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
}

void Player::plusScore(int points) {
    score += points;
}

void Player::minusScore(int points) {
    score -= points;
}

int Player::choose(int lower, int higher) const {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < lower || choice > higher) {
            std::cout << "Invalid input. Please enter a number between " << lower << " and " << higher << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

Game::Game(Deck* deck, Player* player1, Player* player2) : deck(deck), player1(player1), player2(player2) {
    startTime = std::chrono::high_resolution_clock::now();
}

Game::~Game() {
    delete deck;
    delete player1;
    delete player2;
}

Player* Game::getPlayer1() const {
    return player1;
}

Player* Game::getPlayer2() const {
    return player2;
}

Deck* Game::getDeck() const {
    return deck;
}

void Game::initializeGame() {
    deck->shuffle();
    std::cout << "Initial Grid:" << std::endl;
    deck->displayGrid();
    while (!deck->isEmpty()) {
        playerTurn(player1, player2);
        if (!deck->isEmpty()) {
            playerTurn(player2, player1);
        }
    }
    endGame();
}

void Game::endGame() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    std::cout << "Game Over!" << std::endl;
    Player* winner = whoHasTheMostPoints();
    if (winner == nullptr) {
        std::cout << "It's a tie!" << std::endl;
    } else {
        std::cout << winner->getName() << " wins with a score of " << winner->getScore() << "!" << std::endl;
    }
    std::cout << "Game duration: " << duration << " seconds" << std::endl;
}

Player* Game::whoHasTheMostPoints() const {
    if (player1->getScore() > player2->getScore()) {
        return player1;
    } else if (player2->getScore() > player1->getScore()) {
        return player2;
    } else {
        return nullptr;
    }
}

void Game::playerTurn(Player*& currentPlayer, Player*& nextPlayer) {
    std::cout << currentPlayer->getName() << ", it's your turn." << std::endl;
    std::cout << "Enter the coordinates of the first card (x y): ";
    int x1, y1;
    x1 = currentPlayer->choose(0, 3);
    y1 = currentPlayer->choose(0, 3);

    Card* card1 = deck->getCard(x1, y1);
    while (card1->isFacedUp()) {
        std::cout << "Card already face up. Choose another card: ";
        x1 = currentPlayer->choose(0, 3);
        y1 = currentPlayer->choose(0, 3);
        card1 = deck->getCard(x1, y1);
    }

    card1->revealCard();
    deck->displayGrid();

    std::cout << "Enter the coordinates of the second card (x y): ";
    int x2, y2;
    x2 = currentPlayer->choose(0, 3);
    y2 = currentPlayer->choose(0, 3);

    Card* card2 = deck->getCard(x2, y2);
    while (card2 == card1 || card2->isFacedUp()) {
        std::cout << "Invalid choice. Choose another card: ";
        x2 = currentPlayer->choose(0, 3);
        y2 = currentPlayer->choose(0, 3);
        card2 = deck->getCard(x2, y2);
    }

    card2->revealCard();
    deck->displayGrid();

    if (Card::matches(card1, card2)) {
        if (dynamic_cast<BonusCard*>(card1) && dynamic_cast<BonusCard*>(card2)) {
            std::cout << "You matched two bonus cards! Press 1 for +2 points, 2 for +1 point and another turn: ";
            int choice = currentPlayer->choose(1, 2);
            if (choice == 1) {
                currentPlayer->plusScore(2);
            } else {
                currentPlayer->plusScore(1);
                deck->removeCard(card1);
                deck->removeCard(card2);
                std::cout << "Score: " << currentPlayer->displayScore() << std::endl;
                playerTurn(currentPlayer, nextPlayer);
                return;
            }
        } else if (dynamic_cast<PenaltyCard*>(card1) && dynamic_cast<PenaltyCard*>(card2)) {
            std::cout << "You matched two penalty cards! Press 1 for -2 points, 2 for -1 point and skip next turn: ";
            int choice = currentPlayer->choose(1, 2);
            if (choice == 1) {
                currentPlayer->minusScore(2);
            } else {
                currentPlayer->minusScore(1);
                deck->removeCard(card1);
                deck->removeCard(card2);
                std::cout << "Score: " << currentPlayer->displayScore() << std::endl;
                return;
            }
        } else {
            currentPlayer->plusScore(card1->getPoints());
        }
        deck->removeCard(card1);
        deck->removeCard(card2);

        std::cout << "Score: " << currentPlayer->displayScore() << std::endl;
        if (!deck->isEmpty()) {
            playerTurn(currentPlayer, nextPlayer);
        }
    } else {
        if (dynamic_cast<BonusCard*>(card1) && dynamic_cast<PenaltyCard*>(card2)) {
            deck->removeCard(card1);
            deck->removeCard(card2);
        } else if (dynamic_cast<BonusCard*>(card2) && dynamic_cast<PenaltyCard*>(card1)) {
            deck->removeCard(card1);
            deck->removeCard(card2);
        } else if (dynamic_cast<BonusCard*>(card1)) {
            currentPlayer->plusScore(card1->getPoints());
            deck->removeCard(card1);
        } else if (dynamic_cast<BonusCard*>(card2)) {
            currentPlayer->plusScore(card2->getPoints());
            deck->removeCard(card2);
        } else if (dynamic_cast<PenaltyCard*>(card1)) {
            currentPlayer->minusScore(card1->getPoints());
        } else if (dynamic_cast<PenaltyCard*>(card2)) {
            currentPlayer->minusScore(card2->getPoints());
        }

        std::cout << "Score: " << currentPlayer->displayScore() << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        card1->hideCard();
        card2->hideCard();
        deck->displayGrid();
    }
}

int main() {
    Deck* deck = new Deck();
    Player* player1 = new Player("Hamid");
    Player* player2 = new Player("Saka");
    Game game(deck, player1, player2);
    game.initializeGame();

    return 0;
}