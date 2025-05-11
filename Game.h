#pragma once
#include<SDL.h>
#include<bits/stdc++.h>
#include "Column.h"
#include "Graphics.h"
#include "State.h"
#include "Stat.h"
using namespace std;

class Game{
public:
    Stat stat;
    State curState = State::StartScreen;
    void run();
    void init();
    void handleEvents();
    void update();
    void cleanUp();
    void resetGame();
    void spawnMouseIfNeeded();
    void updateSlider();
    void updateMusic();
    bool soundEnabled = true;
    int xBasechuot[4];
    int xBasemeo[4];
    int x,y;
    SDL_Event e;
    int newGame=true;
    bool clicked=false;
    int spawnInterval=2000;
    int idx=1;
private:
    Graphics graphics;
    SDL_Event event;
    Mix_Music *gMusic1;
    Mix_Music *gMusic2;
    Mix_Music *gMusic3;
    Mix_Music *gMusic;
    Mix_Chunk *hup;
    Mix_Chunk *meow;
    Mix_Chunk *pop;

    SDL_Texture* background ;
    SDL_Texture* playTexture;
    SDL_Texture *playagain;
    SDL_Texture* boardTexture;
    SDL_Texture* meodungyen;
    SDL_Texture* info;
    SDL_Texture* meodap ;
    SDL_Texture *diemmeo;
    SDL_Texture *diemchuot;
    SDL_Texture *huongdan;
    SDL_Texture* cursorvl;
    SDL_Texture* cursorsfx;
    SDL_Texture* sets;
    SDL_Texture* menuset;
    SDL_Texture* mzopt;
    SDL_Texture* option;


    TTF_Font *welcome;
    TTF_Font *gover;
    TTF_Font *diem;
    TTF_Font *opt;

    SDL_Color color={128,0,0,0};
    SDL_Color diemm={46,8,84,0};
    SDL_Texture *hello;
    SDL_Texture *hellodongduoi;
    SDL_Texture *gameover;
    SDL_Texture *yourscore;
    SDL_Texture *highscore;
    SDL_Texture* pausebutton;
    SDL_Texture* menupause;
    SDL_Texture* volume;
    SDL_Texture* sfx;
    SDL_Texture* volumebar;
    SDL_Texture* tick;

    TTF_Font *ingame;
    SDL_Color baby={255,0,0,0};
    vector<Column> cot = {
        Column(100, 170, 350, 800),
        Column(175, 240, 350, 800),
        Column(241, 313, 350, 800),
        Column(314, 390, 350, 800)
    };
    Column nutBatDau=Column(100, 400, 550, 638);
    Column nutInfo=Column(10, 60, 20, 70);
    Column tatInfo=Column(360,400,200,250);
    Column nutPlayAgain=Column(100,400,550,638);
    Column nutPause=Column(400,450,10,60);
    Column nutResume=Column(150,300,480,540);
    Column nutHome=Column(150,300,570,630);
    Column vlbar=Column(90,362,280,300);
    Column sfxbar=Column(90,362,390,410);
    Column nutSet=Column(400,450,10,55);
    Column m1=Column(150,170,500,520);
    Column m2=Column(250,270,500,520);
    Column m3=Column(380,400,500,520);
    bool isRunning=true;
    int lastSpawnTime=0;
    SDL_Texture* anhsong[4];
    SDL_Texture* anhchet[4];

    vector<Mouse>mouse;
};
