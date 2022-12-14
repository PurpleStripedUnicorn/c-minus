
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
    // Statements
    TOK_IF, TOK_ELSE, TOK_WHILE,
    // Identifiers and typenames
    TOK_ID, TOK_TYPENAME,
    // Numbers
    TOK_NUM,
    // Special characters
    TOK_COMMA, TOK_SEMICOL,
    TOK_LBRACE, TOK_RBRACE,
    TOK_LCBRACE, TOK_RCBRACE,
    // Assignment
    TOK_ASSIGN,
    // Comparisons
    TOK_EQ, TOK_NEQ, TOK_LT, TOK_LTE, TOK_GT, TOK_GTE,
    // Arithmatic
    TOK_PLUS, TOK_TIMES, TOK_MINUS, TOK_DIV, TOK_MOD,
    // Print statement
    TOK_PRINT,
    // Boolean operators
    TOK_NOT,
};

/**
 * A basic lexer token
 */
struct Token {
    Token(TokenType type = TOK_ERR, std::string content = "", Loc loc = Loc());
    TokenType type;
    std::string content;
    Loc loc;
};

#endif