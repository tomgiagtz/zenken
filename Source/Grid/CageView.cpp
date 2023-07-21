#include "CageView.h"

#include "../Theme/Theme.h"

void CageView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    for (const sf::RectangleShape& edge : edges) {
        _target.draw(edge, _states);
    }
}

void CageView::Start() {}
void CageView::Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {}



/*
void CageView::DrawEdge(CellSide _side, const Cell* _cell, std::array<bool, 4> _neighbors) {
    int edgeLength = gridSettings.cellSize + 2 * (gridSettings.edgeWidth + gridSettings.edgePadding);
    // if cell to the right has an upper edge, use padding
    const int edgeOffset = gridSettings.edgeWidth + gridSettings.edgePadding;
    const int sharedNeighborLength = gridSettings.cellSize + gridSettings.padding + gridSettings.edgeWidth;
    int neighborOffsetY = edgeOffset;


    sf::RectangleShape* edge;
    if (_side == Top || _side == Bottom) {
        //horiz edge
        if (_neighbors[Right] && _side == Top) edgeLength = sharedNeighborLength;
        if (_neighbors[Left] && _side == Bottom) edgeLength = sharedNeighborLength;
        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(edgeLength), static_cast<float>(gridSettings.edgeWidth)));
    } else {
        //vert edge
        if (_neighbors[Top]) {
            edgeLength = sharedNeighborLength;
            neighborOffsetY = 2 * (gridSettings.edgeWidth + gridSettings.edgePadding) + gridSettings.edgePadding;
        }
        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(gridSettings.edgeWidth), static_cast<float>(edgeLength)));
    }

    // top left of cell
    sf::Vector2f cellPos = gridSettings.GetCellPosition(_cell->GetIndex());
    int offset = edgeOffset;
    switch (_side) {
    case Top:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - edgeOffset);
        break;

    case Bottom:

        if (_neighbors[Left]) offset = 2 * (gridSettings.edgeWidth + gridSettings.edgePadding) + gridSettings.edgePadding;

    //don't use edgeOffset because edge origin is *top* left
        edge->setPosition(cellPos.x - offset, cellPos.y + gridSettings.cellSize + gridSettings.edgePadding);
        break;

    case Left:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - neighborOffsetY);
        break;
    case Right:
        edge->setPosition(cellPos.x + gridSettings.cellSize + gridSettings.edgePadding, cellPos.y - neighborOffsetY);
        break;
    default:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - edgeOffset);
    }

    // edge.setPosition(pos.x - edgeOffset, pos.y - edgeOffset);


    edge->setFillColor(Theme::Orange);
    edges.push_back(*edge);
}
*/
void CageView::DrawEdge(CellSide _side, const Cell* _cell, std::array<bool, 4> _neighbors) {
    sf::Color color = Theme::Orange;
    int edgeLength = gridSettings.cellSize + (2 * (gridSettings.edgeWidth + gridSettings.edgePadding) + gridSettings.edgeWidth);
    // if cell to the right has an upper edge, use padding
    const int edgeOffset = gridSettings.edgeWidth + gridSettings.edgePadding;
    const int gapLength = gridSettings.padding - (2 * (gridSettings.edgePadding + gridSettings.edgeWidth));
    int neighborOffsetY = edgeOffset;
    int leftShift = edgeOffset;
    int topShift = edgeOffset;

    sf::RectangleShape* edge;
    if (_side == Top || _side == Bottom) { //horiz edge

        if (_neighbors[Left] && _neighbors[Right]) {
            //normal padding
            leftShift = edgeOffset;
            //unless edge is not a neighbor
            if (!_neighbors[_side]) {
                std::cout << "hello0" << std::endl;
                leftShift = gridSettings.padding - edgeOffset + gridSettings.edgeWidth;
                edgeLength += gridSettings.padding - gridSettings.edgeWidth;
                color = Theme::Black;
            }
        } else if (_neighbors[Left]) { //left only
            leftShift = gridSettings.padding - edgeOffset + gridSettings.edgeWidth;
            edgeLength += edgeOffset + 2; // don't know why this +2 is needed :( think it's a rounding error?
        } else if (_neighbors[Right]) { //right only
            edgeLength += gapLength;
        } else { //no top nor bottom
            edgeLength -= gridSettings.edgeWidth;
        }


        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(edgeLength), static_cast<float>(gridSettings.edgeWidth)));
    } else { //vert edge

        if (_neighbors[Top] && _neighbors[Bottom]) {
            // if ()
            topShift = edgeOffset;
            //unless edge is not a neighbor
            if (!_neighbors[_side]) {
                std::cout << "hello0" << std::endl;
                topShift = gridSettings.padding - edgeOffset + gridSettings.edgeWidth;
                edgeLength += gridSettings.padding - gridSettings.edgeWidth;
                color = Theme::Black;
            }
        } else if (_neighbors[Top]) { //top only
            topShift = gridSettings.padding - edgeOffset;
            edgeLength += edgeOffset + 2; // don't know why this +2 is needed :( think it's a rounding error?
        } else if (_neighbors[Bottom]) { //bottom only
            edgeLength += gapLength;
        } else { //no top nor bottom
            edgeLength -= gridSettings.edgeWidth;
        }
        edge = new sf::RectangleShape(sf::Vector2f(static_cast<float>(gridSettings.edgeWidth), static_cast<float>(edgeLength)));
    }

    // top left of cell
    sf::Vector2f cellPos = gridSettings.GetCellPosition(_cell->GetIndex());
    int offset = edgeOffset;
    switch (_side) {
    case Top:
        edge->setPosition(cellPos.x - leftShift, cellPos.y - edgeOffset);
        break;

    case Bottom:

        //don't use edgeOffset because edge origin is *top* left
        edge->setPosition(cellPos.x - leftShift, cellPos.y + gridSettings.cellSize + gridSettings.edgePadding);
        break;

    case Left:
        edge->setPosition(cellPos.x - edgeOffset, cellPos.y - topShift);
        break;
    case Right:
        edge->setPosition(cellPos.x + gridSettings.cellSize + gridSettings.edgePadding, cellPos.y - topShift);
        break;
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
                DrawEdge(static_cast<CellSide>(i), cell, neighbors);
            }
        }
    }
}
