
#include "parsenode.h"
#include "parsenode/base.h"
#include "parsenode/nodes.h"
#include "visitor.h"
#include <iostream>

ParseTreeVisitor::ParseTreeVisitor() { };

ParseTreeVisitor::~ParseTreeVisitor() { };

void ParseTreeVisitor::visit(ParseNode *node) {
    switch (node->getType()) {
        case NODE_ERR:
            visitErr(node); break;
        case NODE_EMPTY:
            visitEmpty(static_cast<EmptyNode *>(node)); break;
        case NODE_PROGRAM:
            visitProgram(static_cast<ProgramNode *>(node)); break;
        case NODE_SCOPE:
            visitScope(static_cast<ScopeNode *>(node)); break;
        case NODE_FUNC:
            visitFunc(static_cast<FuncNode *>(node)); break;
        case NODE_NUM:
            visitNumber(static_cast<NumberNode *>(node)); break;
        case NODE_IDENT:
            visitIdentifier(static_cast<IdentifierNode *>(node)); break;
        case NODE_PRINT:
            visitPrint(static_cast<PrintNode *>(node)); break;
        case NODE_DECL:
            visitDeclaration(static_cast<DeclarationNode *>(node)); break;
        case NODE_ASSIGN:
            visitAssign(static_cast<AssignNode *>(node)); break;
        case NODE_ADD:
            visitAdd(static_cast<AddNode *>(node)); break;
        case NODE_SUB:
            visitSub(static_cast<SubNode *>(node)); break;
        case NODE_MUL:
            visitMul(static_cast<MulNode *>(node)); break;
        case NODE_IF:
            visitIf(static_cast<IfNode *>(node)); break;
        case NODE_WHILE:
            visitWhile(static_cast<WhileNode *>(node)); break;
    }
}

void ParseTreeVisitor::visitErr(ParseNode *node) {
    std::cerr << "Encountered an ERROR type parse node at " << node->loc <<
    std::endl;
    exit(1);
}

void ParseTreeVisitor::visitEmpty(EmptyNode *node) { (void)node; }