
#include "lexer.h"

Lexer::Lexer(const std::string &txt) : txt(txt), pos(0) {

}

Lexer::~Lexer() {

}

Token Lexer::get() {
    // TODO: implement
}

bool Lexer::atEnd() const {
    return pos >= txt.size();
}