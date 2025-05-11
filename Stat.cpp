#include "Stat.h"
#include<fstream>

Stat::Stat(int initLives) {
    score = 0;
    lives = initLives;
    mxscore=0;
}

void Stat::reset() {
    score = 0;
    lives = 5;
}

void Stat::addScore(int amount) {
    score += amount;
}

void Stat::loseLife() {
    lives--;
}

bool Stat::isGameOver() const {
    return lives <= 0;
}

int Stat::getHighScore() {
    if(mxscore<score){
        mxscore=score;
    }
    return mxscore;
}

void Stat::saveHighScore(const std::string& filename) const {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << mxscore;
        out.close();
    }
}

void Stat::loadHighScore(const std::string& filename) {
    std::ifstream in(filename);
    if (in.is_open()) {
        in >> mxscore;
        in.close();
    } else {
        mxscore = 0;
    }
}
