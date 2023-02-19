#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Window.h"
#include "sdl_text.h"

using namespace std;

void render_text(TTF_Font *font, SDL_Color color, char *text, Window window, int x, int y, int w, int h){
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_RenderCopy(window.getRenderer(), texture,NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

