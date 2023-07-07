#include "EntityManager.h"

void EntityManager::UpdateEntities(const float _deltaTime, const sf::RenderWindow* _window, const sf::Event* _event) {
    for (Entity* entity : entities) {
        if (entity->IsActive()) {
            entity->Update(_deltaTime, _window, _event);
        }
    }

    for (unsigned int i = 0; i < entities.size(); i++) {
        if (entities[i]->WillDestroy()) {
            // Delete the entity and remove it from the vector
            delete entities[i];
            entities.erase(entities.begin() + i);

            // Adjust the counter as we've just removed an element
            i--;
        }
    }
}

void EntityManager::RenderEntities(sf::RenderWindow& _window) {
    for (Entity* entity : entities) {
        if (entity->IsActive()) {
            _window.draw(*entity);
        }
    }
}

void EntityManager::RegisterEntity(Entity& _entity) {
    entities.push_back(&_entity);
    _entity.Start();
}
