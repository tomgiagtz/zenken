#pragma once
#include <vector>

#include "../Models/Cage.h"
#include "../GridSettings.h"
#include "../../Game/Entity.h"

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

    void DrawEdge(CellSide _side, const Cell* _cell, std::array<bool, 4> _neighbors);

    CageView(Cage* _cage, const GridSettings& _gridSettings) :
        gridSettings(_gridSettings), cage(_cage) {
        DrawCage(cage);
    }

    void SetColor(sf::Color _color) {
        for (sf::RectangleShape& edge : edges) {
            edge.setFillColor(_color);
        }
    }

    void DrawCage(Cage* _cage);
    std::string GetLabelString();

private:
    GridSettings gridSettings;
    Cage* cage;
    std::vector<sf::RectangleShape> edges;
    sf::Text label;
};
