#include <iostream> 
#include <fstream>

using namespace std;

/*
* Extrait les données d'un fichier carton pate et les insert dans un tableau d'int et un int passé par adresse
*/
void extraire(string chemin, int valeurs[16][16],int *taille){
    //ouverture du fichier
    ifstream fichier(chemin);
    int i,j;
    if(fichier){
        // premier chiffre du fichier = taille de la grille
        //récupération de la taille
        fichier >> *taille;
        int size = (*taille)*(*taille);
        for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                // valeurs de la grille stockées dans un tableau
                fichier >> valeurs[i][j];
            }
        }
    }
}

void extraireJuste(string chemin, int valeurs[16][16]){
    //ouverture du fichier
    ifstream fichier(chemin);
    int i,j;
    if(fichier){
        // premier chiffre du fichier = taille de la grille
        //récupération de la taille
        int taille;
        fichier >> taille;
        int size = (taille)*(taille);
        for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                // valeurs de la grille stockées dans un tableau
                fichier >> valeurs[i][j];
            }
        }
    }
}