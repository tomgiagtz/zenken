#pragma once
#include <SFML/System/Vector2.hpp>


class Cell {
public:
    //these default values are trash, because default constructor is used in std::vector<Cell>
    Cell(const unsigned int _x = 0, const unsigned int _y = 0, const unsigned int _gridSize = 0, const unsigned int _value = 0) :
        position(_x, _y), gridSize(_gridSize), value(_value) { }

    sf::Vector2i GetPosition() const {
        return position;
    }

    unsigned int GetIndex() const {
        return position.y * gridSize + position.x;
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

    bool operator ==(const Cell& _other) const {
        return position == _other.position;
    }

    bool operator <(const Cell& _other) const {
        return GetIndex() < _other.GetIndex();
    }

    Cell& operator=(const Cell& other) {
        if (this != &other) {
            this->position = other.position;
            this->gridSize = other.gridSize;
            this->value = other.value;
        }
        return *this;
    }

private:
    sf::Vector2i position;
    unsigned int gridSize;
    unsigned int value;
};
