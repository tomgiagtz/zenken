#pragma once
#include "../GridSettings.h"
#include "../../Input/Button.h"
#include "../Models/Cell.h"
#include "../../Game/EntityManager.h"

struct GridSettings;

class CellView : public Entity {
protected:
    void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

public:
    void Start() override;
    void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) override;

private:
    Button* button;
    const GridSettings* settings;
    Cell* cell;
    void HandleKeyPressed(sf::Keyboard::Key _key);

public:
    CellView(Cell* _cell, const GridSettings* _settings, const std::function<void(int)>& _onSelectedCallback) :
        settings(_settings), cell(_cell) {
        const unsigned index = cell->GetIndex();
        const unsigned buttonSize = (settings->width - (settings->padding * (settings->gridSize + 1))) / settings->gridSize;
        const unsigned xPos = settings->padding + (index % settings->gridSize) * (buttonSize + settings->padding);
        const unsigned yPos = settings->padding + (index / settings->gridSize) * (buttonSize + settings->padding);

        button = new Button(index, buttonSize, buttonSize, cell->ToString());
        button->SetPosition(settings->position.x + xPos, settings->position.y + yPos);
        button->SetOnSelectedCallback(_onSelectedCallback);
        EntityManager::Instance().RegisterEntity(*button);
    }

    Button* GetButton() const {
        return button;
    }
};
