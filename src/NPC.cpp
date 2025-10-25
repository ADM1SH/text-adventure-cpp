#include "../include/NPC.h"
#include <iostream>
#include <fstream>

namespace text_adventure {

    NPC::NPC(const std::string &name, const std::string &dialoguePath, bool questGiver)
        : name(name), dialoguePath(dialoguePath), questGiver(questGiver) {}

    void NPC::talk() const {
        std::ifstream file(dialoguePath);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
        } else {
            std::cout << name << " has nothing to say." << std::endl;
        }
    }

    void NPC::trade() {
        std::cout << name << " has nothing to trade." << std::endl;
    }

    void NPC::giveQuest() {
        if (questGiver) {
            std::cout << name << " gives you a quest!" << std::endl;
        } else {
            std::cout << name << " has no quest for you." << std::endl;
        }
    }

}
