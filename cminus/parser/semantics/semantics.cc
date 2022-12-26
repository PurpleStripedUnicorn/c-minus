
#include "debugger/debugger.h"
#include "scope.h"
#include "semantics.h"
#include "parsenode/nodes.h"

SemanticsVisitor::SemanticsVisitor(Debugger &debug, SymbolTable &symbolTable) :
debug(debug), symbolTable(symbolTable) { }

SemanticsVisitor::~SemanticsVisitor() { }

void SemanticsVisitor::visitProgram(ProgramNode *node) {
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitScope(ScopeNode *node) {
    scopeManager.pushScope();
    for (ParseNode *child : node->childNodes)
        child->accept(this);
    scopeManager.popScope();
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
    long long id = scopeManager.find(node->content);
    if (id == -1)
        debug.logger.error("Identifier \"" + node->content + "\" was not "
        "declared in this scope.", node->loc);
    node->rt = symbolTable[id].type;
    node->id = id;
}

void SemanticsVisitor::visitPrint(PrintNode *node) {
    node->child->accept(this);
    node->rt = RT_VOID;
}

void SemanticsVisitor::visitDeclaration(DeclarationNode *node) {
    for (ParseNode *child : node->childNodes) {
        // A declaration can either have an identifier or an assignment behind
        // it
        IdentifierNode *ident;
        if (child->getType() == NODE_IDENT)
            ident = static_cast<IdentifierNode *>(child);
        if (child->getType() == NODE_ASSIGN)
            ident = static_cast<IdentifierNode *>(static_cast<AssignNode *>(
            child)->leftChild);
        if (scopeManager.find(ident->content, false) != -1)
            debug.logger.error("The identifier \"" + ident->content + "\" was "
            "already declared in this scope", child->loc);
        Symbol symbol(ident->content, node->declareType, node->loc);
        size_t id = symbolTable.push(symbol);
        scopeManager.push(ident->content, id);
        child->accept(this);
    }
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
    if (node->rightChild != nullptr)
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
