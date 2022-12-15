
#include "types.h"
#include "parsenode/nodes.h"

TypeVisitor::TypeVisitor() : debug(debug) { }

TypeVisitor::~TypeVisitor() { }

void TypeVisitor::visitProgram(ProgramNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitScope(ScopeNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitFunc(FuncNode *node) {
    node->child->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitNumber(NumberNode *node) {
    node->rt = RT_INT32;
}

void TypeVisitor::visitIdentifier(IdentifierNode *node) {
    // TODO: make a symbol table
}

void TypeVisitor::visitPrint(PrintNode *node) {
    node->child->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitDeclaration(DeclarationNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitAssign(AssignNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->rightChild->rt;
}

void TypeVisitor::visitAdd(AddNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void TypeVisitor::visitSub(SubNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void TypeVisitor::visitMul(MulNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void TypeVisitor::visitIf(IfNode *node) {
    node->leftChild->accept(this);
    node->middleChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitWhile(WhileNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_VOID;
}

void TypeVisitor::visitEq(EqNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void TypeVisitor::visitNeq(NeqNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void TypeVisitor::visitLt(LtNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void TypeVisitor::visitLte(LteNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void TypeVisitor::visitGt(GtNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void TypeVisitor::visitGte(GteNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}
