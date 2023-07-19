#include "CageView.h"

#include "../Theme/Theme.h"

void CageView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    for (const sf::RectangleShape& edge : edges) {
        _target.draw(edge, _states);
    }
}

void CageView::Start() {}
void CageView::Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {}




void CageView::DrawEdge(CellSide _side, const Cell* _cell) {
    const int edgeLength = gridSettings.cellSize + gridSettings.padding; //(gridSettings.edgeWidth + gridSettings.edgePadding);
    // if cell to the right has an upper edge, use padding
    const int edgeOffset = gridSettings.edgeWidth + gridSettings.edgePadding;


    sf::RectangleShape* edge;
    if (_side == Top || _side == Bottom) {
        //horiz edge
        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(edgeLength), static_cast<float>(gridSettings.edgeWidth)));
    } else {
        //vert edge
        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(gridSettings.edgeWidth), static_cast<float>(edgeLength)));
    }

    // top left of cell
    sf::Vector2f cellPos = gridSettings.GetCellPosition(_cell->GetIndex());
    switch (_side) {
    case Top:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - edgeOffset);
        break;

    case Bottom:
        //don't use edgeOffset because edge origin is *top* left
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y + gridSettings.cellSize + gridSettings.edgePadding);
        break;

    case Left:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - edgeOffset);
        break;
    case Right:
        edge->setPosition(cellPos.x + gridSettings.cellSize + gridSettings.edgePadding, cellPos.y - edgeOffset);
        break;
    default:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - edgeOffset);
    }

    // edge.setPosition(pos.x - edgeOffset, pos.y - edgeOffset);


    edge->setFillColor(Theme::Orange);
    edges.push_back(*edge);
}

void CageView::DrawCage(Cage* _cage) {
    for (Cell* cell : _cage->GetCells()) {
        std::array<bool, 4> neighbors = _cage->GetCellNeighborsInCage(cell);
        for (unsigned i = 0; i < neighbors.size(); i++) {
            if (!neighbors[i]) {
                DrawEdge(static_cast<CellSide>(i), cell);
            }
        }
    }
}
