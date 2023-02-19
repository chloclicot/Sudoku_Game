
#define SUDOKU_MAX_SIZE 16

class Grid{
    private :
        int map[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE];
        int cube[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE+1];
        int taille;
        int length;
    public :
        Grid();
        Grid(int grille[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE], int size);
        bool calculate();
        int getCase(int x, int y);
        int getlength();
        int getCaseCube(int x, int y, int layer);
        int addValueToCase(int x,int y, int value);
        void copy(Grid *new_grid);
        int solve(int layer);
        bool isTerminated();
        void generate(int size,int fill);
        int solve_advice(int tab[3]);
        void dispgrid();
    private :
        int sumPossibilities(int x, int y);
        void getSection(int x, int y, int holder[SUDOKU_MAX_SIZE]);
        void getLine(int num_line,int holder[SUDOKU_MAX_SIZE]);
        void getColumn(int num_column,int holder[SUDOKU_MAX_SIZE]);
        int solve_rand(int layer);
        int solve_advice_p(int tab[3],int layer);
        void merge_to_parttern(bool pattern[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE]);
};


void noise_tab(bool tab[SUDOKU_MAX_SIZE][SUDOKU_MAX_SIZE],int taille,int nombre);