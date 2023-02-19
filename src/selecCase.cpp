#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Window.h"
#include "Grid.h"
#include "chiffres.h"
#include "selecCase.h"

using namespace std;

void caseLocation4x4(int x, int y,int *ligne,int *colonne){
    *colonne = (x-100)/140;
    *ligne = (y-80)/140;
}

void selectionCase4x4(Window window,SDL_Renderer* render,SDL_Color fond,int ligne,int colonne){
    SDL_SetRenderDrawColor(render,fond.r-20,fond.g-20,fond.b-20,128);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_MUL);

    SDL_Rect vertical = {(colonne*140 +101),82,139,559};
    SDL_Rect horizontal = {101,(ligne*140 +82),559,139};

    SDL_RenderFillRect(render, &vertical);
    SDL_RenderFillRect(render,&horizontal);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
}

void caseLocation9x9(int x, int y,int *ligne,int *colonne){
       *colonne = (x-100)/60;
       *ligne = (y-80)/60;
}

void selectionCase9x9(Window window,SDL_Renderer* render,SDL_Color fond,int ligne,int colonne){
        SDL_SetRenderDrawColor(render,fond.r-20,fond.g-20,fond.b-20,120);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_MUL);

        SDL_Rect vertical = {(colonne*60 +101),82,59,539};
        SDL_Rect horizontal = {101,(ligne*60 +82),539,59};
    
        SDL_RenderFillRect(render, &vertical);
        SDL_RenderFillRect(render,&horizontal);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
}

void caseLocation16x16(int x, int y,int *ligne,int *colonne){
    *colonne = (x-100)/35;
    *ligne = (y-80)/35;
}


void selectionCase16x16(Window window,SDL_Renderer* render,SDL_Color fond,int ligne,int colonne){
        SDL_SetRenderDrawColor(render,fond.r-20,fond.g-20,fond.b-20,128);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_MUL);

        SDL_Rect vertical = {(colonne*35 +101),82,34,560};
        SDL_Rect horizontal = {101,(ligne*35 +81),560,34};
    
        SDL_RenderFillRect(render, &vertical);
        SDL_RenderFillRect(render,&horizontal);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);

}