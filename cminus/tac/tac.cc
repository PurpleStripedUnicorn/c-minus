
#include "debugger/debugger.h"
#include "parsenode/nodes.h"
#include "parsenode/parsenode.h"
#include "stmt.h"
#include "tac.h"

TACGenerator::TACGenerator(Debugger &debug) : debug(debug), tempID(0) { }

TACGenerator::~TACGenerator() { }

const std::vector<TACStatement> &TACGenerator::getTAC() const {
    return tac;
}

void TACGenerator::visitProgram(ProgramNode *node) {
    for (ParseNode *child : node->children())
        child->accept(this);
}

void TACGenerator::visitScope(ScopeNode *node) {
    // TODO: Add scope functionality
    for (ParseNode *child : node->children())
        child->accept(this);
}

void TACGenerator::visitFunc(FuncNode *node) {
    // TODO: implement function calls, etc.
    node->child->accept(this);
}

void TACGenerator::visitNumber(NumberNode *node) {
    TACOperand dst(TACOP_VAR, tempID++);
    TACOperand src(TACOP_IMM, std::stoll(node->content));
    push(node->loc, TAC_MOV, SIZE_DOUBLE, dst, src);
    lastTmp = dst;
}

void TACGenerator::visitPrint(PrintNode *node) {
    node->child->accept(this);
    push(node->loc, TAC_PRINT, SIZE_DOUBLE, TACOperand(), lastTmp);
}

void TACGenerator::push(const TACStatement &stmt) {
    debug.tacStatements.push_back(stmt);
    tac.push_back(stmt);
}

template<class... T>
void TACGenerator::push(T... args) {
    push(TACStatement(args...));
}