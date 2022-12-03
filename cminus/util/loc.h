
#ifndef FILE_LOC
#define FILE_LOC

#include <string>

/**
 * Represents the location in the input text
 */
struct Loc {
    Loc(size_t line = 0, size_t col = 0);
    std::string str() const;
    friend std::ostream &operator<<(std::ostream &os, const Loc &loc);
    size_t line, col;
};

#endif