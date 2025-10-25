#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Item.h"
#include <iostream>

namespace text_adventure {

    Player::Player()
        : currentRoom(nullptr), health(100), score(0) {}

    void Player::move(Room *nextRoom) {
        currentRoom = nextRoom;
    }

    void Player::take(Item *item) {
        if (item->isPickupable) {
            inventory.push_back(item);
            currentRoom->removeItem(item->name);
            std::cout << "You picked up the " << item->name << "." << std::endl;
        } else {
            std::cout << "You can't pick that up." << std::endl;
        }
    }

    void Player::drop(Item *item) {
        inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
        currentRoom->addItem(item);
        std::cout << "You dropped the " << item->name << "." << std::endl;
    }

    void Player::showInventory() const {
        if (inventory.empty()) {
            std::cout << "Your inventory is empty." << std::endl;
        } else {
            std::cout << "Inventory:" << std::endl;
            for (const auto &item : inventory) {
                std::cout << "- " << item->name << std::endl;
            }
        }
    }

    bool Player::hasItem(const std::string &itemName) const {
        for (const auto &item : inventory) {
            if (item->name == itemName) {
                return true;
            }
        }
        return false;
    }

    Item* Player::getItem(const std::string &itemName) {
        for (auto &item : inventory) {
            if (item->name == itemName) {
                return item;
            }
        }
        return nullptr;
    }

}
