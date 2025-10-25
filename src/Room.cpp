#include "../include/Room.h"
#include "../include/Item.h"
#include "../include/NPC.h"
#include "../include/Event.h"
#include <iostream>

namespace text_adventure {

    Room::Room(const std::string &name, const std::string &description)
        : name(name), description(description) {}

    Room::~Room() {
        for (auto item : items) {
            delete item;
        }
        for (auto npc : npcs) {
            delete npc;
        }
        for (auto event : events) {
            delete event;
        }
    }

    void Room::connect(Room *other, const std::string &direction) {
        exits[direction] = other;
    }

    void Room::addItem(Item *item) {
        items.push_back(item);
    }

    void Room::removeItem(const std::string &itemName) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [&](Item* item) { return item->name == itemName; }), items.end());
    }

    void Room::describe() const {
        std::cout << "=== " << name << " ===" << std::endl;
        std::cout << description << std::endl;

        if (!items.empty()) {
            std::cout << "You see: ";
            for (size_t i = 0; i < items.size(); ++i) {
                std::cout << items[i]->name << (i < items.size() - 1 ? ", " : "");
            }
            std::cout << std::endl;
        }

        if (!npcs.empty()) {
            std::cout << "People here: ";
            for (size_t i = 0; i < npcs.size(); ++i) {
                std::cout << npcs[i]->name << (i < npcs.size() - 1 ? ", " : "");
            }
            std::cout << std::endl;
        }

        std::cout << "Exits: ";
        for (auto const& [direction, room] : exits) {
            std::cout << direction << " ";
        }
        std::cout << std::endl;
    }

    Room *Room::getExit(const std::string &direction) {
        if (exits.count(direction)) {
            return exits.at(direction);
        }
        return nullptr;
    }

}
