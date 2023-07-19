﻿#pragma once
#include <vector>
#include "EntityManager.h"
#include "../Grid/Cage.h"
#include "../Grid/Grid.h"
#include "../Grid/GridView.h"
#include "../Grid/CageView.h"

class Puzzle {
public:
    Puzzle(sf::Vector2f _position, const unsigned int _size = 3, const unsigned int _width = 900) {
        settings = GridSettings(_size, _position, _width);
        grid = new Grid(_size);
        gridView = new GridView(grid, settings);
        EntityManager::Instance().RegisterEntity(*gridView);

        Cage* cage = new Cage();
        cage->Add(grid->GetCell(0));
        cage->Add(grid->GetCell(1));
        cage->Add(grid->GetCell(2));
        cage->Add(grid->GetCell(7));
        cages = std::vector<Cage*>({cage});

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
