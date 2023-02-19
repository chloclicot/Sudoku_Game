#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "jeux.h"
#include "Window.h"
#include "Grid.h"
#include "Historic.h"
#include "color.h"
#include "chiffres.h"
#include "mainpage.h"
#include "selecCase.h"
#include "menuContext.h"


using namespace std;


int mainpage(Grid grid){

    Window window = Window((char*) "GRILLE",SCREEN_WIDTH,SCREEN_HEIGHT); // création de la fenetre

    grid.calculate();
    grid.dispgrid();

    cout << "MAINPAGE : " << grid.getlength() << endl;

    cout << endl << endl;
    switch(grid.getlength()){
        case 4 :
            partie4(&window,grid);
            break;
        case 9 :
            partie9(&window,grid);
            break;
        case 16 :
            partie16(&window,grid);
            break;
    }

    grid.dispgrid();

    window.destroy();
    return 0;
}

int partie4(Window* window,Grid grid){
    bool exit = false; // variable de sortie de la boucle d'event
    int ligne = 0;
    int colonne = 0;
    int x,y,key;
    int index = 0;
    int tab[3];
    Historic h;
    h.update(0,&grid);
    bool menustate = 0;
    TTF_Font * font = TTF_OpenFont("assets/BebasNeue-Regular.ttf", 100);

    while(exit == false){
        SDL_SetRenderDrawColor(window->getRenderer(),255, 200, 200,SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(window->getRenderer(), NULL);
        //Affichage de la grille
        SDL_SetRenderDrawColor(window->getRenderer(),100,60, 60,SDL_ALPHA_OPAQUE);
        jeu4x4(window->getRenderer());
        afficheChiffres4x4(grid,font,*(window));
        SDL_SetRenderDrawColor(window->getRenderer(),LIGHT_PINK.r, LIGHT_PINK.g, LIGHT_PINK.b,SDL_ALPHA_OPAQUE);
        selectionCase4x4(*window,window->getRenderer(),LIGHT_PINK,ligne,colonne);
        if(menustate) OpenMenu(*window,window->getRenderer(),MEDIUM_PINK,font);
        fenetreMenu(*window, window->getRenderer(), MEDIUM_PINK, font);
        SDL_Delay(8); // effectue la boucle toute les 8ms
        window->render();
        if (SDL_PollEvent(window->getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(window->getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                case SDL_MOUSEBUTTONUP :
                    if(window->getEvent().button.button == SDL_BUTTON_LEFT){
                        x=window->getEvent().button.x;
                        y=window->getEvent().button.y;
                        if(menustate){
                            if((x > 0 && x < 276 && y >= 176) || (x>276 && y >=30)) menustate = false;
                            else if(y > 32 && y < 68){
                                exit = true;
                            }
                            else if(y > 68 && y < 104){
                                grid.solve_advice(tab);
                                grid.addValueToCase(tab[0],tab[1],tab[2]);
                                h.update(index,&grid);
                                index = 0;
                                menustate = false;
                            }
                            else if(y > 104 && y < 140 ){
                                if(index < h.getNSave()-1){
                                    index ++;
                                    grid = h.getSave(index);
                                }
                                menustate = false;
                            }
                            else if(y > 140 && y < 176 ){
                                if(index > 0){
                                    index --;
                                    grid = h.getSave(index);
                                }
                                menustate = false;
                            }
                        }
                        else{
                            if(x>100 && x<660 && y> 80 && y<620){
                                caseLocation4x4(x,y,&ligne,&colonne);
                            }
                            else if (x >= 10 && x<= 41 && y >= 7 && y <= 25 ){
                                menustate = true; 
                            }
                        }
                    }
                    break;
                case SDL_KEYUP :
                    key = window->getEvent().key.keysym.sym;
                    if(!menustate){
                        if(key==SDLK_BACKSPACE){
                            grid.addValueToCase(ligne,colonne,0);
                            h.update(index,&grid);
                            index = 0;
                        }
                        if((key>47 && key<53) && grid.getCaseCube(ligne,colonne,0)!=2){
                            grid.addValueToCase(ligne,colonne,key-48);
                            h.update(index,&grid);
                            index = 0;
                        }
                        else if(key==SDLK_z){
                            if(index < h.getNSave()-1){
                                index ++;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key==SDLK_y){
                            if(index > 0){
                                index --;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key == SDLK_h){
                            grid.solve_advice(tab);
                            grid.addValueToCase(tab[0],tab[1],tab[2]);
                            h.update(index,&grid);
                            index = 0;
                        }
                    }
            }
        }
    }
    TTF_CloseFont(font);
    return 0;
}

int partie9(Window* window,Grid grid){
    bool exit = false;
    int ligne = 0;
    int colonne = 0;
    int x,y,key;
    int index = 0;
    int tab[3];
    Historic h;
    h.update(0,&grid);
    bool menustate = false;
    
    TTF_Font * font = TTF_OpenFont("assets/BebasNeue-Regular.ttf", 100);

    while(exit == false){
        SDL_SetRenderDrawColor(window->getRenderer(),255, 200, 200,SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(window->getRenderer(), NULL);
        //Affichage de la grille
        SDL_SetRenderDrawColor(window->getRenderer(),100,60, 60,SDL_ALPHA_OPAQUE);
        jeu9x9(window->getRenderer());
        afficheChiffres9x9(grid,font,*(window));
        afficheChiffres9x9(grid,font,*(window));
        SDL_SetRenderDrawColor(window->getRenderer(),LIGHT_PINK.r, LIGHT_PINK.g, LIGHT_PINK.b,SDL_ALPHA_OPAQUE);
        selectionCase9x9(*window,window->getRenderer(),LIGHT_PINK,ligne,colonne);
        if(menustate) OpenMenu(*window,window->getRenderer(),MEDIUM_PINK,font);
        fenetreMenu(*window, window->getRenderer(), MEDIUM_PINK, font);
        SDL_Delay(8); // effectue la boucle toute les 16ms
        window->render();
        if (SDL_PollEvent(window->getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(window->getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                case SDL_MOUSEBUTTONUP :
                    if(window->getEvent().button.button == SDL_BUTTON_LEFT){
                        x=window->getEvent().button.x;
                        y=window->getEvent().button.y;
                        if(menustate){
                            if((x > 0 && x < 276 && y >= 176) || (x>276 && y >=30)) menustate = false;
                            else if(y > 32 && y < 68){
                                exit = true;
                            }
                            else if(y > 68 && y < 104){
                                grid.solve_advice(tab);
                                grid.addValueToCase(tab[0],tab[1],tab[2]);
                                h.update(index,&grid);
                                index = 0;
                                menustate = false;
                            }
                            else if(y > 104 && y < 140 ){
                                if(index < h.getNSave()-1){
                                    index ++;
                                    grid = h.getSave(index);
                                }
                                menustate = false;
                            }
                            else if(y > 140 && y < 176 ){
                                if(index > 0){
                                    index --;
                                    grid = h.getSave(index);
                                }
                                menustate = false;
                            }
                        }
                        else{
                            if(x>100 && x<720 && y> 80 && y<700){
                                caseLocation9x9(x,y,&ligne,&colonne);
                            }
                            else if (x >= 10 && x<= 41 && y >= 7 && y <= 25 ){
                                menustate = true; 
                            }
                        }
                    }
                    break;
                case SDL_KEYUP :
                    key = window->getEvent().key.keysym.sym;
                    if(!menustate){
                        if(key==SDLK_BACKSPACE){
                            grid.addValueToCase(ligne,colonne,0);
                            h.update(index,&grid);
                            index = 0;
                        }
                        if((key>47 && key<58) && grid.getCaseCube(ligne,colonne,0)!=2){
                            grid.addValueToCase(ligne,colonne,key-48);
                            h.update(index,&grid);
                            index = 0;
                        }
                        else if(key==SDLK_z){
                            if(index < h.getNSave()-1){
                                index ++;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key==SDLK_y){
                            if(index > 0){
                                index --;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key == SDLK_h){
                            grid.solve_advice(tab);
                            grid.addValueToCase(tab[0],tab[1],tab[2]);
                            h.update(index,&grid);
                            index = 0;
                        }
                    }
            }
        }
    }
    TTF_CloseFont(font);
    return 0;
}

int partie16(Window* window,Grid grid){
    bool exit = false; // variable de sortie de la boucle d'event
    int ligne = 0;
    int colonne = 0;
    int x,y,key;
    int index = 0;
    int tab[3];
    Historic h;
    h.update(0,&grid);
    int menustate = false;
    // Ouverture d'une police d'ecriture
        // Rendu du fond blanc de la fenêtre
    
    TTF_Font * font = TTF_OpenFont("assets/BebasNeue-Regular.ttf", 100);

    while(exit == false){
        SDL_SetRenderDrawColor(window->getRenderer(),255, 200, 200,SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(window->getRenderer(), NULL);
        //Affichage de la grille
        SDL_SetRenderDrawColor(window->getRenderer(),100,60, 60,SDL_ALPHA_OPAQUE);
        jeu16x16(window->getRenderer());
        afficheChiffres16x16(grid,font,*(window));
        SDL_SetRenderDrawColor(window->getRenderer(),LIGHT_PINK.r, LIGHT_PINK.g, LIGHT_PINK.b,SDL_ALPHA_OPAQUE);
        selectionCase16x16(*window,window->getRenderer(),LIGHT_PINK,ligne,colonne);
        if(menustate) OpenMenu(*window,window->getRenderer(),MEDIUM_PINK,font);
        fenetreMenu(*window, window->getRenderer(), MEDIUM_PINK, font);
        SDL_Delay(8); // effectue la boucle toute les 16ms
        window->render();
        if (SDL_PollEvent(window->getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(window->getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                case SDL_MOUSEBUTTONUP :
                    x=window->getEvent().button.x;
                    y=window->getEvent().button.y;
                    if(menustate){
                        if((x > 0 && x < 276 && y >= 176) || (x>276 && y >=30)) menustate = false;
                        else if(y > 32 && y < 68){
                            exit = true;
                        }
                        else if(y > 68 && y < 104){
                            grid.solve_advice(tab);
                            grid.addValueToCase(tab[0],tab[1],tab[2]);
                            h.update(index,&grid);
                            index = 0;
                            menustate = false;
                        }
                        else if(y > 104 && y < 140 ){
                            if(index < h.getNSave()-1){
                                index ++;
                                grid = h.getSave(index);
                            }
                            menustate = false;
                        }
                        else if(y > 140 && y < 176 ){
                            if(index > 0){
                                index --;
                                grid = h.getSave(index);
                            }
                            menustate = false;
                        }
                    }
                    else{
                        if(x>100 && x<720 && y> 80 && y<700){
                            caseLocation16x16(x,y,&ligne,&colonne);
                        }
                        else if (x >= 10 && x<= 41 && y >= 7 && y <= 25 ){
                                menustate = true; 
                        }
                    }
                    break;
                case SDL_KEYUP :
                    key = window->getEvent().key.keysym.sym;
                    if(!menustate){
                        if(key==SDLK_BACKSPACE){
                            grid.addValueToCase(ligne,colonne,0);
                            h.update(index,&grid);
                            index = 0;
                        }
                        if((key>47 && key<58) && grid.getCaseCube(ligne,colonne,0)!=2){
                            grid.addValueToCase(ligne,colonne,key-48);
                            h.update(index,&grid);
                            index = 0;
                        }
                        else if(key>96 && key<104){
                            grid.addValueToCase(ligne,colonne,key-87);
                            h.update(index,&grid);
                            index = 0;
                        }
                        else if(key==SDLK_z){
                            if(index < h.getNSave()-1){
                                index ++;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key==SDLK_y){
                            if(index > 0){
                                index --;
                                grid = h.getSave(index);
                            }
                        }
                        else if(key == SDLK_h){
                            grid.solve_advice(tab);
                            grid.addValueToCase(tab[0],tab[1],tab[2]);
                            h.update(index,&grid);
                            index = 0;
                        }
                    }
            }
        }
    }
    TTF_CloseFont(font);
    return 0;
}