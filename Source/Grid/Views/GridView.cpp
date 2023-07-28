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

Button* selectedButton = nullptr;

void GridView::OnButtonSelected(const unsigned _index) {
    if (selectedButton) {
        if (_index == selectedButton->GetID()) return;
        std::cout << "Deselecting button " << selectedButton->GetID() << std::endl;
        selectedButton->Deselect();
    }
    std::cout << "Button " + std::to_string(_index) + " selected" << std::endl;

    selectedButton = cellViews[_index]->GetButton();
}


std::vector<CellView*> GridView::CellViewsFromGrid(Grid* _grid, const GridSettings* _gridSettings) {
    const unsigned gridSize = _gridSettings->gridSize;

    std::vector<CellView*> _cellViews;
    cellViews.reserve(gridSize * gridSize);
    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        Cell* cell = _grid->GetCell(i);
        // _buttons.push_back(new Button(cell->GetIndex(), buttonSize, buttonSize, cell->ToString()));
        Button::Callback callback = [this](const unsigned id) {
            OnButtonSelected(id);
        };
        CellView* currCellView = new CellView(cell, _gridSettings, callback);
        _cellViews.push_back(currCellView);
        EntityManager::Instance().RegisterEntity(*currCellView);

        // _buttons[i]->SetPosition(_gridSettings->position.x + xPos, _gridSettings->position.y + yPos);
        // _buttons[i]->SetText(std::to_string(cell->GetValue()));
    }

    return _cellViews;
}
