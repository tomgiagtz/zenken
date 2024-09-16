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

        // Cage* cage = new Cage(30, Cage::Multiplication);
        // cage->Add(grid->GetCells({0, 1, 2}));
        //
        // Cage* cage2 = new Cage(2, Cage::Subtraction);
        // cage2->Add(grid->GetCells({3, 4, 5})); //, 12, 19, 20, 27, 34, 41, 40, 39, 38, 37, 36, 29, 22, 23, 24, 31}));
        cages = CageSet1();
    }

    // harded coded puzzle found online
    std::vector<Cage*> CageSet1() {
        size = 5;
        grid = new Grid(size);

        Cage* cage1 = new Cage(5, Cage::Addition);
        cage1->Add(grid->GetCells({0, 5}));
        Cage* cage2 = new Cage(9, Cage::Addition);
        cage2->Add(grid->GetCells({1, 2, 3,}));
        Cage* cage3 = new Cage(3, Cage::Subtraction);
        cage3->Add(grid->GetCells({4, 9}));
        Cage* cage4 = new Cage(36, Cage::Multiplication);
        cage4->Add(grid->GetCells({6, 11, 10}));
        Cage* cage5 = new Cage(10, Cage::Multiplication);
        cage5->Add(grid->GetCells({7, 12}));
        Cage* cage6 = new Cage(6, Cage::Addition);
        cage6->Add(grid->GetCells({8, 13}));
        Cage* cage7 = new Cage(3, Cage::Subtraction);
        cage7->Add(grid->GetCells({14, 19}));
        Cage* cage8 = new Cage(3, Cage::Subtraction);
        cage8->Add(grid->GetCells({15, 16}));
        Cage* cage9 = new Cage(12, Cage::Multiplication);
        cage9->Add(grid->GetCells({17, 18, 22}));
        Cage* cage10 = new Cage(5, Cage::Multiplication);
        cage10->Add(grid->GetCells({20, 21}));
        Cage* cage11 = new Cage(1, Cage::Subtraction);
        cage11->Add(grid->GetCells({23, 24}));

        return std::vector<Cage*>({cage1, cage2, cage3, cage4, cage5, cage6, cage7, cage8, cage9, cage10, cage11});
    }

    Grid* GetGrid() {
        return grid;
    }

    std::vector<Cage*>* GetCages() {
        return &cages;
    }

};
