#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include <string>
#include <vector>
#include <map>

namespace text_adventure {
    class Room;
    class Item;
    class NPC;

    class WorldLoader {
    public:
        bool loadWorld(const std::string &filename, std::vector<Room*> &rooms, std::vector<Item*> &items);
    };
}

#endif // WORLDLOADER_H
