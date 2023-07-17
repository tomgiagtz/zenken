#pragma once
#include "Grid.h"
#include "GridSettings.h"
#include "../Game/Entity.h"
#include "../Game/EntityManager.h"
#include "../Input/Button.h"

class GridView : public Entity {


protected:
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

private:
    Grid* grid;
    Button** buttons;
    GridSettings gridSettings;

public:
    GridView(Grid* _grid, const unsigned _width, const unsigned _padding = 10, const sf::Vector2f _position = sf::Vector2f(0, 0)) :
        grid(_grid) {
        const unsigned gridSize = grid->GetSize();
        gridSettings = GridSettings(gridSize, _position, _width, _padding);
        buttons = ButtonsFromGrid(_grid, gridSettings);
        for (unsigned int i = 0; i < gridSettings.gridSize * gridSettings.gridSize; ++i) {
            EntityManager::Instance().RegisterEntity(*buttons[i]);
        }
    }

    GridView(Grid* _grid, const GridSettings& _gridSettings) :
        grid(_grid), gridSettings(_gridSettings) {
        buttons = ButtonsFromGrid(_grid, gridSettings);
        for (unsigned int i = 0; i < gridSettings.gridSize * gridSettings.gridSize; ++i) {
            EntityManager::Instance().RegisterEntity(*buttons[i]);
        }
    }

    ~GridView() override {
        for (unsigned int i = 0; i < gridSettings.gridSize * gridSettings.gridSize; ++i) {
            buttons[i]->Destroy();
        }
    }

    void Start() override;
    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;


    void SetGrid(Grid* _grid) {
        const unsigned gridSize2 = gridSettings.gridSize * gridSettings.gridSize;
        for (unsigned int i = 0; i < gridSize2; ++i) {
            delete buttons[i];
        }
        grid = _grid;
        delete[] buttons;
        buttons = new Button*[gridSize2];
    }

    void SetPosition(const unsigned _x, const unsigned _y) {
        gridSettings.position = sf::Vector2f(_x, _y);
        const unsigned gridSize = gridSettings.gridSize;
        for (unsigned int i = 0; i < gridSize * gridSize; i++) {
            sf::Vector2f buttonPos = buttons[i]->GetPosition();
            buttons[i]->SetPosition(buttonPos + gridSettings.position);
        }
    }

    static Button** ButtonsFromGrid(Grid* _grid, const GridSettings& _gridSettings) {
        const unsigned gridSize = _gridSettings.gridSize;
        const unsigned buttonSize = (_gridSettings.width - (_gridSettings.padding * (gridSize + 1))) / gridSize;
        std::cout << "Button size: " << buttonSize << std::endl;
        Button** _buttons = new Button*[gridSize * gridSize];
        for (unsigned int i = 0; i < gridSize * gridSize; i++) {
            Cell* cell = _grid->GetCell(i % gridSize, i / gridSize);
            _buttons[i] = new Button(buttonSize, buttonSize, std::to_string(cell->GetIndex()));
            unsigned xPos = _gridSettings.padding + (i % gridSize) * (buttonSize + _gridSettings.padding);
            unsigned yPos = _gridSettings.padding + (i / gridSize) * (buttonSize + _gridSettings.padding);
            _buttons[i]->SetPosition(_gridSettings.position.x + xPos, _gridSettings.position.y + yPos);
            // _buttons[i]->SetText(std::to_string(cell->GetValue()));
        }

        return _buttons;
    }
};
