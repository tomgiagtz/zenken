#include <SFML/Graphics.hpp>

#include "Game/GameLoop.h"


int main() {
    GameLoop gameLoop;

    while (gameLoop.IsRunning()) {
        gameLoop.Update();
        // gameLoop.Render();
    }
    return 0;
}
