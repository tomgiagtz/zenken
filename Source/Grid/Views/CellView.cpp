#include "CellView.h"

void CellView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    _target.draw(*button, _states);
}

void CellView::Start() {}

void CellView::Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {
    if (button->IsSelected() && _event->type == sf::Event::KeyPressed) {
        // std::cout << "CellView::Update: " << button->GetID() << std::endl;
        HandleKeyPressed(_event->key.code);
    }
}

void CellView::HandleKeyPressed(const sf::Keyboard::Key _key) {
    // std::cout << "CellView::HandleKeyPressed: " << _key << std::endl;
    if (_key == -1) {
        return;
    }
    switch (_key) {
    case sf::Keyboard::Delete:
    case sf::Keyboard::Backspace:
    case sf::Keyboard::Numpad0:
    case sf::Keyboard::Num0:
        cell->SetValue(0);
        break;
    case sf::Keyboard::Numpad1:
    case sf::Keyboard::Num1:
        cell->SetValue(1);
        break;
    case sf::Keyboard::Numpad2:
    case sf::Keyboard::Num2:
        cell->SetValue(2);
        break;
    case sf::Keyboard::Numpad3:
    case sf::Keyboard::Num3:
        cell->SetValue(3);
        break;
    case sf::Keyboard::Numpad4:
    case sf::Keyboard::Num4:
        cell->SetValue(4);
        break;
    case sf::Keyboard::Numpad5:
    case sf::Keyboard::Num5:
        cell->SetValue(5);
        break;
    case sf::Keyboard::Numpad6:
    case sf::Keyboard::Num6:
        cell->SetValue(6);
        break;
    case sf::Keyboard::Numpad7:
    case sf::Keyboard::Num7:
        cell->SetValue(7);
        break;
    case sf::Keyboard::Numpad8:
    case sf::Keyboard::Num8:
        cell->SetValue(8);
        break;
    case sf::Keyboard::Numpad9:
    case sf::Keyboard::Num9:
        cell->SetValue(9);
        break;
    default:
        return;
    }

    button->SetText(cell->ToString());
    // std::cout << "CellView::HandleKeyPressed: " << cell->ToString() << std::endl;
}
