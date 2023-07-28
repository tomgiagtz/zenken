#include "Cage.h"

#include <iostream>
#include <string>

//naive iteration implementation
bool Cage::IsValid() {
    if (cells.empty()) {
        return false;
    }

    if (cells.size() == 1) {
        return true;
    }
    //constant should only be one cell
    if (operation == Constant) {
        return false;
    }

    //check if all cells are contiguous
    for (const Cell* currCell : cells) {
        std::cout << "Checking cell at index: " << std::to_string(currCell->GetIndex()) << ". ";
        bool hasNeighbor = false;
        const sf::Vector2u currPosition = currCell->GetPosition();
        for (const Cell* potentialNeighbor : cells) {
            if (currCell == potentialNeighbor) continue;
            const sf::Vector2u potentialNeighborPosition = potentialNeighbor->GetPosition();
            const bool isHoriz = abs(static_cast<int>(currPosition.y - potentialNeighborPosition.y)) <= 1;
            const bool isVert = abs(static_cast<int>(currPosition.x - potentialNeighborPosition.x)) <= 1;

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

bool Cage::IsFull() {
    for (Cell* _cell : cells) {
        if (_cell->GetValue() == 0) {
            return false;
        }
    }
    return true;
}

bool Cage::IsPossible() {
    return true;
}

bool Cage::IsCorrect() {
    if (!IsFull()) {
        return false;
    }
    int result = 0;
    int index = 0;
    int maxValue = GetMax();
    int maxIndex = GetMaxIndex();
    // std::cout << "Max: " << maxValue << ", (" << maxIndex << ")\n";
    for (Cell* _cell : cells) {
        const unsigned value = _cell->GetValue();
        switch (operation) {
        case Constant:
            break;
        case Addition:
            result += value;
            break;
        case Subtraction:
            if (index == 0) {
                result = maxValue;
            }
            if (index == maxIndex) break;

            result -= value;
            break;
        case Multiplication:
            if (index == 0) {
                result = value;
                break;
            }
            result *= value;
        // early exit since multiply always increases or stays the same
            if (result > target) return false;
            break;
        case Division:
            if (index == 0) {
                result = maxValue;
            }
            if (index == maxIndex) break;
            result /= value;
        }
        index++;
    }
    return (result == target);
}



std::array<bool, 4> Cage::GetCellNeighborsInCage(const Cell* _cell) {
    std::array<bool, 4> res = {false};
    const sf::Vector2u currPosition = _cell->GetPosition();
    //up right down left
    res[0] = this->Contains(currPosition - sf::Vector2u(0, 1));
    res[1] = this->Contains(currPosition + sf::Vector2u(1, 0));
    res[2] = this->Contains(currPosition + sf::Vector2u(0, 1));
    res[3] = this->Contains(currPosition - sf::Vector2u(1, 0));
    return res;
}

/**
 * Cage Operations
 * 
 */
unsigned Cage::GetMax() {
    unsigned res = 0;
    for (Cell* cell : cells) {
        if (cell->GetValue() > res) {
            res = cell->GetValue();
        }
    }
    return res;
}

unsigned Cage::GetMaxIndex() {
    unsigned res = 0;
    unsigned index = 0;
    unsigned maxIndex = 0;
    for (Cell* cell : cells) {
        if (cell->GetValue() > res) {
            res = cell->GetValue();
            maxIndex = index;
        }
        index++;
    }
    return maxIndex;
}
