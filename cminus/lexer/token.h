
#ifndef FILE_TOKEN
#define FILE_TOKEN

#include <string>

/**
 * A type of a token
*/
enum TokenType {
    TOK_END,
    TOK_ID,
    TOK_COMMA,
    TOK_LBRACE, TOK_RBRACE,
    TOK_LCBRACE, TOK_RCBRACE,
    TOK_EQ,
    TOK_PLUS, TOK_TIMES, TOK_MINUS, TOK_DIV, TOK_MOD
};

/**
 * A basic lexer token
*/
struct Token {
    TokenType type;
    std::string content;
};

#endif