#include "Theme.h"

#include <iostream>


sf::Color Theme::Black = sf::Color(0, 0, 0, 255);
sf::Color Theme::White = sf::Color(255, 255, 255, 255);
sf::Color Theme::Pale = sf::Color(239, 208, 202, 255);
sf::Color Theme::Dun = sf::Color(193, 188, 172, 255);
sf::Color Theme::DarkDun = sf::Color(116, 113, 103, 255);
sf::Color Theme::Orange = sf::Color(242, 76, 0, 255);
sf::Color Theme::Charcoal = sf::Color(61, 84, 103, 255);
sf::Color Theme::DarkCharcoal = sf::Color(30, 42, 52, 255);
sf::Color Theme::Red = sf::Color(231, 29, 54, 255);

sf::Font Theme::Primary;
sf::Font Theme::Secondary;

bool Theme::LoadFonts() {
    if (!Primary.loadFromFile("Source/Resources/Fonts/acumin-pro-bold.ttf")) {
        // handle error
        std::cout << "Error loading Primary font" << std::endl;
        return false;
    }
    if (!Secondary.loadFromFile("Source/Resources/Fonts/mont-gilnoza-regular.ttf")) {
        // handle error
        std::cout << "Error loading Secondary font" << std::endl;
        return false;
    }
    return true;
}
