#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Cage.h"
#include "Cell.h"

class Grid {
private:
    unsigned int size;
    std::vector<std::vector<Cell>> grid;
    std::vector<Cage> cages;
    // Replace the current grid with a new one
    void Replace();

public:
    Grid(const unsigned int _size = 5) :
        size(_size), grid(size, std::vector<Cell>(size)) {
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; ++j) {
                grid[i][j] = Cell(i, j, size, (i * size + j));
            }
        }
    }

    void SetSize(const unsigned int _size) {
        size = _size;
        grid = std::vector<std::vector<Cell>>(size, std::vector<Cell>(size));
    }

    unsigned GetSize() {
        return size;
    }

    /**
     * \brief Get Cell from a position in the grid
     * \param _i column index
     * \param _j row index
     * \return cell at the position
     */
    Cell* GetCell(const unsigned int _i, const unsigned int _j) {
        return &grid[_i][_j];
    }

    /**
     * \brief Get Cell from a index in the grid
     * \param _index converted to a position in the grid
     * \return Cell* the cell at the index
     */
    Cell* GetCell(const unsigned int _index) {
        const sf::Vector2i position = PositionFromIndex(_index, size);
        return &grid[position.x][position.y];
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

    static sf::Vector2i PositionFromIndex(const int _index, const int _size) {
        return {_index % _size, _index / _size};
    }


};
