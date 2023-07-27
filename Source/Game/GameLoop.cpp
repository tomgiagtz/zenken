#include "GameLoop.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Puzzle.h"
#include "../Grid/Cage.h"
#include "../Grid/Grid.h"
#include "../Grid/GridView.h"

Button* GameLoop::CreateButton() {
    sf::Vector2f squareSize(240.f, 120.f);
    sf::RectangleShape* square = new sf::RectangleShape(squareSize);
    // square->setPosition(sf::Vector2f(300, 180));
    // square.setFillColor(sf::Color::Red);
    // square.setOrigin(squareSize.x * 0.5f, squareSize.y * 0.5f);
    // sf::Shape& shape = square;
    return new Button(square);
}

void GameLoop::Init() {
    isRunning = true;
    entityManager = &EntityManager::Instance();
    Theme::LoadFonts();
    window.clear(Theme::DarkDun);

    sf::Vector2u size = window.getSize();
    sf::Vector2f puzzlePosition = sf::Vector2f(size.x - 900 - 88, size.y / 2 - 450.f);

    Puzzle puzzle = Puzzle(puzzlePosition, 7, 900);
}

void GameLoop::Update() {
    sf::Clock clock;
    sf::Event event;


    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            isRunning = false;
            window.close();
        }
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();
        entityManager->UpdateEntities(deltaTime, &window, &event);

        // button->Update(&window, &event);
    }


    //test
    window.clear(Theme::DarkCharcoal);
    entityManager->RenderEntities(window);
    // window.draw(*button);
    window.display();
}
