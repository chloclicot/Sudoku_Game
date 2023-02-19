#include "Grid.h"
#include "Historic.h"
#include <iostream>

using namespace std;

Historic::Historic(){
    n_save = 0;
    for(int i=0;i<MAX_HISTORIC_SAVE;i++){
        value[i] = Grid();
    }
}

void Historic::update(int index, Grid *new_last){
    if(index <= n_save && 0 <= index){
        if(index > 0){
            for(int i=1;i<n_save;i++){
                if((i+index-1)<MAX_HISTORIC_SAVE && i<MAX_HISTORIC_SAVE) value[i] = value[i+index-1];
            }
        }
        else{
            for(int i=n_save;i>0;i--){
                if((i+index-1)<MAX_HISTORIC_SAVE && i<MAX_HISTORIC_SAVE) value[i] = value[i-1];
            }
        }
        new_last->copy(&(value[0]));
        n_save = n_save + 1 - index;
        if(n_save>MAX_HISTORIC_SAVE) n_save = MAX_HISTORIC_SAVE;
        cout << n_save << endl;
    }
}

Grid Historic::getSave(int index){
    if(index < n_save && 0 <= index){
        return value[index];
    }
    return Grid();
}

int Historic::getNSave(){
    return n_save;
}