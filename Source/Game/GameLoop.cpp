#include "GameLoop.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

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
    // sf::RenderWindow window(sf::VideoMode(720, 480), "ZenKen");
    sf::CircleShape shape(100.f);


    shape.setFillColor(sf::Color::Green);

    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    // button->SetPosition(360, 240);
    // button->SetSize(240, 80);
    //
    // entityManager->RegisterEntity(*button);


    Grid* grid = new Grid();
    std::cout << grid->ToString();

    GridView* gridView = new GridView(500, grid);
    entityManager->RegisterEntity(*gridView);
    // grid->Clear();
    // std::cout << grid->ToString();
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
    window.clear(sf::Color::Black);
    entityManager->RenderEntities(window);
    // window.draw(*button);
    window.display();
}
