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
        fillColor = idleColor;
        break;
    case BTN_HOVER:
        fillColor = hoverColor;
        break;
    case BTN_PRESSED:
        fillColor = activeColor;
        OnPressed();
        break;
    case BTN_SELECTED:

        fillColor = selectedColor;
        OnSelected();
        break;
    }

    shape->setFillColor(fillColor);
}

void Button::Deselect() {
    isSelected = false;
    SetState(BTN_IDLE);
}

void Button::SetPosition(sf::Vector2f _position) {
    SetPosition(_position.x, _position.y);
}

void Button::SetPosition(float _x, float _y) {
    position.x = _x;
    position.y = _y;
    shape->setPosition(_x, _y);
    const float ShapeCenterX = _x + (this->shape->getGlobalBounds().width / 2.f);
    const float ShapeCenterY = _y + (this->shape->getGlobalBounds().height / 2.f);

    // const float TextCenterX = (buttonText->getGlobalBounds().width / 2.f);
    // const float TextCenterY = (buttonText->getGlobalBounds().height / 2.f) + characterSize / 2.f;

    sf::FloatRect textRect = buttonText->getLocalBounds();
    buttonText->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // buttonText->setOrigin(ShapeCenterX, ShapeCenterY);

    buttonText->setPosition(ShapeCenterX, ShapeCenterY);
    const float xTweak = 0.95f;
    const float yTweak = 1.f;
    // buttonText->setPosition(
    //     this->shape->getPosition().x + xTweak * (this->shape->getGlobalBounds().width / 2.f) - buttonText->getGlobalBounds().width / 2.f,
    //     this->shape->getPosition().y - (yTweak * (this->shape->getGlobalBounds().height / 2.f) - characterSize / 2.f)
    // );
}

sf::Vector2f Button::GetPosition() {
    return position;
}

bool blockInput = false;



void Button::Update(const float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {
    if (_event->type == sf::Event::MouseButtonReleased && state == BTN_PRESSED) {
        blockInput = false;
        std::cout << "mouse button released" << std::endl;
        if (IsSelected()) {
            isSelected = false;
            std::cout << "exit selected state" << std::endl;
            SetState(BTN_IDLE);
        } else if (!isSelected && isSelectable) {
            isSelected = true;
            std::cout << "enter selected state" << std::endl;
            SetState(BTN_SELECTED);
        }
        return;
    }
    if (blockInput) return;

    const auto localPosition = sf::Mouse::getPosition(*_window);
    // mouse over button
    if (!shape->getGlobalBounds().contains(localPosition.x, localPosition.y)) { //mouse outside button
        if (!isSelected && isSelectable) {
            // std::cout << "enter idle state" << std::endl;
            SetState(BTN_IDLE);
        }
    } else {
        std::cout << "mouse over button" << std::endl;
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::cout << "enter hover state" << std::endl;
            if (!IsSelected()) SetState(BTN_HOVER);
        } else {
            std::cout << "enter pressed state" << std::endl;
            SetState(BTN_PRESSED);
            blockInput = true;
        }
    }
}

void Button::OnDeselected() {
    std::cout << "Button::OnDeselected()" << std::endl;
}

void Button::OnSelected() {
    // std::cout << "Button::OnSelected()" << std::endl;
    if (onSelectedCallback) {
        onSelectedCallback(buttonId);
    }
}

void Button::OnPressed() {
    std::cout << "Button::OnPressed()" << std::endl;
}

void Button::Start() {
    // std::cout << "Button::Start()" << std::endl;
}
