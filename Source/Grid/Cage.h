#pragma once

//using set for uniqueness
// index is the key for a set of cells, retrieved by a position in the grid, converted to an index
// uniqueness is enforced by the set
// lowest index will always be the top most then left most (for placing operation symbol)
#include <set>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <cstdarg>

#include "Cell.h"

class Cage {
    struct CompareCells {
        bool operator()(const Cell* lhs, const Cell* rhs) const {
            // Here we dereference the pointers and compare the Cell objects.
            // The '<' operator must be correctly defined for the Cell class.
            return *lhs < *rhs;
        }
    };

    std::set<Cell*, CompareCells> cells;
    char operation = 'c';

public:
    Cage() = default;
    /**
     * \brief IsValid checks if the cage is geometrically valid, every cell is unique, and the cage is contiguous
     * \return bool whether the cage is valid or not
     */
    bool IsValid();

    bool Contains(Cell* _cell) {
        return cells.find(_cell) != cells.end();
    }

    bool Contains(sf::Vector2u _position) {
        for (Cell* cell : cells) {
            if (cell->GetPosition() == _position) {
                return true;
            }
        }
        return false;
    }

    std::array<bool, 4> GetCellNeighborsInCage(const Cell* _cell);

    bool Add(Cell* _cell) {
        cells.insert(_cell);
        if (IsValid()) {
            return true;
        }
        cells.erase(_cell);
        return false;
    }

    void Add(std::vector<Cell*> _cells) {
        for (Cell* cell : _cells) {
            this->Add(cell);
        }
    }


    void UnsafeAdd(Cell* _cell) {
        cells.insert(_cell);
    }

    std::string ToString() {
        std::string result = "[";
        if (cells.empty()) {
            return result + "]";
        }
        for (Cell* cell : cells) {
            result += std::to_string(cell->GetIndex()) + ", ";
        }
        result.replace(result.length() - 2, 2, "]");
        return result;
    }

    Cell* GetCell(const unsigned int _index) {
        if (_index >= cells.size()) {
            throw std::out_of_range("Index out of range");
        }
        unsigned int i = 0;
        for (Cell* cell : cells) {
            if (i == _index) {
                return cell;
            }
            i++;
        }
        return nullptr;
    }

    std::set<Cell*, CompareCells> GetCells() {
        return cells;
    }

    unsigned GetSize() {
        return cells.size();
    }







};
