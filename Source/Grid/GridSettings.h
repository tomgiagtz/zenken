#pragma once
#include "Grid.h"

struct GridSettings {
    unsigned gridSize;
    unsigned width;
    sf::Vector2f position;
    int padding;
    unsigned cellSize;
    unsigned edgeWidth;
    unsigned edgePadding;



    /**
     * \brief Struct for details about a specific grid
     * \param _gridSize Number of cells in a row/column
     * \param _position top left of grid
     * \param _width size of square
     * \param _padding space between cells
     */
    GridSettings(const unsigned _gridSize = 3, const sf::Vector2f _position = sf::Vector2f(0, 0), const unsigned _width = 900, const int _padding = 48, const unsigned _edgeWidth = 4, const unsigned _edgePadding = 10) :
        gridSize(_gridSize), width(_width), position(_position), padding(_padding), edgeWidth(_edgeWidth), edgePadding(_edgePadding) {
        cellSize = (width - (padding * (_gridSize + 1))) / _gridSize;
    }

    sf::Vector2f GetCellPosition(const unsigned _i, const unsigned _j) const {
        return sf::Vector2f(position.x + padding + (_i * (cellSize + padding)), position.y + padding + (_j * (cellSize + padding)));
    }

    sf::Vector2f GetCellPosition(const unsigned _index) const {
        const sf::Vector2i cellPosition = Grid::PositionFromIndex(_index, gridSize);
        return GetCellPosition(cellPosition.x, cellPosition.y);
    }
};
