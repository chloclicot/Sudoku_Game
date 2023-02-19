#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "src/jeux.h"
#include "src/Window.h"
#include "src/Grid.h"
#include "src/Historic.h"
#include "src/extraireGrille.h"
#include "src/mainpage.h"
#include "src/accueil.h"



int main(){

    SDL_Init(0);
    TTF_Init();
    Grid g;
    char *a = accueil_window();
    cout << a << endl;
    int tg = (int) a[0];
    if(tg==52){
        cout << "generating 4x4...";
        g.generate(2,a[2]-40);
        cout << "done !" << endl;
    }
    else if(tg==57){
        cout << "generating 9x9...";
        cout << 41-(5*(a[2]-49)) << "...";
        g.generate(3,41-(5*(a[2]-49)));
        cout << "done !" << endl;
    }
    else{
        cout << "Loading from file..." << endl;
        int tab[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE],t;
        extraire(a,tab,&t);
        g = Grid(tab,t);
        g.calculate();
        cout << "done !" << endl;
    }

    cout << "lauching mainpage" << endl;
    mainpage(g);

    TTF_Quit();
    SDL_Quit();

    return 0;
}