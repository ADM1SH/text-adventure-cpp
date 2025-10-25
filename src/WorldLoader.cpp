#include "../include/WorldLoader.h"
#include "../include/Room.h"
#include "../include/Item.h"
#include "../include/NPC.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace text_adventure {

    bool WorldLoader::loadWorld(const std::string &filename, std::vector<Room*> &rooms, std::vector<Item*> &items) {
        std::ifstream worldFile(filename);
        if (!worldFile.is_open()) {
            std::cerr << "Error: Could not open world file: " << filename << std::endl;
            return false;
        }

        std::string line;
        Room* currentRoom = nullptr;

        while (std::getline(worldFile, line)) {
            if (line.empty() || line[0] == '#') {
                continue; // Skip empty lines and comments
            }

            if (line == "[Room]") {
                std::string name, desc;
                std::getline(worldFile, line);
                name = line.substr(line.find("=") + 1);
                std::getline(worldFile, line);
                desc = line.substr(line.find("=") + 1);
                currentRoom = new Room(name, desc);
                rooms.push_back(currentRoom);
            } else if (line.find("Exit") == 0) {
                // This is a simplified loader. A real implementation would need to parse exits
                // and connect rooms after all rooms have been loaded.
            } else if (line.find("Item") == 0) {
                // Simplified item loading
                std::string itemName = line.substr(line.find("=") + 1);
                Item* newItem = new Item(itemName, "An item.", false, true);
                items.push_back(newItem);
                if (currentRoom) {
                    currentRoom->addItem(newItem);
                }
            }
        }

        worldFile.close();
        std::cout << "World loaded from " << filename << std::endl;
        return true;
    }

}
