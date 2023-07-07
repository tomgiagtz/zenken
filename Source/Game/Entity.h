#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    virtual void Start() = 0;
    virtual void Update(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) = 0;


    bool IsActive() const {
        return active;
    }

    void SetActive(bool _active) {
        active = _active;
    }

    bool WillDestroy() {
        return shouldDestroy;
    }

    void Destroy() {
        active = false;
        shouldDestroy = true;
    }

private:
    bool active = true;
    bool shouldDestroy = false;
};
