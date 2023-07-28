#include "GridView.h"

void GridView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    for (Button* button : buttons) {
        _target.draw(*button, _states);
    }
}

void GridView::Start() { }
void GridView::Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {}

// old array version
// void GridView::SetGrid(Grid* _grid) {
//     const unsigned gridSize2 = gridSettings.gridSize * gridSettings.gridSize;
//     for (unsigned int i = 0; i < gridSize2; ++i) {
//         delete buttons[i];
//     }
//     grid = _grid;
//     delete[] buttons;
//     buttons = new Button*[gridSize2];
// }

void GridView::SetPosition(const float _x, const float _y) {
    gridSettings.position = sf::Vector2f(_x, _y);
    const unsigned gridSize = gridSettings.gridSize;
    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        sf::Vector2f buttonPos = buttons[i]->GetPosition();
        buttons[i]->SetPosition(buttonPos + gridSettings.position);
    }
}

void GridView::OnButtonSelected(int _index) {
    std::cout << "Button " + std::to_string(_index) + " selected" << std::endl;
}

std::vector<Button*> GridView::ButtonsFromGrid(Grid* _grid, const GridSettings& _gridSettings) {
    const unsigned gridSize = _gridSettings.gridSize;
    const unsigned buttonSize = (_gridSettings.width - (_gridSettings.padding * (gridSize + 1))) / gridSize;
    std::cout << "Button size: " << buttonSize << std::endl;
    std::vector<Button*> _buttons;
    buttons.reserve(gridSize * gridSize);
    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        Cell* cell = _grid->GetCell(i % gridSize, i / gridSize);
        _buttons.push_back(new Button(cell->GetIndex(), buttonSize, buttonSize, std::to_string(cell->GetIndex())));
        _buttons[i]->SetOnSelectedCallback([this](int id) {
            OnButtonSelected(id);
        });
        unsigned xPos = _gridSettings.padding + (i % gridSize) * (buttonSize + _gridSettings.padding);
        unsigned yPos = _gridSettings.padding + (i / gridSize) * (buttonSize + _gridSettings.padding);
        _buttons[i]->SetPosition(_gridSettings.position.x + xPos, _gridSettings.position.y + yPos);
        // _buttons[i]->SetText(std::to_string(cell->GetValue()));
    }

    return _buttons;
}
