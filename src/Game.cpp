#include "../include/Game.h"
#include "../include/Item.h"
#include "../include/Room.h"
#include <iostream>

namespace text_adventure {

    Game::Game()
        : isRunning(false), currentRoom(nullptr) {}

    Game::~Game() {
        for (auto room : rooms) {
            delete room;
        }
    }

    void Game::init() {
        isRunning = true;

        // Create rooms
        Room* entrance = new Room("Dungeon Entrance", "A dark stone chamber lit by flickering torches.");
        Room* hallway = new Room("Hallway", "A narrow passage leading deeper underground.");
        Room* treasureRoom = new Room("Treasure Room", "A small room filled with treasure!");
        rooms.push_back(entrance);
        rooms.push_back(hallway);
        rooms.push_back(treasureRoom);

        // Connect rooms
        entrance->connect(hallway, "north");
        hallway->connect(entrance, "south");

        // Create items
        Item* torch = new Item("torch", "A wooden torch that lights your path.", true, true);
        entrance->addItem(torch);

        // Set starting room
        currentRoom = entrance;
        player.currentRoom = currentRoom;
    }

    void Game::gameLoop() {
        while (isRunning) {
            renderRoom();
            std::string input = parser.getInput();
            Command cmd = parser.parse(input);
            processCommand(cmd);
        }
    }

    void Game::renderRoom() const {
        currentRoom->describe();
    }

    void Game::processCommand(const Command &cmd) {
        if (cmd.action == "go") {
            Room* nextRoom = currentRoom->getExit(cmd.target);
            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
                player.move(nextRoom);
                std::cout << "You enter the " << nextRoom->name << "." << std::endl;
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (cmd.action == "look") {
            renderRoom();
        } else if (cmd.action == "take") {
            Item* itemToTake = nullptr;
            for (auto item : currentRoom->items) {
                if (item->name == cmd.target) {
                    itemToTake = item;
                    break;
                }
            }
            if (itemToTake != nullptr) {
                player.take(itemToTake);
            } else {
                std::cout << "That item isn't here." << std::endl;
            }
        } else if (cmd.action == "inventory") {
            player.showInventory();
        } else if (cmd.action == "use") {
            if (player.hasItem(cmd.target)) {
                Item* item = player.getItem(cmd.target);
                item->use(*currentRoom);

                // Handle special torch logic
                if (item->name == "torch" && currentRoom->name == "Hallway") {
                    Room* hallway = nullptr;
                    Room* treasureRoom = nullptr;
                    for (auto r : rooms) {
                        if (r->name == "Hallway") hallway = r;
                        if (r->name == "Treasure Room") treasureRoom = r;
                    }
                    if (hallway && treasureRoom) {
                        hallway->connect(treasureRoom, "east");
                    }
                }
            } else {
                std::cout << "You don't have that item." << std::endl;
            }
        } else if (cmd.action == "quit" || cmd.action == "exit") {
            endGame();
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    void Game::endGame() {
        isRunning = false;
        std::cout << "Thanks for playing!" << std::endl;
    }

}
