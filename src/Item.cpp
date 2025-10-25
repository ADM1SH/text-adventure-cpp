#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include <iostream>

namespace text_adventure {
    Item::Item(const std::string &name, const std::string &description, bool isUsable, bool isPickupable)
        : name(name), description(description), isUsable(isUsable), isPickupable(isPickupable) {}

    void Item::inspect() const {
        std::cout << description << std::endl;
    }

    void Item::use(Room &room) {
        if (isUsable) {
            if (this->name == "torch" && room.name == "Hallway") {
                if (room.getExit("east") == nullptr) {
                    std::cout << "The light reveals a hidden door to the east!" << std::endl;
                } else {
                    std::cout << "The door to the east is already revealed." << std::endl;
                }
            } else {
                std::cout << "You can't use this item in any special way right now." << std::endl;
            }
        } else {
            std::cout << "You can't use this item." << std::endl;
        }
    }
}
