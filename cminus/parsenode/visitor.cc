
#include "parsenode.h"
#include "visitor.h"
#include <iostream>

ParseTreeVisitor::ParseTreeVisitor() { };

ParseTreeVisitor::~ParseTreeVisitor() { };

void ParseTreeVisitor::visit(ParseNode *node) {
    switch (node->getType()) {
        case NODE_ERR:
            visitErr(node); break;
        case NODE_EMPTY:
            visitEmpty(node); break;
        case NODE_PROGRAM:
            visitProgram(node); break;
        case NODE_SCOPE:
            visitScope(node); break;
        case NODE_FUNC:
            visitFunc(node); break;
        case NODE_STMT:
            visitStmt(node); break;
        case NODE_NUM:
            visitBasic(node); break;
        case NODE_ADD:
        case NODE_SUB:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
            visitArithmatic(node); break;
        case NODE_PRINT:
            visitPrint(node); break;
    }
}

void ParseTreeVisitor::visitErr(ParseNode *node) {
    std::cerr << "Encountered an ERROR type parse node at " << node->loc <<
    std::endl;
    exit(1);
}

void ParseTreeVisitor::visitEmpty(ParseNode *node) { }