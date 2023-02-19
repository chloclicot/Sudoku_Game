#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Window.h"
#include "sdl_text.h"
#include "color.h"
#include "Grid.h"
#include "jeux.h"
#include "chiffres.h"


using namespace std;

// Pour afficher les chiffres avec la grille de sudoku 
// adapté à une fenêtre de taille 128 par 720

//prends en paramètre le tableau qui contient les informations de la grille
//affiche tous les chiffres différents de 0 en noir dans la grille


void afficheChiffres4x4(Grid g,TTF_Font *font, Window window){

    char t[] = "0123456789ABCDEF";
    char l[] = "X";
    int i,j,c,x,y=110;


    for(j=0;j<4;j++){
        x = 90;
        for(i=0;i<4;i++){
            if(g.getCaseCube(i,j,0)==2){
                l[0] = t[g.getCase(i,j)];
                render_text(font, BLACK,l , window, y, x, 120, 120);
            }
            else if(g.getCaseCube(i,j,0)==1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, DARK_GRAY_BLUE,l , window, y, x, 120, 120);
            }
            else if(g.getCaseCube(i,j,0)==-1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, RED,l , window, y, x, 120, 120);
            }
            x = x + 139;
        }
        y = y + 140;
    }
}


void afficheChiffres9x9(Grid g,TTF_Font *font, Window window){
    char t[] = "0123456789ABCDEF";
    char l[] = "X";
    int i,j,c,y,x=107;

    for(j=0;j<9;j++){
        y = 90;
        for(i=0;i<9;i++){
            if(g.getCaseCube(i,j,0)==2){
                l[0] = t[g.getCase(i,j)];
                render_text(font, BLACK,l , window, x, y, 45, 50);
            }
            else if(g.getCaseCube(i,j,0)==1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, DARK_GRAY_BLUE,l , window, x, y, 45, 50);
            }
            else if(g.getCaseCube(i,j,0)==-1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, RED,l , window, x, y, 45, 50);
            }
            y = y + 60;
        }
        x = x + 60;
    }
}

void afficheChiffres16x16(Grid g,TTF_Font *font, Window window){
    char t[] = "0123456789ABCDEFG";
    char l[] = "X";
    int i,j,c,y,x=108;
    
    for(j=0;j<16;j++){
        y = 85;
        for(i=0;i<16;i++){
            if(g.getCaseCube(i,j,0)==2){
                l[0] = t[g.getCase(i,j)];
                render_text(font, BLACK,l , window, x, y, 20, 30);
            }
            else if(g.getCaseCube(i,j,0)==1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, DARK_GRAY_BLUE,l , window, x, y, 20, 30);
            }
            else if(g.getCaseCube(i,j,0)==-1){
                l[0] = t[g.getCase(i,j)];
                render_text(font, RED,l , window, x, y, 20, 30);
            }
            y = y + 35;
        }
        x = x + 35;
    }
}
