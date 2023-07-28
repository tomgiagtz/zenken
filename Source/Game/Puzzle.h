#pragma once
#include <vector>
#include "EntityManager.h"
#include "../Grid/Models/Cage.h"
#include "../Grid/Models/Grid.h"
#include "../Grid/Views/GridView.h"
#include "../Grid/Views/CageView.h"

class Puzzle {
public:
    Puzzle(sf::Vector2f _position, const unsigned int _size = 3, const unsigned int _width = 900) {
        settings = GridSettings(_size, _position, _width);
        grid = new Grid(_size);
        gridView = new GridView(grid, settings);
        EntityManager::Instance().RegisterEntity(*gridView);

        Cage* cage = new Cage();
        cage->Add(grid->GetCells({0, 1, 2}));
        Cage* cage2 = new Cage();
        cage2->Add(grid->GetCells({3, 4, 5, 12, 19, 20, 27, 34, 41, 40, 39, 38, 37, 36, 29, 22, 23, 24, 31}));
        // cage2->Add(grid->GetCell(1));
        cages = std::vector<Cage*>({cage, cage2});

        cageView = new CageView(&cages, settings);
        EntityManager::Instance().RegisterEntity(*cageView);

        // std::cout << "Cage is valid: " + std::to_string(cage->IsValid()) << std::endl;
        std::cout << "Cage: " + cage->ToString() << std::endl;
        std::cout << grid->ToString();
    }

private:
    GridSettings settings;
    Grid* grid;
    GridView* gridView;

    std::vector<Cage*> cages;
    CageView* cageView;

};
