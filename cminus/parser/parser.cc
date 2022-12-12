
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
    if (!accept(type)) {
        std::cerr << "Incorrect token type matched at " << getLoc() << ". "
        "Expected (" << int(type) << ") got (" << int(cur().type) << ")."
        << std::endl;
        exit(1);
    }
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
    ParseNode *node = readExpr();
    expect(TOK_SEMICOL), next();
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
    ParseNode *leftNode = readSum();
    if (!accept(TOK_ASSIGN)) {
        delete node;
        return leftNode;
    }
    node->leftChild = leftNode;
    next();
    if (leftNode->getType() != NODE_IDENT) {
        std::cerr << "Expected an identifier before assignment." << std::endl;
        exit(1);
    }
    ParseNode *rightNode = readAssign();
    node->rightChild = rightNode;
    return node;
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
    std::cerr << "Expected an expression base." << std::endl;
    exit(1);
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
    if (tname == "void") {
        std::cerr << "Cannot create variables of type 'void'." << std::endl;
        exit(1);
    }
    ReturnType type = RT_INT;
    if (tname == "int")
        type = RT_INT;
    // TODO: implement more types
    DeclarationNode *node = new DeclarationNode(getLoc(), type);
    next();
    // NOTE: currently it is guaranteed that the children are identifiers
    std::vector<ParseNode *> children;
    children.push_back(readIdent());
    while (accept(TOK_COMMA))
        next(), children.push_back(readIdent());
    expect(TOK_SEMICOL), next();
    node->childNodes = children;
    return node;
}