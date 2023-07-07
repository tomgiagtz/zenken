#include "Grid.h"

void Grid::Replace() {
    // First, delete the old array
    for (unsigned int i = 0; i < size; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    // Then, create a new one
    grid = new Cell*[size];
    for (unsigned int i = 0; i < size; ++i) {
        grid[i] = new Cell[size];
    }
}
