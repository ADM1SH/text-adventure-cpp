#include "../include/Event.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include <iostream>

namespace text_adventure {

    Event::Event(const std::string &condition, const std::string &effect)
        : condition(condition), effect(effect), triggered(false) {}

    void Event::checkTrigger(Player &player) {
        if (!triggered) {
            // Basic example: condition is having a specific item
            if (player.hasItem(condition)) {
                std::cout << "An event is triggered!" << std::endl;
                // The effect could be creating a new exit, revealing an item, etc.
                // This is where you would implement the logic for the effect.
                std::cout << effect << std::endl;
                triggered = true;
            }
        }
    }

}
