#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Command.h"

namespace text_adventure {
    class Parser {
    public:
        std::string getInput() const;
        Command parse(const std::string &input) const;
    };
}

#endif // PARSER_H
