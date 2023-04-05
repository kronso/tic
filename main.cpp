#include <iostream>
#include <conio.h>
#include <cstring>
#include <time.h>
#include <windows.h>    

#include "tic.hpp"

// just for aesthetic purposes
void delayPrint(const char *s, float delay_ms = 50) { 
    for (; *s; s++) {
        std::cout << *s;
        Sleep(delay_ms);
    }
    Sleep(1000);
}

int main() {
    // constructor to choose 'X' or 'O' respectively
    // true for default
    Grid g(false, true);
    g.initGrid();
    // instructions
    delayPrint("Use WASD to move...");
    delayPrint("\nEnter to place...");

    do {
        g.printGrid();
        if (g.x_turn) { std::cout << "\nx's turn..."; }
        else if (g.o_turn) { std::cout << "\no's turn...";}
        g.moveCursor();
    } while (!g.winner() && !g.tie());
    // just to get rid of the players cursor
    g.cursor_y = g.cursor_x = -1;

    g.printGrid();
    if (g.winner()) {
        if (!g.x_turn) { std::cout << "\nx wins"; }
        else if (!g.o_turn) { std::cout << "\no wins"; }
    } else if (g.tie()) { std::cout << "TIE"; }

    return EXIT_SUCCESS;
}