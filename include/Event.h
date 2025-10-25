#ifndef EVENT_H
#define EVENT_H

#include <string>

namespace text_adventure {
    class Player;
    class Room;

    class Event {
    public:
        std::string condition;
        std::string effect;
        bool triggered;

        Event(const std::string &condition, const std::string &effect);

        void checkTrigger(Player &player);
    };
}

#endif // EVENT_H
