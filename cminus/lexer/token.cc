
#include "token.h"

Token::Token(TokenType type, std::string content, Loc loc) : type(type),
content(content), loc(loc) {

}