#pragma once
#include <SFML/Graphics.hpp>
// #include <memory>
#include <iostream>

#include "../Game/Entity.h"
#include "../Theme/Theme.h"

class Button : public Entity {


private:
    sf::RectangleShape* shape;
    bool isSelectable;
    bool isSelected = false;
    sf::Text* buttonText;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    unsigned int characterSize = 16;

    sf::Vector2f position;




    enum ButtonState {
        BTN_IDLE = 0,
        BTN_HOVER,
        BTN_PRESSED,
        BTN_SELECTED,
    };

    ButtonState state = BTN_IDLE;
    ButtonState prevState = BTN_IDLE;

    // Implement the sf::Drawable interface
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
        _target.draw(*shape, _states);
        _target.draw(*buttonText, _states);
    }


    void SetState(ButtonState _state);

public:
    // using memory and smart pointers
    // Button(std::unique_ptr<sf::Shape> _shape, sf::Color _idleColor = sf::Color::White, sf::Color _hoverColor = sf::Color::Red, sf::Color _activeColor = sf::Color::Black, std::string _text = "press", unsigned int _characterSize = 30 /*, sf::Font* font, */) : shape(std::move(_shape)), idleColor(_idleColor), hoverColor(_hoverColor), activeColor(_activeColor) {
    //     // Set button text
    //     // buttonText.setFont(*font);
    //     buttonText.setString(_text);
    //     buttonText.setFillColor(sf::Color::White);
    //     buttonText.setCharacterSize(_characterSize);
    //     buttonText.setPosition(
    //         this->shape->getPosition().x + (this->shape->getGlobalBounds().width / 2.f) - buttonText.getGlobalBounds().width / 2.f,
    //         this->shape->getPosition().y
    //     );
    //
    //     // Set color
    //     this->shape->setFillColor(_idleColor);
    // }

    Button(sf::RectangleShape* _shape, std::string _text = "press", unsigned int _characterSize = 48, bool _isSelectable = true, sf::Color _idleColor = Theme::Pale, sf::Color _hoverColor = Theme::Dun, sf::Color _activeColor = Theme::DarkDun) :
        shape(_shape), isSelectable(_isSelectable), idleColor(_idleColor), hoverColor(_hoverColor), activeColor(_activeColor), characterSize(_characterSize) {
        // Set button text
        position = _shape->getPosition();
        buttonText = new sf::Text();
        buttonText->setFont(Theme::Mono);
        buttonText->setString("Hello");
        buttonText->setFillColor(Theme::DarkCharcoal);
        buttonText->setCharacterSize(_characterSize);
        buttonText->setPosition(this->shape->getPosition().x + (this->shape->getGlobalBounds().width / 2.f) - buttonText->getGlobalBounds().width / 2.f, this->shape->getPosition().y);

        // Set color
        this->shape->setFillColor(_idleColor);
    }

    // default constructor
    Button(const float _xSize = 20, const float _ySize = 20, const std::string& _text = "press", bool _isSelectable = true, sf::Color _idleColor = Theme::Pale, sf::Color _hoverColor = Theme::Dun, sf::Color _activeColor = Theme::DarkDun) :
        isSelectable(_isSelectable), idleColor(_idleColor), hoverColor(_hoverColor), activeColor(_activeColor) {
        // Set button shape
        shape = new sf::RectangleShape(sf::Vector2f(_xSize, _ySize));
        position = shape->getPosition();
        characterSize = static_cast<int>(_ySize) - 12;
        // Set button text
        buttonText = new sf::Text();
        buttonText->setFont(Theme::Mono);
        buttonText->setString(_text);
        buttonText->setFillColor(Theme::DarkCharcoal);
        buttonText->setCharacterSize(characterSize);
        buttonText->setLineSpacing(0);
        buttonText->setLetterSpacing(0);
        // buttonText->setPosition(
        //     this->shape->getPosition().x + (this->shape->getGlobalBounds().width / 2.f) - buttonText->getGlobalBounds().width / 2.f,
        //     this->shape->getPosition().y + characterSize * 1.25f
        // );

        // Set color
        this->shape->setFillColor(_idleColor);
    }

    void SetPosition(sf::Vector2f _position);
    void SetPosition(float _x, float _y);
    sf::Vector2f GetPosition();

    void SetOrigin(float _x, float _y) {
        shape->setOrigin(_x, _y);
        buttonText->setOrigin(_x, _y);
    }

    void SetSize(float _x, float _y) {
        shape->setSize(sf::Vector2f(_x, _y));
    }

    void SetText(std::string _text) {
        buttonText->setString(_text);
        buttonText->setPosition(this->shape->getPosition().x + (this->shape->getGlobalBounds().width / 2.f) - buttonText->getGlobalBounds().width / 2.f, this->shape->getPosition().y);
    }

    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;

    ~Button() override {
        delete shape;
        delete buttonText;
    }

    bool IsPressed() const {
        return state == BTN_PRESSED;
    }

    bool IsSelected() const {
        return isSelectable && isSelected;
    };

    //if selectable use these
    void OnDeselected();
    void OnSelected();
    // otherwise use this
    void OnPressed();

    void Start() override;

};
