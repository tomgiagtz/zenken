#pragma once
#include <vector>
#include "../../Game/EntityManager.h"
#include "../Models/Cage.h"
#include "../Models/Grid.h"
#include "../Views/GridView.h"
#include "../Views/CageView.h"
#include "../Models/Puzzle.h"

class PuzzleView {
public:
    PuzzleView(sf::Vector2f _position, const unsigned int _size = 3, const unsigned int _width = 900) {
        settings = GridSettings(_size, _position, _width);
        puzzle = new Puzzle(_size);
        gridView = new GridView(puzzle->GetGrid(), settings);
        EntityManager::Instance().RegisterEntity(*gridView);

        std::vector<Cage*> cages = *puzzle->GetCages();
        for (Cage* cage : cages) {
            CageView* cageView = new CageView(cage, settings);
            EntityManager::Instance().RegisterEntity(*cageView);
            cageViews.push_back(cageView);
        }

        // std::cout << "Cage is valid: " + std::to_string(cage->IsValid()) << std::endl;
        // std::cout << "Cage: " + cage->ToString() << std::endl;
        std::cout << puzzle->GetGrid()->ToString();
    }

private:
    GridSettings settings;
    GridView* gridView;

    // std::vector<Cage*> cages;
    std::vector<CageView*> cageViews;

    Puzzle* puzzle;

};
