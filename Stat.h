#ifndef STAT_H
#define STAT_H
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class Stat{
public:
    int score;
    int lives;
    int mxscore;

    Stat(int initLives = 5);

    void reset();
    void addScore(int amount = 1);
    void loseLife();
    bool isGameOver() const;
    int getHighScore();
    void saveHighScore(const std::string& filename = "highscore.txt") const;
    void loadHighScore(const std::string& filename = "highscore.txt");
};
#endif
