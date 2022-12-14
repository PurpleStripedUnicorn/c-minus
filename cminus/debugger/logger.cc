
#include "logger.h"
#include <string>
#include <iostream>

Logger::Logger() { }

Logger::~Logger() { }

void Logger::error(const std::string &msg, Loc loc) const {
    std::cerr << colorText(loc.str() + ": ", COLOR_WHITE, true) << colorText(
    "error: ", COLOR_RED, true) << msg << std::endl;
    exit(1);
}

std::string Logger::colorText(const std::string &txt, ConsoleColor color,
bool bold) {
    std::string out = "\033[0;";
    switch (color) {
        case COLOR_BLACK: out.append("30"); break;
        case COLOR_RED: out.append("31"); break;
        case COLOR_GREEN: out.append("32"); break;
        case COLOR_YELLOW: out.append("33"); break;
        case COLOR_BLUE: out.append("34"); break;
        case COLOR_MAGENTA: out.append("35"); break;
        case COLOR_CYAN: out.append("36"); break;
        case COLOR_WHITE: out.append("37"); break;
        default: break;
    }
    if (bold)
        out.append(";1");
    out.append("m");
    return out + txt + "\033[0m";
}