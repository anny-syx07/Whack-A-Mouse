#pragma once
#include<SDL.h>
#include "Mouse.h"

class Column{
public:
    int xtrai,xphai,ytren,yduoi;
    Column(int xtrai, int xphai, int ytren, int yduoi){
        this->xtrai=xtrai;
        this->xphai=xphai;
        this->ytren=ytren;
        this->yduoi=yduoi;
    };
    bool checkmouse(int x, int y){
        if(x>=xtrai&&x<=xphai&&y>=ytren&&y<=yduoi) return true;
        return false;
    }
    bool click=false;
    bool firsttime=false;
    int clickTime;
    bool playingAnimation;
};
