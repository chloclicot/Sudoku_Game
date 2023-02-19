#include <SDL2/SDL_ttf.h>
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "sdl_text.h"
#include "accueil.h"
#include "color.h"
#include "fd/tinyfiledialogs.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

char* accueil_window(){
    int x,y;
    char * a;
    char * lFilterPatterns[1] = { ((char*) "*.cartonpate") };
    char * selection;
    bool exit = false; // variable de sortie de la boucle d'event

    Window window = Window((char*) "Sudoku",SCREEN_WIDTH,SCREEN_HEIGHT);

    // Rendu du fond blanc de la fenêtre
    SDL_SetRenderDrawColor(window.getRenderer(),255, 255, 255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(window.getRenderer(), NULL);

    // Ouverture d'une police d'ecriture
    TTF_Font * font = TTF_OpenFont("assets/DalekPinpointBold.ttf", 100);
    TTF_Font * font_2 = TTF_OpenFont("assets/CarterOne-Regular.ttf", 100);

    // Texte de presentation
    render_text(font, BLACK, (char*) "Sudoku", window, 120, 10, 400, 100);
    render_text(font_2, DARK_GRAY_BLUE, (char*) "Par Sylvain SAUSSE et Chloe VARIN", window, 95, 100, 450, 40);

    // Boutons de menu
    render_text(font_2, DARK_GRAY_BLUE, (char*) "Ouvrir une grille", window, 120, 200, 250, 40);
    render_text(font_2, DARK_GRAY_BLUE, (char*) "Creer une grille", window, 120, 250, 250, 40);



    // rendu du texte
    window.render();
    // Fermeture du fichier de police
    TTF_CloseFont(font);
    TTF_CloseFont(font_2);

    // Boucle d'event
    while(exit == false){
        SDL_Delay(16); // effectue la boucle toute les 16ms
        if (SDL_PollEvent(window.getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(window.getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                // Click event
                case SDL_MOUSEBUTTONUP:
                    if(window.getEvent().button.button == SDL_BUTTON_LEFT)
                    {
                        x=window.getEvent().button.x;
                        y=window.getEvent().button.y;
                        if( y > 250 && y < 290 && x > 120 && x < 370){
                            a = gen_selector();
                            if(a!=((char*)"0")){
                                window.destroy();
                                return a;
                            }
                        }
                        else if( y > 200 && y < 240 && x > 120 && x < 370){
                            selection = tinyfd_openFileDialog( // there is also a wchar_t version
                                "Choisir une grille", // title
                                NULL, // optional initial directory
                                1, // number of filter patterns
                                lFilterPatterns, // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
                                NULL, // optional filter description
                                0 // forbid multiple selections
                            );
                            if(selection != NULL ){
                                //TTF_Quit();
                                // destruction de la fenètre
                                window.destroy();
                                // fermeture du module SDL
                                return selection;
                            }
                        }
                            
                    }
            }
        }
    }
    // destruction de la fenètre
    window.destroy();
    // fermeture du module SDL
    return (char*)"0";
}

char* gen_selector(){
    bool exit = false;
    Window popup = Window((char *) "Selectionner le type de grille",450,300);
    SDL_SetRenderDrawColor(popup.getRenderer(),255, 255, 255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(popup.getRenderer(), NULL);
        // Initialisationd de la librarie SDL_ttf.h
    // Ouverture d'une police d'ecriture
    TTF_Font * font = TTF_OpenFont("assets/DalekPinpointBold.ttf", 100);
    TTF_Font * font_2 = TTF_OpenFont("assets/CarterOne-Regular.ttf", 100);

    render_text(font, BLACK, (char*) "Choisissez la taille", popup, 75, 0, 300, 50);
    render_text(font_2, BLACK, (char*) "4x4", popup, 75, 100, 75, 75);
    render_text(font_2, BLACK, (char*) "9x9", popup, 300, 100, 75, 75);
    render_text(font_2, BLACK, (char*) "annuler", popup, 150, 200, 150, 50);


    // rendu du texte
    popup.render();
    // Fermeture du fichier de police
    TTF_CloseFont(font);
    TTF_CloseFont(font_2);

    int x,y;
     while(exit == false){
        SDL_Delay(16); // effectue la boucle toute les 16ms
        if (SDL_PollEvent(popup.getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(popup.getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                case SDL_MOUSEBUTTONUP:
                    if(popup.getEvent().button.button == SDL_BUTTON_LEFT){
                        x=popup.getEvent().button.x;
                        y=popup.getEvent().button.y;
                        if( y > 200 && y < 250 && x > 150 && x < 300){
                            exit = true;
                        }
                        if( y > 100 && y < 175 && x > 75 && x < 150){
                            popup.destroy();
                            char* a;
                            char* b = diff_window();
                            if(b!=(char*)"0"){
                                char* a;
                                a = (char*) malloc(4);
                                strcpy(a,"4-");
                                strcat(a,b);
                                return a;
                            }
                        }
                        if( y > 100 && y < 175 && x > 300 && x < 375){
                            popup.destroy();
                            char* b = diff_window();
                            if(b!=(char*)"0"){
                                char* a;
                                a = (char*) malloc(4);
                                strcpy(a,"9-");
                                strcat(a,b);
                                return a;
                            }
                        }

                    }
            }
        }
    }
    popup.destroy();
    return (char*)"0";
}

char* diff_window(){
    bool exit = false;
    Window popup = Window((char *) "Selectionner le type de grille",450,300);
    SDL_SetRenderDrawColor(popup.getRenderer(),255, 255, 255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(popup.getRenderer(), NULL);
        // Initialisationd de la librarie SDL_ttf.h
    // Ouverture d'une police d'ecriture
    TTF_Font * font = TTF_OpenFont("assets/DalekPinpointBold.ttf", 100);
    TTF_Font * font_2 = TTF_OpenFont("assets/CarterOne-Regular.ttf", 100);

    render_text(font, BLACK, (char*) "Choisissez la difficultee", popup, 75, 0, 300, 50);
    render_text(font_2, BLACK, (char*) "1", popup, 60, 100, 30, 75);
    render_text(font_2, BLACK, (char*) "2", popup, 120, 100, 50, 75);
    render_text(font_2, BLACK, (char*) "3", popup, 190, 100, 50, 75);
    render_text(font_2, BLACK, (char*) "4", popup, 260, 100, 50, 75);
    render_text(font_2, BLACK, (char*) "5", popup, 330, 100, 50, 75);
    render_text(font_2, BLACK, (char*) "annuler", popup, 150, 200, 150, 50);

    // rendu du texte
    popup.render();
    // Fermeture du fichier de police
    TTF_CloseFont(font);
    TTF_CloseFont(font_2);

    int x,y;
     while(exit == false){
        SDL_Delay(16); // effectue la boucle toute les 16ms
        if (SDL_PollEvent(popup.getEventPointer())){ // recuperer les events tant qu'il y en a en attente
            switch(popup.getEvent().type){ // ici on gère les differents events
                case SDL_QUIT : // Si l'utilisateur demande de fermer l'application
                    exit = true;
                case SDL_MOUSEBUTTONUP:
                    if(popup.getEvent().button.button == SDL_BUTTON_LEFT){
                        x=popup.getEvent().button.x;
                        y=popup.getEvent().button.y;
                        if( y > 200 && y < 250 && x > 150 && x < 300){
                            exit = true;
                        }
                        if( y > 100 && y < 175 && x>60 && x<90){
                            popup.destroy();
                            return (char*) "1";
                        }
                        if( y > 100 && y < 175 && x>120 && x<170){
                            popup.destroy();
                            return (char*) "2";
                        }
                        if( y > 100 && y < 175 && x>190 && x<240){
                            popup.destroy();
                            return (char*) "3";
                        }
                        if( y > 100 && y < 175 && x>260 && x<310){
                            popup.destroy();
                            return (char*) "4";
                        }
                        if( y > 100 && y < 175 && x>330 && x<380){
                            popup.destroy();
                            return (char*) "5";
                        }

                    }
            }
        }
    }
    popup.destroy();
    return (char*)"0";
}