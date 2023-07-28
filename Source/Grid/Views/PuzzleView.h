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

        cageView = new CageView(puzzle->GetCages(), settings);
        EntityManager::Instance().RegisterEntity(*cageView);

        // std::cout << "Cage is valid: " + std::to_string(cage->IsValid()) << std::endl;
        // std::cout << "Cage: " + cage->ToString() << std::endl;
        std::cout << puzzle->GetGrid()->ToString();
    }

private:
    GridSettings settings;
    GridView* gridView;

    // std::vector<Cage*> cages;
    CageView* cageView;

    Puzzle* puzzle;

};
