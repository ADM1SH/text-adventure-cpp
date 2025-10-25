#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>

namespace text_adventure {
    class Item;
    class NPC;
    class Event;

    class Room {
    public:
        std::string name;
        std::string description;
        std::map<std::string, Room*> exits;
        std::vector<Item*> items;
        std::vector<NPC*> npcs;
        std::vector<Event*> events;

        Room(const std::string &name, const std::string &description);
        ~Room();

        void connect(Room *other, const std::string &direction);
        void addItem(Item *item);
        void removeItem(const std::string &itemName);
        void describe() const;
        Room *getExit(const std::string &direction);
    };
}

#endif // ROOM_H
