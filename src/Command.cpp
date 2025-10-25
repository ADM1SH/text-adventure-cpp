#include "../include/Command.h"

namespace text_adventure {
    Command::Command(const std::string& action, const std::string& target)
        : action(action), target(target) {}
}
