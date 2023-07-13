#pragma once
#include "Grid.h"
#include "../Game/Entity.h"
#include "../Game/EntityManager.h"
#include "../Input/Button.h"

class GridView : public Entity {


protected:
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

private:
    unsigned width;
    Grid* grid;
    Button** buttons;
    sf::Vector2f position;

public:
    GridView(Grid* _grid, const unsigned _width, const unsigned _padding = 10, const sf::Vector2f _position = sf::Vector2f(0, 0)) : width(_width), grid(_grid), position(_position) {
        const unsigned gridSize = grid->GetSize();

        buttons = ButtonsFromGrid(_grid, _width, _padding, _position);
        for (unsigned int i = 0; i < grid->GetSize() * grid->GetSize(); ++i) {
            EntityManager::Instance().RegisterEntity(*buttons[i]);
        }
    }

    void Start() override;
    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;


    void SetGrid(Grid* _grid) {
        for (unsigned int i = 0; i < grid->GetSize() * grid->GetSize(); ++i) {
            delete buttons[i];
        }
        grid = _grid;
        delete[] buttons;
        buttons = new Button*[width * width];
    }

    void SetPosition(const float _x, const float _y) {
        position.x = _x;
        position.y = _y;
        const unsigned gridSize = grid->GetSize();
        for (unsigned int i = 0; i < gridSize * gridSize; i++) {
            sf::Vector2f buttonPos = buttons[i]->GetPosition();
            buttons[i]->SetPosition(buttonPos + position);
        }
    }

    static Button** ButtonsFromGrid(Grid* _grid, const unsigned _width, const unsigned _padding = 10, const sf::Vector2f _position = sf::Vector2f(0, 0)) {
        const unsigned gridSize = _grid->GetSize();

        const unsigned buttonSize = (_width - (_padding * (gridSize + 1))) / gridSize;
        std::cout << "Button size: " << buttonSize << std::endl;
        Button** _buttons = new Button*[gridSize * gridSize];
        for (unsigned int i = 0; i < gridSize * gridSize; i++) {
            Cell* cell = _grid->GetCell(i % gridSize, i / gridSize);
            _buttons[i] = new Button(buttonSize, buttonSize, std::to_string(cell->GetIndex()));
            unsigned xPos = _padding + (i % gridSize) * (buttonSize + _padding);
            unsigned yPos = _padding + (i / gridSize) * (buttonSize + _padding);
            _buttons[i]->SetPosition(_position.x + xPos, _position.y + yPos);
            // _buttons[i]->SetText(std::to_string(cell->GetValue()));
        }

        return _buttons;
    }
};
