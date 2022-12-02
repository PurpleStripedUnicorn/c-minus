
#include "lexer/lexer.h"
#include "parser.h"

Parser::Parser(Lexer &lexer) : lexer(lexer), curToken(Token()), tree(nullptr) {

}

Parser::~Parser() {

}

void Parser::parse() {
    tree = readProgram();
}

ParseNode *Parser::getTree() const {
    return tree;
}

Token Parser::cur() const {
    return curToken;
}

void Parser::next() {
    curToken = lexer.get();
}

bool Parser::atEnd() const {
    return cur().type == TOK_END;
}

ParseNode *Parser::readProgram() {
    while (!atEnd()) {
        
    }
}