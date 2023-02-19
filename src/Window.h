class Window{
    private :
        SDL_Renderer *renderer;
        SDL_Window *self;
        SDL_Event event;
        int width;
        int height;
    public :
        Window(char *name, int width, int height);

        // détruit la fenêtre
        void destroy();

        // Actualise le rendu
        void render();

        // retourne l'attribut renderer
        SDL_Renderer* getRenderer();

        // retourne l'atribut self
        SDL_Window* getSelf();

        // retourne l'attribut event
        SDL_Event getEvent();

        // retourne un pointeur vers l'attribut event
        SDL_Event* getEventPointer();


};