#pragma once
#include "CellView.h"
#include "../Models/Grid.h"
#include "../GridSettings.h"
#include "../../Game/Entity.h"
#include "../../Game/EntityManager.h"
#include "../../Input/Button.h"

class GridView : public Entity {


protected:
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

private:
    Grid* grid;
    std::vector<Button*> buttons;
    std::vector<CellView*> cellViews;
    GridSettings gridSettings;

public:
    GridView(Grid* _grid, const unsigned _width, const unsigned _padding = 10, const sf::Vector2f _position = sf::Vector2f(0, 0)) :
        grid(_grid) {
        const unsigned gridSize = grid->GetSize();
        gridSettings = GridSettings(gridSize, _position, _width, _padding);
        cellViews = CellViewsFromGrid(_grid, &gridSettings);
    }

    GridView(Grid* _grid, const GridSettings& _gridSettings) :
        grid(_grid), gridSettings(_gridSettings) {
        cellViews = CellViewsFromGrid(_grid, &gridSettings);
    }

    ~GridView() override {
        for (unsigned int i = 0; i < gridSettings.gridSize * gridSettings.gridSize; ++i) {
            buttons[i]->Destroy();
        }
    }

    void Start() override;
    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;


    // void SetGrid(Grid* _grid);

    void SetPosition(float _x, float _y);

    std::vector<CellView*> CellViewsFromGrid(Grid* _grid, const GridSettings* _gridSettings);
    void OnButtonSelected(unsigned _index);
};
