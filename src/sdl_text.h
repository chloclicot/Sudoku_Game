/*
* rend un texte dans la fenètre donnée en paramètre
*
* @param font : le pointeur d'une police d'ecriture
* @param color : couleur du texte
* @param text : list de caractère (pas un String) correspondant au texte que l'on veut afficher
* @param window : fenètre ou doit etre afficher le texte
* @param x : position x du coin haut droit du texte
* @param y : position y du coin haut droit du texte
* @param w : longueur en pixel du texte
* @param h : hauteur en pixel du texte
*
*/
void render_text(TTF_Font *font, SDL_Color color, char *text, Window window, int x, int y, int w, int h);