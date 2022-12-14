
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "debugger/debugger.h"
#include "lexer/lexer.h"
#include "machinecode/generator.h"
#include "parsenode/parsenode.h"
#include "parser/parser.h"
#include "tac/tac.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "No input filename given." << std::endl;
        return 1;
    }
    // Read in the given text file
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return 1;
    }
    std::stringstream stream;
    stream << file.rdbuf();
    std::string txt = stream.str();
    // Start debugger
    Debugger debug;
    std::ofstream lexerDebug("lexer.debug"), parserDebug("parser.debug"),
    tacDebug("tac.debug");
    debug.enable();
    // Lexer
    Lexer lexer(txt, debug);
    // Parser
    Parser parser(lexer, debug);
    parser.parse();
    debug.lexer(lexerDebug);
    debug.parser(parserDebug);
    // TAC generation
    TACGenerator tac(debug);
    parser.getTree()->accept(&tac);
    debug.tac(tacDebug);
    // Machine code generation
    MCGenerator mc(tac.getTAC(), debug);
    mc.generate();
    mc.write(std::cout);
    return 0;
}