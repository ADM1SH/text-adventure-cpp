#include "../include/SaveSystem.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Item.h"
#include <fstream>
#include <iostream>

namespace text_adventure {

    void SaveSystem::save(const Player &player, const std::string &filename) const {
        std::ofstream saveFile(filename);
        if (saveFile.is_open()) {
            saveFile << player.currentRoom->name << std::endl;
            saveFile << player.health << std::endl;
            saveFile << player.score << std::endl;
            for (const auto& item : player.inventory) {
                saveFile << item->name << std::endl;
            }
            saveFile.close();
            std::cout << "Game saved." << std::endl;
        } else {
            std::cerr << "Error: Could not save game to " << filename << std::endl;
        }
    }

    void SaveSystem::load(Player &player, std::vector<Room*> &rooms, const std::string &filename) {
        std::ifstream loadFile(filename);
        if (loadFile.is_open()) {
            std::string roomName;
            std::getline(loadFile, roomName);

            for (auto& room : rooms) {
                if (room->name == roomName) {
                    player.currentRoom = room;
                    break;
                }
            }

            loadFile >> player.health;
            loadFile >> player.score;

            // Clear current inventory
            player.inventory.clear();

            // This is a simplified load. A real implementation would need to handle
            // creating item objects again and adding them to the player's inventory.

            loadFile.close();
            std::cout << "Game loaded." << std::endl;
        } else {
            std::cerr << "Error: Could not load game from " << filename << std::endl;
        }
    }

}
