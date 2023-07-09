#include "GridView.h"

void GridView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    for (unsigned int i = 0; i < grid->GetSize() * grid->GetSize(); ++i) {
        _target.draw(*buttons[i], _states);
    }
}

void GridView::Start() { }
void GridView::Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {}
