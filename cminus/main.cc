
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "debugger/debugger.h"
#include "lexer/lexer.h"
#include "machinecode/generator.h"
#include "parsenode/parsenode.h"
#include "parser/parser.h"
#include "parser/semantics/semantics.h"
#include "tac/tac.h"

int main(int argc, char *argv[]) {
    bool debugMode = false;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [args] <filename>" <<
        std::endl;
        return 2;
    }
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-d")
            debugMode = true;
    }
    // Read in the given text file
    std::string filename = argv[argc - 1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the give file \"" << filename << "\"" <<
        std::endl;
        return 2;
    }
    std::stringstream stream;
    stream << file.rdbuf();
    std::string txt = stream.str();
    // Start debugger
    Debugger debug;
    std::string lexerDebugFile, parserDebugFile, tacDebugFile;
    lexerDebugFile = parserDebugFile = tacDebugFile = "/dev/null";
    if (debugMode) {
        lexerDebugFile = "lexer.debug";
        parserDebugFile = "parser.debug";
        tacDebugFile = "tac.debug";
    }
    std::ofstream lexerDebug(lexerDebugFile), parserDebug(parserDebugFile),
    tacDebug(tacDebugFile);
    if (debugMode)
        debug.enable();
    // Create a global symbol table
    SymbolTable symbolTable(debug);
    // Lexer
    Lexer lexer(txt, debug);
    // Parser
    Parser parser(lexer, debug);
    parser.parse();
    debug.lexer(lexerDebug);
    debug.parser(parserDebug);
    // Semantical analysis
    SemanticsVisitor semantics(debug, symbolTable);
    parser.getTree()->accept(&semantics);
    // TAC generation
    TACGenerator tac(debug, symbolTable);
    parser.getTree()->accept(&tac);
    debug.tac(tacDebug);
    // Machine code generation
    MCGenerator mc(tac.getTAC(), debug);
    mc.generate();
    mc.write(std::cout);
    return 0;
}