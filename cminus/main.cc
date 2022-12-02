
#include <iostream>
#include "debugger/debugger.h"
#include "lexer/lexer.h"

int main() {
    std::string txt = "Hello World!";
    Lexer lexer(txt);
    std::vector<Token> tokens;
    while (!lexer.atEnd())
        tokens.push_back(lexer.get());
    Debugger debug;
    debug.lexer("lexer.debug", tokens);
    return 0;
}