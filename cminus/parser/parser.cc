
#include "lexer/lexer.h"
#include "parsenode/nodes.h"
#include "parsenode/parsenode.h"
#include "parser.h"
#include "util/types.h"
#include <iostream>
#include <vector>

Parser::Parser(Lexer &lexer, Debugger &debug) : lexer(lexer), curToken(Token()),
tree(nullptr), debug(debug) {

}

Parser::~Parser() {
    delete tree;
}

void Parser::parse() {
    next();
    tree = readProgram();
    debug.tree = tree;
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
    if (!accept(type))
        debug.logger.error("Unexpected token", getLoc());
}

ParseNode *Parser::readProgram() {
    std::vector<ParseNode *> children;
    ProgramNode *node = new ProgramNode(getLoc());
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
    next();
    expect(TOK_LBRACE), next();
    expect(TOK_RBRACE), next();
    node->child = readScope();
    return node;
}

ParseNode *Parser::readStmt() {
    if (accept(TOK_LCBRACE))
        return readScope();
    // TODO: Add more cases here when they are implemented
    if (accept(TOK_TYPENAME))
        return readDeclaration();
    if (accept(TOK_PRINT))
        return readPrint();
    if (accept(TOK_IF))
        return readIf();
    if (accept(TOK_WHILE))
        return readWhile();
    ParseNode *node = readExpr();
    expect(TOK_SEMICOL), next();
    return node;
}

ParseNode *Parser::readIf() {
    IfNode *node = new IfNode(getLoc());
    expect(TOK_IF), next();
    expect(TOK_LBRACE), next();
    node->leftChild = readExpr();
    expect(TOK_RBRACE), next();
    node->middleChild = readStmt();
    node->rightChild = nullptr;
    node->hasElse = false;
    if (accept(TOK_ELSE)) {
        next();
        node->rightChild = readStmt();
        node->hasElse = true;
    }
    return node;
}

ParseNode *Parser::readWhile() {
    WhileNode *node = new WhileNode(getLoc());
    expect(TOK_WHILE), next();
    expect(TOK_LBRACE), next();
    node->leftChild = readExpr();
    expect(TOK_RBRACE), next();
    node->rightChild = readStmt();
    return node;
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
    node->child = readExpr();
    expect(TOK_RBRACE), next();
    expect(TOK_SEMICOL), next();
    return node;
}

ParseNode *Parser::readExpr() {
    ParseNode *node = readAssign();
    return node;
}

ParseNode *Parser::readAssign() {
    // Right associative
    AssignNode *node = new AssignNode(getLoc());
    node->leftChild = nullptr, node->rightChild = nullptr;
    ParseNode *leftNode = readEquality();
    if (!accept(TOK_ASSIGN)) {
        delete node;
        return leftNode;
    }
    node->leftChild = leftNode;
    next();
    if (leftNode->getType() != NODE_IDENT)
        debug.logger.error("Expected an identifier at the left side of an "
        "assignment", node->loc);
    node->rightChild = readAssign();
    return node;
}

ParseNode *Parser::readEquality() {
    // Left associative
    Loc loc = getLoc();
    ParseNode *cur = readCompare();
    while (accept(TOK_EQ) || accept(TOK_NEQ)) {
        BinaryNode *newCur;
        if (accept(TOK_EQ))
            newCur = new EqNode(loc);
        else
            newCur = new NeqNode(loc);
        next();
        newCur->leftChild = cur;
        newCur->rightChild = readCompare();
        cur = newCur;
    }
    return cur;
}

ParseNode *Parser::readCompare() {
    // Left associative
    Loc loc = getLoc();
    ParseNode *cur = readSum();
    while (accept(TOK_LT) || accept(TOK_LTE) || accept(TOK_GT) ||
    accept(TOK_GTE)) {
        BinaryNode *newCur;
        if (accept(TOK_LT))
            newCur = new LtNode(loc);
        else if (accept(TOK_LTE))
            newCur = new LteNode(loc);
        else if (accept(TOK_GT))
            newCur = new GtNode(loc);
        else
            newCur = new GteNode(loc);
        next();
        newCur->leftChild = cur;
        newCur->rightChild = readSum();
        cur = newCur;
    }
    return cur;
}

ParseNode *Parser::readSum() {
    // Left associative
    Loc loc = getLoc();
    ParseNode *cur = readProduct();
    while (accept(TOK_PLUS) || accept(TOK_MINUS)) {
        BinaryNode *newCur;
        if (accept(TOK_PLUS))
            newCur = new AddNode(loc);
        else
            newCur = new SubNode(loc);
        next();
        newCur->leftChild = cur;
        newCur->rightChild = readProduct();
        cur = newCur;
    }
    return cur;
}

ParseNode *Parser::readProduct() {
    // Left associative
    // TODO: implement division and modulo
    Loc loc = getLoc();
    ParseNode *cur = readExprLeaf();
    while (accept(TOK_TIMES)) {
        BinaryNode *newCur = new MulNode(loc);
        next();
        newCur->leftChild = cur;
        newCur->rightChild = readExprLeaf();
        cur = newCur;
    }
    return cur;
}

ParseNode *Parser::readExprLeaf() {
    if (accept(TOK_NUM))
        return readNum();
    if (accept(TOK_ID))
        return readIdent();
    debug.logger.error("Expected a number or an identifier", getLoc());
    return nullptr;
}

ParseNode *Parser::readNum() {
    expect(TOK_NUM);
    NumberNode *node = new NumberNode(cur().content, getLoc());
    next();
    return node;
}

ParseNode *Parser::readIdent() {
    expect(TOK_ID);
    IdentifierNode *node = new IdentifierNode(cur().content, getLoc());
    next();
    return node;
}

ParseNode *Parser::readDeclaration() {
    expect(TOK_TYPENAME);
    std::string tname = cur().content;
    if (tname == "void")
        debug.logger.error("Cannot create variables of type \"void\"",
        getLoc());
    ReturnType type = RT_INT32;
    if (tname == "int")
        type = RT_INT32;
    // TODO: implement more types
    DeclarationNode *node = new DeclarationNode(getLoc(), type);
    next();
    std::vector<ParseNode *> children;
    children.push_back(readExpr());
    while (accept(TOK_COMMA))
        next(), children.push_back(readExpr());
    for (const ParseNode *child : children)
        if (child->getType() != NODE_IDENT && child->getType() != NODE_ASSIGN)
            debug.logger.error("Invalid expression in declaration", child->loc);
    expect(TOK_SEMICOL), next();
    node->childNodes = children;
    return node;
}