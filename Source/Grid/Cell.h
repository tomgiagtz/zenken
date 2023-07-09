#pragma once
#include <SFML/System/Vector2.hpp>


class Cell {
public:
    Cell(const int _x = 0, const int _y = 0, const int _value = 0) : position(_x, _y), value(_value) { }

    sf::Vector2i GetPosition() const {
        return position;
    }

    unsigned int GetValue() const {
        return value;
    }

    void SetValue(const unsigned int _i) {
        value = _i;
    }

    void SetPosition(const unsigned _i, const unsigned _j) {
        position.x = _i;
        position.y = _j;
    }

private:
    sf::Vector2i position;
    unsigned int value;
};
