#pragma once
#include "Entity.h"

class EntityManager {
public:
    void UpdateEntities(float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event);
    void RenderEntities(sf::RenderWindow& _window);
    void RegisterEntity(Entity& _entity);

    static EntityManager& Instance() {
        static EntityManager* instance = new EntityManager();
        return *instance;
    }

private:
    EntityManager() = default;
    std::vector<Entity*> entities;
};
