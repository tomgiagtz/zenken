#pragma once

#include "EntityManager.h"
#include "../Input/Button.h"

class GameLoop {
private:
    bool isRunning = true;
    Button* button;
    sf::RenderWindow window;

    EntityManager* entityManager;

public:
    Button* CreateButton();
    void Init();

    bool IsRunning() const {
        return isRunning;
    }

    void Update();

    GameLoop() :
        button(CreateButton()), window(sf::VideoMode(1920, 1080), "ZenKen") {
        Init();
    }
};
