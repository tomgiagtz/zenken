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

public:
    GridView(unsigned _width, Grid* _grid) : width(_width), grid(_grid) {
        const unsigned gridSize = grid->GetSize();

        buttons = ButtonsFromGrid(_width, _grid);
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

    static Button** ButtonsFromGrid(unsigned _width, Grid* grid) {
        const unsigned gridSize = grid->GetSize();
        const unsigned padding = 10;

        const unsigned buttonSize = (_width - (padding * (gridSize + 1))) / gridSize;

        Button** _buttons = new Button*[gridSize * gridSize];
        for (unsigned int i = 0; i < gridSize * gridSize; i++) {
            Cell* cell = grid->GetCell(i % gridSize, i / gridSize);
            _buttons[i] = new Button(buttonSize, buttonSize, std::to_string(cell->GetValue()));
            _buttons[i]->SetPosition(padding + (i % gridSize) * (buttonSize + padding), padding + (i / gridSize) * (buttonSize + padding));
            // _buttons[i]->SetText(std::to_string(cell->GetValue()));
        }

        return _buttons;
    }
};
