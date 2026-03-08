#ifndef ITEM_H
#define ITEM_H

#include <string>

namespace text_adventure {
    class Player;
    class Room;

    class Item {
    public:
        std::string name;
        std::string description;
        std::string useEffect;
        std::string useTarget;
        bool isUsable;
        bool isPickupable;

        Item(const std::string &name, const std::string &description, const std::string &useEffect, const std::string &useTarget, bool isUsable, bool isPickupable);
        virtual ~Item() = default;

        void inspect() const;
        virtual void use(Room &room);
    };
}

#endif // ITEM_H
