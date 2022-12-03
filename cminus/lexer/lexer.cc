
#include "lexer.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

std::unordered_map<char, TokenType> smallTokens = {
    { '(', TOK_LBRACE },
    { ')', TOK_RBRACE },
    { '{', TOK_LCBRACE },
    { '}', TOK_RCBRACE },
    { ',', TOK_COMMA },
    { ';', TOK_SEMICOL },
    { '=', TOK_EQ },
    { '+', TOK_PLUS },
    { '-', TOK_MINUS },
    { '*', TOK_TIMES },
    { '/', TOK_DIV },
    { '%', TOK_MOD },
};

std::unordered_set<std::string> typenames = {
    "void",
    "bool",
    "int",
    "unsigned",
    "uint8_t"
};

Lexer::Lexer(const std::string &txt) : txt(txt), pos(0), loc(1, 1), savedLoc(1,
1) {

}

Lexer::~Lexer() {

}

Token Lexer::get() {
    savedLoc = loc;
    if (atEnd())
        return Token(TOK_END);
    if (smallTokens.find(cur()) != smallTokens.end()) {
        Token ret = Token(smallTokens.find(cur())->second, "", savedLoc);
        next();
        return ret;
    }
    if (('a' <= cur() && cur() <= 'z') || ('A' <= cur() && cur() <= 'Z')
    || cur() == '_')
        return readID();
    if ('0' <= cur() && cur() <= '9')
        return readNum();
    if (cur() == ' ' || cur() == '\n' || cur() == '\t') {
        next();
        return get();
    }
    std::cerr << "Lexer error, unrecognized token." << std::endl;
    exit(1);
}

bool Lexer::atEnd() const {
    return pos >= txt.size();
}

char Lexer::cur() const {
    if (atEnd())
        return '\n';
    return txt[pos];
}

void Lexer::next() {
    if (!atEnd() && cur() == '\n')
        loc.col = 1, loc.line++;
    else
        loc.col++;
    pos++;
}

Token Lexer::readID() {
    std::string ret;
    while (('a' <= cur() && cur() <= 'z') || ('A' <= cur() && cur() <= 'Z')
    || cur() == '_')
        ret += cur(), next();
    if (typenames.find(ret) != typenames.end())
        return Token(TOK_TYPENAME, ret, savedLoc);
    if (ret == "print")
        return Token(TOK_PRINT, "", savedLoc);
    return Token(TOK_ID, ret, savedLoc);
}

Token Lexer::readNum() {
    std::string ret;
    while ('0' <= cur() && cur() <= '9')
        ret += cur(), next();
    return Token(TOK_NUM, ret, savedLoc);
}