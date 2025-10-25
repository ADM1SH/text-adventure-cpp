#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <vector>

namespace text_adventure {
    class Player;
    class Room;

    class SaveSystem {
    public:
        void save(const Player &player, const std::string &filename) const;
        void load(Player &player, std::vector<Room*> &rooms, const std::string &filename);
    };
}

#endif // SAVESYSTEM_H
