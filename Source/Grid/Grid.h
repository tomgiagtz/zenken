#pragma once
#include <iostream>

#include "Cell.h"

class Grid {
public:
    Grid(unsigned int _size = 5) : size(_size) {
        grid = new Cell*[size];
        for (unsigned int i = 0; i < size; i++) {
            grid[i] = new Cell[size];
            for (unsigned int j = 0; j < size; ++j) {
                grid[i][j] = Cell(i, j); // copy the initData into each cell
            }
        }
    }

    ~Grid() {
        for (unsigned int i = 0; i < size; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    /**
     * \brief replaces entire grid with a new one
     * 
     * \param _size size of square grid
     */
    void SetSize(unsigned int _size) {
        size = _size;
        Replace();
    }

    void ToString() const {
        for (unsigned int i = 0; i < size; ++i) {
            for (unsigned int j = 0; j < size; ++j) {
                std::cout << grid[i][j].GetValue() << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    unsigned int size;
    Cell** grid;

    // Replace the current grid with a new one
    void Replace();
};
