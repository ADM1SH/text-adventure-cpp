#include "../include/Parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace text_adventure {

    std::string Parser::getInput() const {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);
        return input;
    }

    Command Parser::parse(const std::string &input) const {
        std::stringstream ss(input);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> words(begin, end);

        if (words.empty()) {
            return Command("", "");
        }

        std::string action = words[0];
        std::transform(action.begin(), action.end(), action.begin(), ::tolower);

        std::string target = "";
        if (words.size() > 1) {
            target = words[1];
            std::transform(target.begin(), target.end(), target.begin(), ::tolower);
        }

        return Command(action, target);
    }

}
