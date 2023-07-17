#pragma once
#include <vector>

#include "Cage.h"
#include "GridSettings.h"
#include "../Game/Entity.h"

class CageView : public Entity {
    enum CellSide {
        Top,
        Right,
        Bottom,
        Left
    };

protected:
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

public:
    void Start() override;
    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;
    ~CageView() override = default;

    void DrawEdge(CellSide _side, const Cell* _cell);

    CageView(std::vector<Cage*>* _cages, const GridSettings& _gridSettings) :
        gridSettings(_gridSettings), cages(_cages) {
        Cell* cell1 = cages[0][0]->GetCell(0);
        DrawEdge(Top, cell1);
        DrawEdge(Bottom, cell1);
        DrawEdge(Left, cell1);
        DrawEdge(Right, cell1);
    }


    GridSettings gridSettings;
    std::vector<Cage*>* cages;
    std::vector<sf::RectangleShape> edges;
};
