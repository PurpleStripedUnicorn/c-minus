
#ifndef FILE_TOKEN
#define FILE_TOKEN

#include "util/loc.h"
#include <string>

/**
 * A type of a token
 */
enum TokenType {
    // Types used in compiler
    TOK_END, TOK_ERR,
    // Identifiers
    TOK_ID,
    // Special characters
    TOK_COMMA,
    TOK_LBRACE, TOK_RBRACE,
    TOK_LCBRACE, TOK_RCBRACE,
    // Comparisons
    TOK_EQ,
    // Arithmatic
    TOK_PLUS, TOK_TIMES, TOK_MINUS, TOK_DIV, TOK_MOD
};

/**
 * A basic lexer token
 */
struct Token {
    Token(TokenType type = TOK_ERR, std::string content = "");
    TokenType type;
    std::string content;
    Loc loc;
};

#endif