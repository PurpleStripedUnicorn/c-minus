
#ifndef FILE_LOC
#define FILE_LOC

#include <string>

/**
 * Represents the location in the input text
 */
struct Loc {
    Loc(size_t line = 0, size_t col = 0);
    std::string str() const;
    size_t line, col;
};

#endif