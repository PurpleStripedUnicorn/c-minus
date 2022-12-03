
#include "loc.h"
#include <string>
#include <iostream>

Loc::Loc(size_t line, size_t col) : line(line), col(col) {

}

std::string Loc::str() const {
    if (line == 0)
        return "-";
    if (col == 0)
        return std::to_string(line);
    return std::to_string(line) + '[' + std::to_string(col) + ']';
}

std::ostream &operator<<(std::ostream &os, const Loc &loc) {
    return os << loc.str();
}