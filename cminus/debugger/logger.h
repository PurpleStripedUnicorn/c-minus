
#ifndef FILE_LOGGER
#define FILE_LOGGER

#include "util/loc.h"
#include <string>

/**
 * Color to print text in linux terminal
 */
enum ConsoleColor {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
};

/**
 * General logger component
 * Used to show errors and logging
 */
class Logger {

public:

    /**
     * Constructor
     */
    Logger();

    /**
     * Destructor
     */
    ~Logger();

    /**
     * Show an error, also stops the compiler
     * @param msg The message to show
     * @param loc The location of the error
     */
    void error(const std::string &msg, Loc loc = Loc()) const;

private:

    /**
     * Return a linux terminal formatted string to output colored text
     * @param txt The text to change the color of
     * @param color The color to change it to
     * @param bold Wether the text should be made bold
     * @return A new string with color information encoded
     */
    static std::string colorText(const std::string &txt, ConsoleColor color,
    bool bold = false);

};

#endif