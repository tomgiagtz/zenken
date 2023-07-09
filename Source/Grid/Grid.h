#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"

class Grid {
private:
    unsigned int size;
    std::vector<std::vector<Cell>> grid;
    // Replace the current grid with a new one
    void Replace();

public:
    Grid(const unsigned int _size = 5) : size(_size), grid(size, std::vector<Cell>(size)) {
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; ++j) {
                grid[i][j] = Cell(i, j, (i * size) + j);
            }
        }
    }

    /**
     * \brief replaces entire grid with a new one
     * 
     * \param _size size of square grid
     */
    void SetSize(const unsigned int _size) {
        size = _size;
        grid = std::vector<std::vector<Cell>>(size, std::vector<Cell>(size));
    }

    void Clear() {
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; ++j) {
                grid[i][j].SetValue(0);
            }
        }
    }

    std::string ToString() const {
        std::string result;
        for (unsigned int i = 0; i < grid.size(); ++i) {
            for (unsigned int j = 0; j < grid[i].size(); ++j) {
                result += std::to_string(grid[i][j].GetValue()) + " ";
            }
            result += "\n";
        }
        return result;
    }


};
