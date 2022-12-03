
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "debugger/debugger.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "No input filename given." << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return 1;
    }
    std::stringstream stream;
    stream << file.rdbuf();
    std::string txt = stream.str();
    Debugger debug;
    debug.enable();
    Lexer lexer(txt, debug);
    Parser parser(lexer, debug);
    parser.parse();
    // Debug files
    std::ofstream lexerDebug("lexer.debug"), parserDebug("parser.debug");
    debug.lexer(lexerDebug);
    debug.parser(parserDebug);
    return 0;
}