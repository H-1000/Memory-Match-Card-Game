#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <limits>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& name = "");
    ~Player() {}

    int displayScore() const;
    std::string getName() const;
    void setName(const std::string& name);
    int getScore() const;
    void setScore(int newScore);
    void plusScore(int points);
    void minusScore(int points);
    int choose(int lower, int higher) const;
};

#endif