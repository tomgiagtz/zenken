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
