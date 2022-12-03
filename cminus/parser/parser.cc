
#include "lexer/lexer.h"
#include "parsenode/nodes.h"
#include "parsenode/parsenode.h"
#include "parser.h"
#include "util/types.h"
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
    ProgramNode *node = new ProgramNode(getLoc());
    Loc loc = getLoc();
    while (!atEnd())
        children.push_back(readFunc());
    node->childNodes = children;
    return node;
}

ParseNode *Parser::readFunc() {
    expect(TOK_TYPENAME);
    FuncNode *node = new FuncNode(getLoc());
    node->returnType = toReturnType(cur().content);
    next();
    expect(TOK_ID);
    node->name = cur().content;
    expect(TOK_LBRACE), next();
    expect(TOK_RBRACE), next();
    node->child = readScope();
}

ParseNode *Parser::readStmt() {
    if (accept(TOK_LCBRACE))
        return readScope();
    // TODO: Add more cases here when they are implemented
    return readPrint();
}

ParseNode *Parser::readScope() {
    expect(TOK_LCBRACE), next();
    ScopeNode *node = new ScopeNode(getLoc());
    while (!accept(TOK_RCBRACE) && !atEnd())
        node->childNodes.push_back(readStmt());
    expect(TOK_RCBRACE), next();
    return node;
}

ParseNode *Parser::readPrint() {
    expect(TOK_PRINT), next();
    expect(TOK_LBRACE), next();
    PrintNode *node = new PrintNode(getLoc());
    node->child = readNum();
    expect(TOK_RBRACE), next();
    return node;
}

ParseNode *Parser::readNum() {
    expect(TOK_NUM);
    NumberNode *node = new NumberNode(cur().content, getLoc());
    next();
    return node;
}