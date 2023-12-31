﻿#include "Grid.h"

std::vector<Cell*> Grid::GetCells(std::initializer_list<unsigned int> _indices) {
    std::vector<Cell*> res;
    std::cout << "Adding new cage: ";
    for (const unsigned int index : _indices) {
        if (index >= size * size) {
            std::cout << "Index out of bounds: " << index << std::endl;
            continue;
        }
        std::cout << std::to_string(index) + " ";
        res.push_back(GetCell(index));
    }
    std::cout << std::endl;

    return res;
}
