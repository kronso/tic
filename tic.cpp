#include <iostream>
#include <conio.h>
#include <cstring>
#include <time.h>
#include <windows.h>

#include "tic.hpp"

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
            if (cursor_y == i && cursor_x == j) { // highlights players cursor
                std::cout << GREEN_FG << grid[i][j] << RESET << "  ";
            } else if (grid[i][j] != '.') { 
                if (highlightResult(i, j)) { // highlights the winning line
                    std::cout << RED_FG << grid[i][j] << RESET << "  ";
                } else {
                    std::cout << BLACK_FG << grid[i][j] << RESET << "  ";
                }
            } else {
                std::cout << grid[i][j] << "  ";
            }
        }
        std::cout << std::endl;
    }
}
// just for aesthetics
// highlights winners connect-line-thing 
bool Grid::highlightResult(int y, int x) {
    for (int i = 0; i < SIZE; i++) {
        if ((y == result_y[i] && x == result_x[i]) || (y == result_y1[i] && x == result_x1[i])) {
            return true;
        }
    }
    return false;
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
                enemyPlay();
            }
            break;    
        default:
            break;        
    }
}

void Grid::playerTurn() {
    bool temp;
    temp = o_turn;
    o_turn = x_turn;
    x_turn = temp;
}
void Grid::resetResult(char *arr) {
    // '\0' to compare it with string literal "XXX" / "OOO"
    for (int i = 0; i < (SIZE + 1); i++) {
        arr[i] = '.';
        if (i == SIZE) { arr[i] = '\0'; }
    }
}
char *Grid::compare(char c, char *arr) {
    for (int i = 0; i < (SIZE + 1); i++) {
        arr[i] = c;
        if (i == SIZE) { arr[i] = '\0'; }
    }
    return arr;
}
void Grid::resetPosition(int *arr) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = -1; // -1 because it can't be printed on the grid;
    }
}
bool Grid::winner() {
    // extra + 1 for '\0'
    char check_row[SIZE + 1];
    char check_col[SIZE + 1];
    // string to compare to
    char result[SIZE + 1];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            check_row[j] = grid[i][j];
            result_y[j] = i, result_x[j] = j; // setting position for highlight

            check_col[j] = grid[j][i]; 
            result_y1[j] = j, result_x1[j] = i; // ^ same thing here
            if (strcmp(check_row, compare('X', result)) == 0 || strcmp(check_row, compare('O', result)) == 0) {
                // reset the other positions so it doesn't show in print
                resetPosition(result_y1); resetPosition(result_x1);
                return true;
            } else if (strcmp(check_col, compare('X', result)) == 0 || strcmp(check_col, compare('O', result)) == 0) {
                resetPosition(result_y); resetPosition(result_x);
                return true;
            }
        }
        // reset everything for the next loop to reuse
        resetResult(check_row); resetResult(check_col); 
        resetPosition(result_y); resetPosition(result_x); 
        resetPosition(result_y1); resetPosition(result_x1);
    }
    // I reused the two arrays for the left and right diagonal check 
    // might not be readable but it works :D
    for (int i = 0; i < SIZE; i++) {
        // top-left to bottom-right diagonal
        check_row[i] = grid[i][i];
        result_y[i] = i, result_x[i] = i;
        // top-right to bottom-left diagonal
        check_col[i] = grid[i][(SIZE - 1) - i];
        result_y1[i] = i, result_x1[i] = (SIZE - 1) - i;
        if (strcmp(check_row, compare('X', result)) == 0 || strcmp(check_row, compare('O', result)) == 0) {
            resetPosition(result_y1); resetPosition(result_x1);
            return true;
        } else if (strcmp(check_col, compare('X', result)) == 0 || strcmp(check_col, compare('O', result)) == 0) {
            resetPosition(result_y); resetPosition(result_x);
            return true;
        }
    }
    // reset if no line was found
    resetPosition(result_y); resetPosition(result_x); 
    resetPosition(result_y1); resetPosition(result_x1);
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

// use it if u want a fake 'bot' to vs
void Grid::enemyPlay() {
    srand(time(NULL));
    int rand_row, rand_col;
    while (!winner() && !tie()) {
        rand_row = rand() % SIZE;
        rand_col = rand() % SIZE;
        if (grid[rand_row][rand_col] == '.') {
            if (o_turn) { grid[rand_row][rand_col] = 'O';}
            else if (x_turn) { grid[rand_row][rand_col] = 'X'; }
            playerTurn();
            return;
        } else { continue; }
    }
}
