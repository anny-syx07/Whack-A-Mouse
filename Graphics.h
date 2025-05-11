#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include<SDL_mixer.h>
#include<SDL_ttf.h>


struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;
	Mix_Music *gMusic;
	Mix_Chunk *gChunk;
	void logErrorAndExit(const char* msg, const char* error);
	void init();
	void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    Mix_Music *loadMusic(const char* path);
    void toggle(Mix_Music *gMusic);
    Mix_Chunk *loadChunk(const char* path);
    TTF_Font *loadFont(const char* path, int size);
    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);
    void quit();
};

#endif // _GRAPHICS__H

