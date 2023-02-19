# define MAX_HISTORIC_SAVE 20

class Historic{
    private :
        Grid value[MAX_HISTORIC_SAVE];
        int n_save;
    public :
        Historic();
        void update(int index, Grid *new_last);
        Grid getSave(int index);
        int getNSave();
};