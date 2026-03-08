#include "../include/Game.h"
#include "../include/WorldLoader.h"
#include "../include/Item.h"
#include "../include/NPC.h"
#include "../include/Room.h"
#include "../include/Event.h"
#include <iostream>
#include <sstream>

namespace text_adventure {

    Game::Game()
        : isRunning(false), currentRoom(nullptr) {}

    Game::~Game() {
        for (auto room : rooms) {
            for (auto npc : room->npcs) {
                delete npc;
            }
            delete room;
        }
        for (auto item : allItems) {
            delete item;
        }
    }

    void Game::init() {
        isRunning = true;
        WorldLoader worldLoader;
        worldLoader.loadWorld("data/world.txt", rooms, allItems);

        if (!rooms.empty()) {
            currentRoom = rooms[0];
            player.currentRoom = currentRoom;
        } else {
            std::cerr << "Error: No rooms loaded. Exiting." << std::endl;
            isRunning = false;
        }
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
        } else if (cmd.action == "drop") {
            if (player.hasItem(cmd.target)) {
                Item* itemToDrop = player.getItem(cmd.target);
                player.drop(itemToDrop);
            } else {
                std::cout << "You don't have that item." << std::endl;
            }
        } else if (cmd.action == "inventory") {
            player.showInventory();
        } else if (cmd.action == "use") {
            if (player.hasItem(cmd.target)) {
                Item* item = player.getItem(cmd.target);
                item->use(*currentRoom);

                if (item->isUsable && item->useTarget == currentRoom->name) {
                    std::stringstream ss(item->useEffect);
                    std::string segment;
                    std::vector<std::string> parts;
                    while(std::getline(ss, segment, ':')) {
                       parts.push_back(segment);
                    }

                    if (parts.size() == 3 && parts[0] == "unlocks") {
                        std::string direction = parts[1];
                        std::string targetRoomName = parts[2];

                        Room* targetRoom = nullptr;
                        for (auto r : rooms) {
                            if (r->name == targetRoomName) {
                                targetRoom = r;
                                break;
                            }
                        }

                        if (targetRoom && currentRoom->getExit(direction) == nullptr) {
                            currentRoom->connect(targetRoom, direction);
                            std::cout << "The " << item->name << " reveals a hidden exit to the " << direction << "!" << std::endl;
                        }
                    }
                }
            } else {
                std::cout << "You don't have that item." << std::endl;
            }
        } else if (cmd.action == "talk") {
            NPC* npcToTalkTo = nullptr;
            for (auto npc : currentRoom->npcs) {
                if (npc->name == cmd.target) {
                    npcToTalkTo = npc;
                    break;
                }
            }
            if (npcToTalkTo != nullptr) {
                npcToTalkTo->talk();
            } else {
                std::cout << "There is no one here by that name." << std::endl;
            }
        } else if (cmd.action == "save") {
            saveSystem.save(player, "data/save.txt");
        } else if (cmd.action == "load") {
            saveSystem.load(player, rooms, allItems, "data/save.txt");
            currentRoom = player.currentRoom; // Update currentRoom after loading
        } else if (cmd.action == "help") {
            std::cout << "Available commands: go, look, take, drop, use, inventory, talk, save, load, help, exit." << std::endl;
        } else if (cmd.action == "exit" || cmd.action == "quit") {
            endGame();
        } else {
            std::cout << "Invalid command." << std::endl;
        }

        // Check for events after every command
        for (auto& event : currentRoom->events) {
            event->checkTrigger(player, *currentRoom);
        }
    }

    void Game::endGame() {
        isRunning = false;
        std::cout << "Thanks for playing!" << std::endl;
    }

}
