#include "../include/Event.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Item.h"
#include <iostream>
#include <vector>
#include <sstream>

namespace text_adventure {

    Event::Event(const std::string &condition, const std::string &effect)
        : condition(condition), effect(effect), triggered(false) {}

    void Event::checkTrigger(Player &player, Room &room) {
        if (!triggered) {
            std::stringstream ss_cond(condition);
            std::string segment;
            std::vector<std::string> cond_parts;
            while(std::getline(ss_cond, segment, ':')) {
               cond_parts.push_back(segment);
            }

            bool conditionMet = false;
            if (cond_parts.size() == 2 && cond_parts[0] == "has") {
                if (player.hasItem(cond_parts[1])) {
                    conditionMet = true;
                }
            }

            if (conditionMet) {
                std::stringstream ss_eff(effect);
                std::vector<std::string> eff_parts;
                while(std::getline(ss_eff, segment, ':')) {
                   eff_parts.push_back(segment);
                }

                if (eff_parts.size() == 2 && eff_parts[0] == "reveals") {
                    // In a real game, you'd have a master list of items to pull from.
                    // For this example, we'll create a new item.
                    Item* newItem = new Item(eff_parts[1], "A newly revealed item.", "", "", false, true);
                    room.addItem(newItem);
                    std::cout << "An event is triggered! A " << newItem->name << " has been revealed." << std::endl;
                    triggered = true;
                }
            }
        }
    }

}
