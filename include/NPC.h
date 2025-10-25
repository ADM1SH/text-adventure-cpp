#ifndef NPC_H
#define NPC_H

#include <string>

namespace text_adventure {
    class NPC {
    public:
        std::string name;
        std::string dialoguePath;
        bool questGiver;

        NPC(const std::string &name, const std::string &dialoguePath, bool questGiver);

        void talk() const;
        void trade();
        void giveQuest();
    };
}

#endif // NPC_H
