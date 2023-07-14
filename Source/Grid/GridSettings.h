#pragma once

struct GridSettings {
    unsigned gridSize;
    unsigned width;
    sf::Vector2f position;
    unsigned padding;
    unsigned buttonSize;



    GridSettings(const unsigned _gridSize = 3, const sf::Vector2f _position = sf::Vector2f(0, 0), const unsigned _width = 900, const unsigned _padding = 10):
        gridSize(_gridSize), width(_width), position(_position), padding(_padding) {
        buttonSize = (width - (padding * (_gridSize + 1))) / _gridSize;
    }


};
