#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>


class Cell {
public:
    //these default values are trash, because default constructor is used in std::vector<Cell>
    Cell(const unsigned _x = 0, const unsigned _y = 0, const unsigned int _gridSize = 0, const unsigned int _value = 0) :
        position(_x, _y), gridSize(_gridSize), value(_value) { }

    sf::Vector2u GetPosition() const {
        return position;
    }

    unsigned int GetIndex() const {
        return static_cast<int>(position.y * gridSize + position.x);
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

    //tostring
    std::string ToString() const {
        if (value == 0) {
            return " ";
        }
        return std::to_string(value);
    }

    bool operator ==(const Cell& _other) const {
        return position == _other.position && gridSize == _other.gridSize && value == _other.value;
    }

    bool operator <(const Cell& _other) const {
        return GetIndex() < _other.GetIndex();
    }

    Cell& operator=(const Cell& _other) {
        if (this != &_other) {
            this->position = _other.position;
            this->gridSize = _other.gridSize;
            this->value = _other.value;
        }
        return *this;
    }

private:
    sf::Vector2u position;
    unsigned int gridSize;
    unsigned int value;


};
