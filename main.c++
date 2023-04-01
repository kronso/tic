#include <iostream>
#include <conio.h>
#include <cstring>

#define clear() std::cout << "\e[1;1H\e[2J";
#define GREEN_FG "\033[38;5;49m"
#define BLACK_FG "\033[38;5;239m"
#define RESET "\033[m"
#define SIZE 3

class Grid {
    private:
        char grid[SIZE][SIZE];
    public:
        int cursor_y, cursor_x;
        bool x_turn = false, o_turn = true;
        
        Grid(int y, int x) {
            cursor_y = y;
            cursor_x = x;
        }

        void initGrid();
        void printGrid();
        void moveCursor();

        void playerTurn();
        void reset(char *arr);
        bool winner();
        bool tie();
};




void Grid::initGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = '.';
        }
    }
}
void Grid::printGrid() {
    clear();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cursor_y == i && cursor_x == j) {
                std::cout << GREEN_FG << grid[i][j] << RESET << "  ";
            } else if (grid[i][j] != '.') { 
                std::cout << BLACK_FG << grid[i][j] << RESET << "  ";
            } else {
                std::cout << grid[i][j] << "  ";
            }
        }
        std::cout << std::endl;
    }
}
void Grid::moveCursor() {
    const int ENTER = 13;
    char input;

    kbhit();
    input = tolower(getch());
    switch(input) {
        case 'w':
            if (cursor_y > 0) { cursor_y -= 1; }
            break;
        case 'a':
            if (cursor_x > 0) { cursor_x -= 1; }   
            break;            
        case 's':
            if (cursor_y < (SIZE - 1)) { cursor_y += 1; }
            break;
        case 'd':
            if (cursor_x < (SIZE - 1)) { cursor_x += 1; }
            break;                        
        case ENTER:
            if (grid[cursor_y][cursor_x] == '.') {
                if (x_turn) { grid[cursor_y][cursor_x] = 'X'; }
                else if (o_turn) { grid[cursor_y][cursor_x] = 'O'; }
                playerTurn();
            }
            break;    
        default:
            break;        
    }
}

// swaps turn
void Grid::playerTurn() {
    bool temp;
    temp = o_turn;
    o_turn = x_turn;
    x_turn = temp;
}
void Grid::reset(char *arr) {
    // '\0' to compare it with string literal "XXX" / "OOO"
    for (int i = 0; i < SIZE + 1; i++) {
        arr[i] = '.';
        if (i == SIZE) { arr[i] = '\0'; }
    }
}
bool Grid::winner() {
    // extra + 1 for '\0'
    char check_row[SIZE + 1];
    char check_col[SIZE + 1];
    
    for (int i = 0; i < SIZE; i++) {
        reset(check_row); reset(check_col);
        for (int j = 0; j < SIZE; j++) {
            check_row[j] = grid[i][j];
            check_col[j] = grid[j][i]; 
            if (strcmp(check_row, "XXX") == 0 || strcmp(check_row, "OOO") == 0) {
                return true;
            } else if (strcmp(check_col, "XXX") == 0 || strcmp(check_col, "OOO") == 0) {
                return true;
            }
        }
    }
    // I reused the two arrays for the left and right diagonal check 
    // might not be readable but it works :D
    reset(check_row); reset(check_col);
    for (int i = -1; i < 2; i++) {
        // left diagonal
        check_row[i + 1] = grid[1 + i][1 + i];
        // right diagonal
        check_col[i + 1] = grid[1 + i][1 - i];
        if (strcmp(check_row, "XXX") == 0 || strcmp(check_row, "OOO") == 0) {
            return true;
        } else if (strcmp(check_col, "XXX") == 0 || strcmp(check_col, "OOO") == 0) {
            return true;
        }
    }
    return false;
}
bool Grid::tie() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == '.') { return false; }
        }
    }
    return true;
}

int main() {
    Grid g(1, 1);
    g.initGrid();
    do {
        g.printGrid();
        if (g.x_turn) { std::cout << "\nX's TURN"; }
        else if (g.o_turn) { std::cout << "\nO's TURN"; }
        g.moveCursor();
    } while (!g.winner() && !g.tie());

    g.printGrid();
    if (g.winner()) {
        if (!g.x_turn) { std::cout << "\nX WON"; }
        else if (!g.o_turn) { std::cout << "\nO WON"; }
    } else if (g.tie()) { std::cout << "TIE"; }

    return EXIT_SUCCESS;
}