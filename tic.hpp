#ifndef TIC_H
#define TIC_H

#define clear() std::cout << "\e[1;1H\e[2J";

#define GREEN_FG "\033[38;5;49m"
#define BLACK_FG "\033[38;5;239m"
#define RED_FG "\033[38;5;197m"
#define RESET "\033[m"

// change this for different sizes
// height and width of grid will always be the same
// if the size is even, the highlighting is a bit scuffed
#define SIZE 3

class Grid {
    char grid[SIZE][SIZE];
    public:
        int cursor_y = SIZE / 2, cursor_x = SIZE / 2;
        // ROWS AND top-left to bottom-right diagonal
        int result_x[SIZE];
        int result_y[SIZE];
        // COLS AND top-right to bottom-left diagonal
        int result_x1[SIZE];
        int result_y1[SIZE];

        bool x_turn, o_turn;

        Grid(bool x = true, bool o = false) {
            x_turn = x;
            o_turn = o;
        }

        void initGrid();
        void printGrid();
        bool highlightResult(int y, int x);
        void moveCursor();

        void playerTurn();
        void resetResult(char *arr);
        void resetPosition(int *arr);
        char *compare(char c, char *arr);
        bool winner();
        bool tie();

        void enemyPlay();
};

#endif