#pragma once
#include <vector>
#include "Grid.h"
#include "Cage.h"

class Puzzle {

    unsigned size;
    std::vector<Cage*> cages;
    Grid* grid;

public:
    Puzzle(unsigned _size) {
        size = _size;
        grid = new Grid(_size);

        Cage* cage = new Cage();
        cage->Add(grid->GetCells({0, 1, 2}));
        Cage* cage2 = new Cage();
        cage2->Add(grid->GetCells({3, 4, 5, 12, 19, 20, 27, 34, 41, 40, 39, 38, 37, 36, 29, 22, 23, 24, 31}));
        cages = std::vector<Cage*>({cage, cage2});
    }

    Grid* GetGrid() {
        return grid;
    }

    std::vector<Cage*>* GetCages() {
        return &cages;
    }

};
