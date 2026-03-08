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

    void SaveSystem::load(Player &player, std::vector<Room*> &rooms, const std::vector<Item*> &allItems, const std::string &filename) {
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
            loadFile.ignore(); // Consume the rest of the line

            // Clear current inventory
            player.inventory.clear();

            std::string itemName;
            while (std::getline(loadFile, itemName)) {
                for (auto& item : allItems) {
                    if (item->name == itemName) {
                        player.inventory.push_back(item);
                        break;
                    }
                }
            }

            // Remove loaded items from their original rooms
            for (auto& itemInInventory : player.inventory) {
                for (auto& room : rooms) {
                    room->removeItem(itemInInventory->name);
                }
            }

            loadFile.close();
            std::cout << "Game loaded." << std::endl;
        } else {
            std::cerr << "Error: Could not load game from " << filename << std::endl;
        }
    }

}
