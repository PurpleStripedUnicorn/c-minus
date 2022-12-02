
#include "lexer.h"
#include <string>

Lexer::Lexer(const std::string &txt) : txt(txt), pos(0) {

}

Lexer::~Lexer() {

}

Token Lexer::get() {
    if (atEnd())
        return Token(TOK_END);
    // TODO: implement
    std::string t; t += cur();
    next();
    return Token(TOK_ID, t);
}

bool Lexer::atEnd() const {
    return pos >= txt.size();
}

char Lexer::cur() const {
    return txt[pos];
}

void Lexer::next() {
    pos++;
}