#include <SDL2/SDL_ttf.h>
#include <SDL.h>
#include <iostream>
#include "Window.h"

using namespace std;

Window::Window(char *name, int width, int height){
    this->width = width;
    this->height = height;
    self = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, width,height, 0);
    renderer = SDL_CreateRenderer(self,-1, 0);
    if ((self == NULL) || (renderer == NULL)) {
        cout <<  "could not create window: %s\n" << SDL_GetError() << endl;
    }
}

void Window::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(self);
}

void Window::render(){
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer(){
    return renderer;
}

SDL_Window* Window::getSelf(){
    return self;
}

SDL_Event Window::getEvent(){
    return event;
}

SDL_Event* Window::getEventPointer(){
    return &event;
}