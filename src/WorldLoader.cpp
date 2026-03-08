#include "../include/WorldLoader.h"
#include "../include/Room.h"
#include "../include/Item.h"
#include "../include/NPC.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

namespace text_adventure {

    // Helper structs to hold data before creating objects
    struct RoomData {
        std::string name;
        std::string description;
        std::map<std::string, std::string> exits;
        std::vector<std::string> itemNames;
        std::vector<std::string> npcNames;
    };

    struct ItemData {
        std::string name;
        std::string description;
        std::string useEffect;
        std::string useTarget;
        bool isUsable;
        bool isPickupable;
    };

    struct NpcData {
        std::string name;
        std::string dialoguePath;
        bool questGiver;
    };

    // Helper function to trim whitespace from a string
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    bool WorldLoader::loadWorld(const std::string &filename, std::vector<Room*> &rooms, std::vector<Item*> &items) {
        std::ifstream worldFile(filename);
        if (!worldFile.is_open()) {
            std::cerr << "Error: Could not open world file: " << filename << std::endl;
            return false;
        }

        std::map<std::string, RoomData> roomDatas;
        std::map<std::string, ItemData> itemDatas;
        std::map<std::string, NpcData> npcDatas;

        std::string line;
        std::string currentSection;
        RoomData* currentRoomData = nullptr;
        ItemData* currentItemData = nullptr;
        NpcData* currentNpcData = nullptr;

        while (std::getline(worldFile, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') {
                continue;
            }

            if (line == "[Room]") {
                currentSection = "Room";
                RoomData rd;
                roomDatas[""] = rd; // Placeholder
                currentRoomData = &roomDatas[""];
                currentItemData = nullptr;
                currentNpcData = nullptr;
            } else if (line == "[Item]") {
                currentSection = "Item";
                ItemData id;
                itemDatas[""] = id; // Placeholder
                currentItemData = &itemDatas[""];
                currentRoomData = nullptr;
                currentNpcData = nullptr;
            } else if (line == "[NPC]") {
                currentSection = "NPC";
                NpcData nd;
                npcDatas[""] = nd; // Placeholder
                currentNpcData = &npcDatas[""];
                currentRoomData = nullptr;
                currentItemData = nullptr;
            } else {
                size_t separatorPos = line.find('=');
                if (separatorPos != std::string::npos) {
                    std::string key = trim(line.substr(0, separatorPos));
                    std::string value = trim(line.substr(separatorPos + 1));

                    if (currentSection == "Room" && currentRoomData) {
                        if (key == "Name") {
                            currentRoomData->name = value;
                            roomDatas[value] = *currentRoomData;
                            roomDatas.erase("");
                            currentRoomData = &roomDatas[value];
                        } else if (key == "Desc") {
                            currentRoomData->description = value;
                        } else if (key.rfind("Exit", 0) == 0) {
                            std::string direction = key.substr(4);
                            std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
                            currentRoomData->exits[direction] = value;
                        } else if (key == "Item") {
                            currentRoomData->itemNames.push_back(value);
                        } else if (key == "NPC") {
                            currentRoomData->npcNames.push_back(value);
                        }
                    } else if (currentSection == "Item" && currentItemData) {
                        if (key == "Name") {
                            currentItemData->name = value;
                            itemDatas[value] = *currentItemData;
                            itemDatas.erase("");
                            currentItemData = &itemDatas[value];
                        } else if (key == "Desc") {
                            currentItemData->description = value;
                        } else if (key == "UseEffect") {
                            currentItemData->useEffect = value;
                        } else if (key == "UseTarget") {
                            currentItemData->useTarget = value;
                        } else if (key == "Usable") {
                            currentItemData->isUsable = (value == "true");
                        } else if (key == "Pickupable") {
                            currentItemData->isPickupable = (value == "true");
                        }
                    } else if (currentSection == "NPC" && currentNpcData) {
                        if (key == "Name") {
                            currentNpcData->name = value;
                            npcDatas[value] = *currentNpcData;
                            npcDatas.erase("");
                            currentNpcData = &npcDatas[value];
                        } else if (key == "Dialogue") {
                            currentNpcData->dialoguePath = value;
                        } else if (key == "QuestGiver") {
                            currentNpcData->questGiver = (value == "true");
                        }
                    }
                }
            }
        }
        worldFile.close();

        // Create Items
        std::map<std::string, Item*> createdItems;
        for (auto const& [name, data] : itemDatas) {
            Item* newItem = new Item(data.name, data.description, data.useEffect, data.useTarget, data.isUsable, data.isPickupable);
            items.push_back(newItem);
            createdItems[name] = newItem;
        }

        // Create NPCs
        std::map<std::string, NPC*> createdNpcs;
        for (auto const& [name, data] : npcDatas) {
            NPC* newNpc = new NPC(data.name, data.dialoguePath, data.questGiver);
            createdNpcs[name] = newNpc;
        }

        // Create Rooms
        std::map<std::string, Room*> createdRooms;
        for (auto const& [name, data] : roomDatas) {
            Room* newRoom = new Room(data.name, data.description);
            rooms.push_back(newRoom);
            createdRooms[name] = newRoom;
        }

        // Populate Rooms
        for (auto const& [name, data] : roomDatas) {
            Room* room = createdRooms[name];
            for (const auto& itemName : data.itemNames) {
                if (createdItems.count(itemName)) {
                    room->addItem(createdItems[itemName]);
                }
            }
            for (const auto& npcName : data.npcNames) {
                if (createdNpcs.count(npcName)) {
                    room->npcs.push_back(createdNpcs[npcName]);
                }
            }
            for (auto const& [direction, exitName] : data.exits) {
                if (createdRooms.count(exitName)) {
                    room->connect(createdRooms[exitName], direction);
                }
            }
        }

        std::cout << "World loaded from " << filename << std::endl;
        return true;
    }

}
