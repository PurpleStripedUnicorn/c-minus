
#include "lexer/lexer.h"
#include "parsenode/node.h"
#include "parsenode/parsenode.h"
#include "parser.h"
#include <iostream>
#include <vector>

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

const Token &Parser::cur() const {
    return curToken;
}

void Parser::next() {
    curToken = lexer.get();
}

Loc Parser::getLoc() const {
    return cur().loc;
}

bool Parser::atEnd() const {
    return cur().type == TOK_END;
}

bool Parser::accept(TokenType type) const {
    return type == cur().type;
}

void Parser::expect(TokenType type) const {
    if (!accept(type)) {
        std::cerr << "Incorrect node type matched at << " << getLoc() << "."
        << std::endl;
        exit(1);
    }
}

ParseNode *Parser::readProgram() {
    std::vector<ParseNode *> children;
    Loc loc = getLoc();
    while (!atEnd())
        children.push_back(readFunction());
    return new ProgramNode(loc, children);
}

ParseNode *Parser::readFunction() {
    expect(TOK_TYPENAME);

}