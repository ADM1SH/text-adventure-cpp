#include "../include/Game.h"

int main() {
    text_adventure::Game game;
    game.init();
    game.gameLoop();
    return 0;
}
