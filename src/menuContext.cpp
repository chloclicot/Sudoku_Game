// Affichage d'un menu conetxtuel cliquable dans la fenetre
// Adapté à une fenetre 1280 par 720

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Window.h"
#include "sdl_text.h"
#include "jeux.h"
#include "color.h"
#include "menuContext.h"

using namespace std;

/**
 * @brief Affiche la fenêtre avec la barre de menu
 * 
 * @param window fenêtre dans laquell eon affiche
 * @param render Renderer
 * @param color couleur du fond
 * @param font police dans laquelle on écrit
 */

void fenetreMenu(Window window,SDL_Renderer* render, const SDL_Color color,TTF_Font *font){

    //Affichage de la grille dans une couleur plus foncée
    SDL_SetRenderDrawColor(window.getRenderer(),color.r - 155,color.g - 40, color.b-40,SDL_ALPHA_OPAQUE);

    //dessiner un rectangle avec les trois petits traits avec marqué menu en blanc 

    SDL_Rect rect = {0, 0,1280,30 };

    SDL_SetRenderDrawColor(render,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(render, &rect); 

    //La on voudrait juste faire une ligne un peu plus foncée pour délimiter le rect du menu
    //Donc on récupere les valeurs de la couleur et on enleve genre 10 à tous
    SDL_SetRenderDrawColor(render,color.r - 155,color.g-40,color.b-40,SDL_ALPHA_OPAQUE );
    SDL_RenderDrawLine(render,0,30,1280,30);
    SDL_RenderDrawLine(render,0,31,1280,31);

    //Ecriture du texte
    // Trois petits rectangles du menu en blanc
    SDL_Rect rects[3] = {{10,7,30,3},{10,14,30,3},{10,21,30,3}};
    SDL_SetRenderDrawColor(render,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRects(render, rects,3);
    // MENU en blanc
    render_text(font,WHITE,(char*) "MENU",window,45,3,60,28);
    SDL_SetRenderDrawColor(window.getRenderer(),0,0,0,SDL_ALPHA_OPAQUE);
}


void OpenMenu(Window window,SDL_Renderer* render,SDL_Color color,TTF_Font *font){
    int i,y;
    SDL_Rect rectMenu = {0, 32, 277, 144};
    SDL_Texture *texture1 = SDL_CreateTexture(render, 0, SDL_TEXTUREACCESS_TARGET, rectMenu.w, rectMenu.h);

    SDL_Rect rectM = {0,0,rectMenu.w,rectMenu.h}; //Apres on pourra remplir un p eu moins pour rajouter une petite ombre et tout
    SDL_SetRenderDrawColor(render,MEDIUM_PINK.r,MEDIUM_PINK.g,MEDIUM_PINK.b,SDL_ALPHA_OPAQUE);
    SDL_SetRenderTarget(render,texture1);
    SDL_RenderFillRect(render,&rectM);

    SDL_SetRenderDrawColor(render,color.r - 20,color.g-20,color.b-20,SDL_ALPHA_OPAQUE);
    y = 32;
    for(i=0;i<5;i++){
        SDL_RenderDrawLine(render,0, y, rectM.w, y);
        SDL_RenderDrawLine(render,0, y+1, rectM.w, y+1);
        y = y + 36;
    }

    //Texte des options
    render_text(font,BLACK,(char*) "Quitter ",window,3,3,100,30);
    render_text(font,BLACK,(char*) "Aide ",window,3,39,60,30);
    render_text(font,BLACK,(char*) "Precedent ",window,3,75,120,30);
    render_text(font,BLACK,(char*) "Suivant ",window,3,108,110,30);
    

    // Les trois rectangles des cases 
    SDL_Rect rect1 = {0,0,rectM.w,32};
    SDL_Rect rect2 = {0,32,rectM.w,32};
    SDL_Rect rect3 = {0,64,rectM.w,32};
    

    //On remet le renderer correctement
    SDL_SetRenderTarget(render,NULL);
    SDL_RenderCopy(render, texture1, NULL, &rectMenu);
}