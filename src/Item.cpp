#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include <iostream>

namespace text_adventure {
    Item::Item(const std::string &name, const std::string &description, const std::string &useEffect, const std::string &useTarget, bool isUsable, bool isPickupable)
        : name(name), description(description), useEffect(useEffect), useTarget(useTarget), isUsable(isUsable), isPickupable(isPickupable) {}

    void Item::inspect() const {
        std::cout << description << std::endl;
    }

    void Item::use(Room &room) {
        if (isUsable) {
            if (useTarget == room.name || useTarget.empty()) {
                std::cout << "You use the " << name << "." << std::endl;
            } else {
                std::cout << "You can't use this item here." << std::endl;
            }
        } else {
            std::cout << "You can't use this item." << std::endl;
        }
    }
}
