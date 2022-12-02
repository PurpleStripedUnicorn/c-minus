
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "debugger/debugger.h"
#include "lexer/lexer.h"

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
    Lexer lexer(txt);
    std::vector<Token> tokens;
    while (!lexer.atEnd())
        tokens.push_back(lexer.get());
    Debugger debug;
    debug.lexer("lexer.debug", tokens);
    return 0;
}