#include <iostream>

class Graph {
    const int SIZE = 10;
    public:
        // dynamically allocate a 3D array
        // 30 * 30 = 900 pointers
        char ***grid = new char**[SIZE];
        int x_origin, y_origin, z_origin;

    void allocateGraph();
    void initGraph();
    void printGraph();
};      

void Graph::allocateGraph() {
    // https://www.geeksforgeeks.org/how-to-dynamically-allocate-a-3d-array-in-c/
    for (int z = 0; z < SIZE; z++) {
        grid[z] = new char*[SIZE];
        for (int y = 0; y < SIZE; y++) {
            grid[z][y] = new char[SIZE];
        }
    }
}

void Graph::initGraph() {
    // https://www.geeksforgeeks.org/how-to-dynamically-allocate-a-3d-array-in-c/
    for (int z = 0; z < SIZE; z++) {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                grid[z][y][x] = '1';
            }
        }
    }
}

void Graph::printGraph() {
    for (int z = 0; z < SIZE; z++) {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                std::cout << grid[z][y][x];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    Graph g;
    g.allocateGraph();
    g.initGraph();
    g.printGraph();
    return 1;
}