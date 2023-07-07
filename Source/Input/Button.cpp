#include "Button.h"

void Button::SetState(ButtonState _state) {
    if (_state == state) {
        return;
    }
    prevState = state;
    state = _state;

    sf::Color fillColor;
    sf::Color selectedColor = Theme::Charcoal;
    switch (state) {
    case BTN_IDLE:
        if (IsSelected()) {
            fillColor = selectedColor;
            break;
        }
        fillColor = idleColor;
        break;
    case BTN_HOVER:
        fillColor = hoverColor;
        break;
    case BTN_PRESSED:
        if (IsSelected()) {
            isSelected = false;
            fillColor = activeColor;
            OnDeselected();
            break;
        }
        fillColor = activeColor;
        OnPressed();
        break;
    case BTN_SELECTED:
        isSelected = true;
        fillColor = selectedColor;
        OnSelected();
        break;
    default:
        fillColor = sf::Color::Red;
        break;
    }

    shape->setFillColor(fillColor);
}

bool blockInput = false;



void Button::Update(const float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {
    if (_event->type == sf::Event::MouseButtonReleased) {
        blockInput = false;
    }
    if (blockInput) {
        // blockInput = false;
        return;
    }
    const auto localPosition = sf::Mouse::getPosition(*_window);
    if (!shape->getGlobalBounds().contains(localPosition.x, localPosition.y)) {
        SetState(BTN_IDLE);
        return;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        SetState(BTN_HOVER);
        return;
    }

    blockInput = true;


    if (isSelectable) {
        if (!isSelected) {
            SetState(BTN_SELECTED);
        } else {
            SetState(BTN_PRESSED);
        }
    } else {
        SetState(BTN_PRESSED);
    }
}

void Button::OnDeselected() {
    std::cout << "Button::OnDeselected()" << std::endl;
}

void Button::OnSelected() {
    std::cout << "Button::OnSelected()" << std::endl;
}

void Button::OnPressed() {
    std::cout << "Button::OnPressed()" << std::endl;
}

void Button::Start() {
    std::cout << "Button::Start()" << std::endl;
}
