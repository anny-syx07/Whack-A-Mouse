#pragma once
#include<SDL.h>
class Mouse
{
public:
    int col;
    int y;
    int speed;
    SDL_Texture* texsong;
    SDL_Texture* texchet;
    bool song;
    bool visible;
    Mouse(int col, int y, int speed, SDL_Texture* texsong, SDL_Texture* texchet,bool song, bool visible){
        this->col=col;
        this->y=y;
        this->speed=speed;
        this->texchet=texchet;
        this->texsong=texsong;
        this->song=song;
        this->visible=visible;
    };
};
