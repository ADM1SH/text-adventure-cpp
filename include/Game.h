#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Room.h"
#include "Parser.h"
#include "Command.h"
#include "SaveSystem.h"

namespace text_adventure {
    class Game {
    public:
        bool isRunning;
        Player player;
        std::vector<Room*> rooms;
        std::vector<Item*> allItems;
        Parser parser;
        Room* currentRoom;
        SaveSystem saveSystem;

        Game();
        ~Game();

        void init();
        void gameLoop();
        void renderRoom() const;
        void processCommand(const Command &cmd);
        void endGame();
    };
}

#endif // GAME_H
