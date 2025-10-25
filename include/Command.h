#ifndef COMMAND_H
#define COMMAND_H

#include <string>

namespace text_adventure {
    class Command {
    public:
        std::string action;
        std::string target;

        Command(const std::string &action, const std::string &target);
    };
}

#endif // COMMAND_H
