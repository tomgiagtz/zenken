#pragma once
#include <vector>

#include "Cell.h"

class Cage {
    std::vector<Cell*> cells;

public:
    /**
     * \brief IsValid checks if the cage is geometrically valid, every cell is unique, and the cage is contiguous
     * \param _cells the cells that are in the cage
     * \return bool whether the cage is valid or not
     */
    bool IsValid(std::vector<Cell*> _cells);

    bool Add(Cell* _cell) {
        cells.push_back(_cell);
        if (IsValid(cells)) {
            return true;
        }
        cells.pop_back();
        return false;
    }



};
