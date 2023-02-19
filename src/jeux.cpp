//#include "sdl_text.h"
//#include "Window.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "jeux.h"
#include <iostream>

// adapté a une fenêtre 1280x720
// Avec les grosses cases délimitées

//Grille 4x4

/*
* Affiche une grille de sudoku de taille 4*4
* Avec le renderer en paramètre
*/
void jeu4x4(SDL_Renderer* renderer){
int i;
float x1,y1,x2,y2;
x1 = 100;
y1 = 80;

//lignes verticales x1 = x2
for(i=0;i<5;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1,640);
    if(i%2==0){
     SDL_RenderDrawLineF(renderer,x1+1,y1,x1+1,640);   
    }
    x1 = x1 + 140;
    }
x1 = 100;
y1 = 80;
// lignes horizontales y1 = y2
for(i=0;i<5;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1+560,y1);
    if(i%2==0){
    SDL_RenderDrawLineF(renderer,x1,y1+1,x1+560,y1+1);   
    }
    y1 = y1 + 140;
    }
}

//grille 9x9

/*
* Affiche une grille de sudoku de taille 9*9
* Avec le renderer en paramètre
*/
void jeu9x9(SDL_Renderer* renderer){
int i;
float x1,y1,x2,y2;
x1 = 100;
y1 = 80;

//lignes verticales x1 = x2
for(i=0;i<10;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1,620);
    if(i%3 == 0){
        SDL_RenderDrawLineF(renderer,x1+1,y1,x1+1,620);  
    }
    x1 = x1 + 60;
}
x1 = 100;
y1 = 80;
// lignes horizontales y1 = y2
for(i=0;i<10;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1+540,y1);
    if(i%3==0){
        SDL_RenderDrawLineF(renderer,x1,y1+1,x1+540,y1+1);   
    }
    y1 = y1 + 60;
}
}

// grille 16x16

/*
* Affiche une grille de sudoku de taille 16*16
* Avec le renderer en paramètre
*/
void jeu16x16(SDL_Renderer* renderer){
int i;
float x1,y1,x2,y2;
x1 = 100;
y1 = 80;

//lignes verticales x1 = x2
for(i=0;i<17;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1,640);
    if(i%4==0){
        SDL_RenderDrawLineF(renderer,x1+1,y1,x1+1,640);
    }
    x1 = x1 + 35;
    }
x1 = 100;
y1 = 80;
// lignes horizontales y1 = y2
for(i=0;i<17;i++){
    SDL_RenderDrawLineF(renderer,x1,y1,x1+560,y1);
    if(i%4==0){
        SDL_RenderDrawLineF(renderer,x1,y1+1,x1+560,y1+1);
    }
    y1 = y1 + 35;
    }
}