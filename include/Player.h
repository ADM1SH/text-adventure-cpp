#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

namespace text_adventure {
    class Room;
    class Item;

    class Player {
    public:
        Room *currentRoom;
        std::vector<Item*> inventory;
        int health;
        int score;

        Player();

        void move(Room *nextRoom);
        void take(Item *item);
        void drop(Item *item);
        void showInventory() const;
        bool hasItem(const std::string &itemName) const;
        Item* getItem(const std::string &itemName);
    };
}

#endif // PLAYER_H
