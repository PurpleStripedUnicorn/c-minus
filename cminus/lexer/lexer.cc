
#include "lexer.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

// This map contains types of small and simple tokens
// If a string is present in this map, then all of its prefixes should be too!
std::unordered_map<std::string, TokenType> smallTokens = {
    { "(", TOK_LBRACE },
    { ")", TOK_RBRACE },
    { "{", TOK_LCBRACE },
    { "}", TOK_RCBRACE },
    { ",", TOK_COMMA },
    { ";", TOK_SEMICOL },
    { "=", TOK_ASSIGN },
    { "+", TOK_PLUS },
    { "-", TOK_MINUS },
    { "*", TOK_TIMES },
    { "/", TOK_DIV },
    { "%", TOK_MOD },
    { "==", TOK_EQ },
    { "!=", TOK_NEQ },
    { "<", TOK_LT },
    { "<=", TOK_LTE },
    { ">", TOK_GT },
    { ">=", TOK_GTE },
    { "!", TOK_NOT },
};

std::unordered_set<std::string> typenames = {
    "void",
    "bool",
    "int",
    "unsigned",
    "uint8_t"
};

Lexer::Lexer(const std::string &txt, Debugger &debug) : txt(txt), pos(0),
loc(1, 1), savedLoc(1, 1), debug(debug) {

}

Lexer::~Lexer() {

}

Token Lexer::get() {
    Token tok = getToken();
    debug.tokens.push_back(tok);
    return tok;
}

bool Lexer::atEnd() const {
    return pos >= txt.size();
}

Token Lexer::getToken() {
    savedLoc = loc;
    if (atEnd())
        return Token(TOK_END);
    std::string curStr;
    curStr.push_back(cur());
    if (smallTokens.find(curStr) != smallTokens.end())
        return readSmallToken();
    if (('a' <= cur() && cur() <= 'z') || ('A' <= cur() && cur() <= 'Z')
    || cur() == '_')
        return readID();
    if ('0' <= cur() && cur() <= '9')
        return readNum();
    if (cur() == ' ' || cur() == '\n' || cur() == '\t') {
        next();
        return getToken();
    }
    debug.logger.error("Unrecognized token", savedLoc);
    return Token();
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
    || cur() == '_' || ('0' <= cur() && cur() <= '9'))
        ret += cur(), next();
    if (typenames.find(ret) != typenames.end())
        return Token(TOK_TYPENAME, ret, savedLoc);
    if (ret == "print")
        return Token(TOK_PRINT, "", savedLoc);
    if (ret == "if")
        return Token(TOK_IF, "", savedLoc);
    if (ret == "else")
        return Token(TOK_ELSE, "", savedLoc);
    if (ret == "while")
        return Token(TOK_WHILE, "", savedLoc);
    return Token(TOK_ID, ret, savedLoc);
}

Token Lexer::readNum() {
    std::string ret;
    while ('0' <= cur() && cur() <= '9')
        ret += cur(), next();
    return Token(TOK_NUM, ret, savedLoc);
}

Token Lexer::readSmallToken() {
    std::string content;
    content.push_back(cur()), next();
    while (smallTokens.find(content + cur()) != smallTokens.end())
        content.push_back(cur()), next();
    return Token(smallTokens.find(content)->second, "", savedLoc);
}