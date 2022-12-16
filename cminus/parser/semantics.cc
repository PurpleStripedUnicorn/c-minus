
#include "debugger/debugger.h"
#include "semantics.h"
#include "parsenode/nodes.h"

SemanticsVisitor::SemanticsVisitor(Debugger &debug) : debug(debug) { }

SemanticsVisitor::~SemanticsVisitor() { }

void SemanticsVisitor::visitProgram(ProgramNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitScope(ScopeNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitFunc(FuncNode *node) {
    node->child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitNumber(NumberNode *node) {
    node->rt = RT_INT32;
}

void SemanticsVisitor::visitIdentifier(IdentifierNode *node) {
    // TODO: make a symbol table
}

void SemanticsVisitor::visitPrint(PrintNode *node) {
    node->child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitDeclaration(DeclarationNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitAssign(AssignNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->rightChild->rt;
}

void SemanticsVisitor::visitAdd(AddNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void SemanticsVisitor::visitSub(SubNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void SemanticsVisitor::visitMul(MulNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = node->leftChild->rt;
}

void SemanticsVisitor::visitIf(IfNode *node) {
    node->leftChild->accept(this);
    node->middleChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitWhile(WhileNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitEq(EqNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void SemanticsVisitor::visitNeq(NeqNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void SemanticsVisitor::visitLt(LtNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void SemanticsVisitor::visitLte(LteNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void SemanticsVisitor::visitGt(GtNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}

void SemanticsVisitor::visitGte(GteNode *node) {
    node->leftChild->accept(this);
    node->rightChild->accept(this);
    node->rt = RT_BOOL;
}
