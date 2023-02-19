int occurences(int value, int *tab, int size_tab){
    int i,index;
    index = 0;
    for(i=0;i<size_tab;i++){
        index += tab[i]==value;
    }
    return index;
}