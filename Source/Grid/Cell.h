#pragma once
#include <SFML/System/Vector2.hpp>


class Cell {
public:
    Cell(const int _x = 0, const int _y = 0) : position(_x, _y) { }

    sf::Vector2i GetPosition() const {
        return position;
    }

    unsigned int GetValue() const {
        return value;
    }

private:
    sf::Vector2i position;
    unsigned int value;
};
