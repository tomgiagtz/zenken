﻿#include "Cage.h"

#include <iostream>
#include <string>

//naiive iteration implementation
bool Cage::IsValid() {
    if (cells.empty()) {
        return false;
    }

    if (cells.size() == 1) {
        return true;
    }

    //Set already guarantees uniqueness
    // //check if all cells are unique
    // for (unsigned int i = 0; i < cells.size(); ++i) {
    //     for (unsigned int j = i + 1; j < cells.size(); ++j) {
    //         if (cells[i] == cells[j]) {
    //             return false;
    //         }
    //     }
    // }

    //check if all cells are contiguous
    for (const Cell* currCell : cells) {
        std::cout << "Checking cell at index: " << std::to_string(currCell->GetIndex()) << ". ";
        bool hasNeighbor = false;
        const sf::Vector2i currPosition = currCell->GetPosition();
        for (const Cell* potentialNeighbor : cells) {
            if (currCell == potentialNeighbor) continue;
            const sf::Vector2i potentialNeighborPosition = potentialNeighbor->GetPosition();
            const bool isHoriz = abs(currPosition.y - potentialNeighborPosition.y) <= 1;
            const bool isVert = abs(currPosition.x - potentialNeighborPosition.x) <= 1;

            if (isHoriz && isVert) {
                hasNeighbor = true;
                std::cout << "Cell " << currCell->GetIndex() << " has neighbor " << potentialNeighbor->GetIndex() << "\n";
                break;
            }
        }
        if (!hasNeighbor) {
            std::cout << "Cell " << currCell->GetIndex() << " has no neighbors\n";
            return false;
        }
    }
    return true;
}