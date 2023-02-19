#include <iostream>
#include "Grid.h"
#include "classictools.h"
#include <cstdlib> 
#include <ctime> 

using namespace std;

/*
* Contructeur public de la class Grid
*/
Grid::Grid(int grille[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE], int size){
    int t = size*size;
    if(t<=SUDOKU_MAX_SIZE){
        int i,j;
        taille = size;
        length = size*size;
        for(i=0;i<t;i++){
            for(j=0;j<t;j++){
                map[i][j] = grille[i][j];
                if(map[i][j]!=0){
                    cube[i][j][0]=2;
                }
                else{
                    cube[i][j][0]=0;
                }
            }
        }
        calculate();
    }
    else{
        cout << "Trop grand" << endl;
    }
}

/*
* Constructeur privé de la class Grid
*/
Grid::Grid(){
    taille = 0;
    length =0;
    for(int i=0;i<SUDOKU_MAX_SIZE;i++){
        for(int j=0;j<SUDOKU_MAX_SIZE;j++){
                map[i][j] = 0;
            for(int k =0;k<SUDOKU_MAX_SIZE+1;k++){
                this->cube[i][j][k] = 0;
            }
        }
    }
}



/*
* Recupère les valeurs de la section de la case de coordonée (x,y)
*/
void Grid::getSection(int x, int y, int holder[SUDOKU_MAX_SIZE]){
    int p_x = x/taille;
    int p_y = y/taille;
    if(p_x<taille && p_y<taille){
        int a = 0;
        for(int i=p_x*taille;i<(p_x+1)*(taille);i++){
            for(int j=p_y*taille;j<(p_y+1)*(taille);j++){
                holder[a++] = map[i][j];
            }
        }
    }
    else{
        cout << "e" << endl;
    }
    return;
}


/*
* Recupère les valeurs de la ligne de la case de coordonée (x,y)
*/
void Grid::getLine(int num_line,int holder[SUDOKU_MAX_SIZE]){
    if(num_line <= length)
        for(int i=0;i<length;i++){
            holder[i] = map[num_line][i];
    }
    else{
        cout << "e" << endl;
    }
    return;
}

/*
* Recupère les valeurs de la colonne de la case de coordonée (x,y)
*/
void Grid::getColumn(int num_column,int holder[SUDOKU_MAX_SIZE]){
    if(num_column <= length)
        for(int i=0;i<length;i++){
            holder[i] = map[i][num_column];
    }
    else{
        cout << "e" << endl;
    }
    return;
}

/*
*
* Recalcule les valeur de la variable cube
*
* variable cube :
* i -> coord x | j -> cord y
* k=0 => etat de la case : 0 vide; 1 completée et valide; -1 completée et invalide; 2 Issu du generateur
* k=i => possibilitée de mettre le chiffre i dedans
*
*/
bool Grid::calculate(){
    int i,j,k;
    for(i=0;i<length;i++){
        for(j=0;j<length;j++){
            if(map[i][j]==0){
                cube[i][j][0]=0;
                for(k=1;k<length+1;k++){
                    bool le_booleen = true;
                    int zone[length];
                    int line[length];
                    int col[length];
                    getSection(i,j,zone);
                    getLine(i,line);
                    getColumn(j,col);
                    for(int l=0;l<length;l++){
                        if( zone[l]==k || line[l]==k || col[l]==k ) le_booleen = 0;
                    }
                    cube[i][j][k] = le_booleen;
                }
            }
            else if(cube[i][j][0]!=2){
                int val = map[i][j];
                int zone[length];
                int line[length];
                int col[length];
                getSection(i,j,zone);
                getLine(i,line);
                getColumn(j,col);
                if(occurences(val,zone,length)==1 && occurences(val,line,length)==1 && occurences(val,col,length)==1){
                    cube[i][j][0] = 1;
                }
                else{
                    cube[i][j][0] = -1;
                }
            }
        }
    }
    return 0;
}

/*
* Recupère les valeurs de la case de coordonée (x,y)
*/
int Grid::getCase(int x, int y){
    return map[x][y];
}

/*
* Recupère les valeurs de cube[x][y][layer]
*/
int Grid::getCaseCube(int x, int y, int layer){
    return cube[x][y][layer];
}

/*
* Retourne le nombre de possibilité de la case (x,y)
*/
int Grid::sumPossibilities(int x,int y){
    int sum=0;
    if(cube[x][y][0]==0){
        for(int i=1;i<(length)+1;i++){
            sum = sum + cube[x][y][i];
        }
        return sum;
    }
    return -1;
}

/*
*  Ajoute la valeur à la case (x,y) et recalcule le cube à l'aide de Grid::calculate
*/
int Grid::addValueToCase(int x, int y, int value){
    if(value<=length && cube[x][y][0]!=2){
        map[x][y] = value;
        calculate();
        return cube[x][y][0];
    }
    return -2;
}

/*
* Copie la grille qui appelle la methode dans la grille passé par adresse
*/
void Grid::copy(Grid *new_grid){
    new_grid->taille = this->taille;
    new_grid->length = this->length;
    for(int i=0;i<SUDOKU_MAX_SIZE;i++){
        for(int j=0;j<SUDOKU_MAX_SIZE;j++){
            new_grid->map[i][j] = this->getCase(i,j);
            for(int k =0;k<SUDOKU_MAX_SIZE+1;k++){
                new_grid->cube[i][j][k] = this->getCaseCube(i,j,k);
            }
        }
    }
}

int Grid::solve(int layer){
    if(isTerminated()){
        return 1;
    }
    int i,j;
    int index = -1;
    int jndex = -1;
    int min = length+1;
    int placeholder;
    for(i=0;i<length;i++){
        for(j=0;j<length;j++){
            if(getCaseCube(i,j,0)==0){
                int placeholder = sumPossibilities(i,j);
                if(placeholder <= min && placeholder != 0){
                    index = i;
                    jndex = j;
                    min = placeholder;
                }
            }
        }
    }
    int r;
    if(index!=-1 && jndex!=-1){
        for(i=1;i<length+1;i++){
            if(getCaseCube(index,jndex,i)==1){
                //Grid a;
                //copy(&a);
                //a.addValueToCase(index,jndex,i);
                addValueToCase(index,jndex,i);
                //int ret = a.solve(layer+1);
                r = solve(layer+1);
                if(r==1){
                    //a.copy(this);
                    return 1;
                }
            }
        }
        addValueToCase(index,jndex,0);
    }
    return -1;
}

bool Grid::isTerminated(){
    for(int i =0;i<length;i++){
        for(int j =0;j<length;j++){
            if(getCaseCube(i,j,0)==0 || getCaseCube(i,j,0)==-1){
                return false;
            }
        }
    }
    return true;
}

void Grid::dispgrid(){
    char translater[17] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G'};
    for(int i =0;i<length;i++){
        for(int j =0;j<length;j++){
            cout << translater[getCase(i,j)] << ' ';
            if(j%taille==taille-1) cout << ' ';
        }
        cout << endl;
        if(i%taille==taille-1) cout << endl;
    }
}

int Grid::solve_rand(int layer){
    if(isTerminated()){
        return 1;
    }
    int index = -1;
    int jndex = -1;
    int min = length+1;
    int placeholder;
    srand((unsigned)time(0)); 
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            if(getCaseCube(i,j,0)==0){
                int placeholder = sumPossibilities(i,j);
                if(placeholder <= min && placeholder != 0){
                    index = i;
                    jndex = j;
                    min = placeholder;
                }
            }
        }
    }
    int translater[length];
    bool accept;
    int value;
    for(int i=0;i<length;i++){
        accept = false;
        while(!accept){
            value = (rand()%(length))+1;
            accept = true;
            for(int j=0; j<i;j++){
                if(translater[j]==value) accept = false;
            }
        }
        translater[i] = value ;
    }
    if(index!=-1 && jndex!=-1){
        for(int i=0;i<length;i++){
            if(getCaseCube(index,jndex,translater[i])==1){
                //Grid a;
                //copy(&a);
                //a.addValueToCase(index,jndex,translater[i]);
                addValueToCase(index,jndex,translater[i]);
                //int ret = a.solve_rand(layer+1);
                int ret = solve_rand(layer+1);
                if(ret == 1){
                    //a.copy(this);
                    return 1;
                }
            }
        }
        addValueToCase(index,jndex,0);
    }
    return -1;
}

void Grid::merge_to_parttern(bool pattern[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE]){
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            if(pattern[i][j]){
                cube[i][j][0]=2;
            }
            else{
                map[i][j]=0;
                cube[i][j][0]=0;
            }
        }
    }
}

void Grid::generate(int size,int fill){
    *(this) = Grid();
    this->taille = size;
    this->length = (size)*(size);
    this->calculate();
    this->solve_rand(0);
    bool pattern[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE];
    noise_tab(pattern,taille,fill);
    this->merge_to_parttern(pattern);
    this->calculate();
}

void noise_tab(bool tab[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE],int taille,int nombre){
    int a,b;
    for(int j=0;j<taille*taille;j++){
       for(int k = 0;k<taille*taille;k++){
            tab[j][k]=0;
        }
    }
    srand((unsigned)time(0));
    if(nombre > taille*taille*taille*taille) nombre = taille*taille*taille*taille;
    for(int i = 0; i<nombre; i++){
        a = rand()%(taille*taille);
        b = rand()%(taille*taille);
        while(tab[a][b]){
            a = rand()%(taille*taille);
            b = rand()%(taille*taille);
        }
        tab[a][b]=true;
    }
}

int Grid::solve_advice_p(int tab[3],int layer){
    if(isTerminated()){
        return 1;
    }
    int i,j;
    int index = -1;
    int jndex = -1;
    int min = length+1;
    int placeholder;
    for(i=0;i<length;i++){
        for(j=0;j<length;j++){
            if(getCaseCube(i,j,0)==0){
                int placeholder = sumPossibilities(i,j);
                if(placeholder <= min && placeholder != 0){
                    index = i;
                    jndex = j;
                    min = placeholder;
                }
            }
        }
    }
    if(index!=-1 && jndex!=-1){
        for(i=1;i<length+1;i++){
            if(getCaseCube(index,jndex,i)==1){
                 //Grid a;
                //copy(&a);
                //a.addValueToCase(index,jndex,translater[i]);
                addValueToCase(index,jndex,i);
                //int ret = a.solve_rand(layer+1);
                int ret = solve_rand(layer+1);

                if(ret == 1){
                    tab[0] = index;
                    tab[1] = jndex;
                    tab[2] = i;
                    return 1;
                }
            }
        }
        addValueToCase(index,jndex,0);
    }
    return -1;
}

int Grid::solve_advice(int tab[3]){
    Grid a;
    copy(&a);
    return a.solve_advice_p(tab,0);
}

int Grid::getlength(){
    return length;
}