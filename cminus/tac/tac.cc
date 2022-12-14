
#include "debugger/debugger.h"
#include "parsenode/base.h"
#include "parsenode/nodes.h"
#include "parsenode/parsenode.h"
#include "stmt.h"
#include "tac.h"
#include <iostream>

TACGenerator::TACGenerator(Debugger &debug) : debug(debug), tempID(0),
labelID(0) { }

TACGenerator::~TACGenerator() { }

const std::vector<TACStatement> &TACGenerator::getTAC() const {
    return tac;
}

void TACGenerator::visitProgram(ProgramNode *node) {
    for (ParseNode *child : node->children())
        child->accept(this);
}

void TACGenerator::visitScope(ScopeNode *node) {
    scopes.pushScope();
    for (ParseNode *child : node->children())
        child->accept(this);
    scopes.popScope();
}

void TACGenerator::visitFunc(FuncNode *node) {
    // TODO: implement function calls, etc.
    node->child->accept(this);
}

void TACGenerator::visitNumber(NumberNode *node) {
    lastTmp = TACOperand(TACOP_IMM, std::stoll(node->content));
}

void TACGenerator::visitIdentifier(IdentifierNode *node) {
    long long id = scopes.find(node->content);
    if (id == -1)
        debug.logger.error("The identifier \"" + node->content + "\" was not "
        "declared in this scope");
    lastTmp = TACOperand(TACOP_VAR, id);
}

void TACGenerator::visitPrint(PrintNode *node) {
    node->child->accept(this);
    push(node->loc, TAC_PRINT, SIZE_DOUBLE, TACOperand(), lastTmp);
}

void TACGenerator::visitDeclaration(DeclarationNode *node) {
    // NOTE: Currently it is guaranteed that the children are identifier nodes
    for (ParseNode *child : node->childNodes) {
        std::string name = static_cast<IdentifierNode *>(child)->content;
        if (scopes.find(name, false) != -1)
            debug.logger.error("The name \"" + name + "\" was already declared "
            "in this scope", node->loc);
        scopes.add(name, tempID++);
    }
}

void TACGenerator::visitAssign(AssignNode *node) {
    std::string name = static_cast<IdentifierNode *>(node->leftChild)->content;
    long long id = scopes.find(name);
    if (id == -1) {
        debug.logger.error("The name \"" + name + "\" was not declared in this "
        "scope", node->loc);
    }
    node->rightChild->accept(this);
    TACOperand dst(TACOP_VAR, id);
    TACOperand src = lastTmp;
    push(node->loc, TAC_MOV, SIZE_DOUBLE, dst, src);
    lastTmp = dst;
}

void TACGenerator::visitAdd(AddNode *node) {
    visitBinaryStatement(TAC_ADD, node);
}

void TACGenerator::visitSub(SubNode *node) {
    visitBinaryStatement(TAC_SUB, node);
}

void TACGenerator::visitMul(MulNode *node) {
    visitBinaryStatement(TAC_MUL, node);
}

void TACGenerator::visitIf(IfNode *node) {
    //   je .L1, [left], 0
    //   [middle]
    //   jmp .L2            (for if-else)
    // .L1
    //   [right]            (for if-else)
    // .L2                  (for if-else)
    node->leftChild->accept(this);
    TACOperand label1(TACOP_LABEL, labelID++);
    TACOperand zero(TACOP_IMM, 0);
    push(node->loc, TAC_JE, SIZE_DOUBLE, label1, lastTmp, zero);
    node->middleChild->accept(this);
    TACOperand label2;
    if (node->hasElse) {
        label2 = TACOperand(TACOP_LABEL, labelID++);
        push(node->loc, TAC_JUMP, SIZE_EMPTY, label2);
    }
    push(node->loc, TAC_LABEL, SIZE_EMPTY, label1);
    if (node->hasElse) {
        node->rightChild->accept(this);
        push(node->loc, TAC_LABEL, SIZE_EMPTY, label2);
    }
}

void TACGenerator::visitWhile(WhileNode *node) {
    (void)node;
    std::cerr << "Not implemented" << std::endl;
    exit(1);
}

void TACGenerator::push(const TACStatement &stmt) {
    debug.tacStatements.push_back(stmt);
    tac.push_back(stmt);
}

template<class... T>
void TACGenerator::push(T... args) {
    push(TACStatement(args...));
}

TACOperand TACGenerator::newTmp() {
    return TACOperand(TACOP_VAR, tempID++);
}

void TACGenerator::visitBinaryStatement(TACType type, BinaryNode *node) {
    node->leftChild->accept(this);
    TACOperand src1 = lastTmp;
    node->rightChild->accept(this);
    TACOperand src2 = lastTmp;
    TACOperand dst = newTmp();
    push(node->loc, type, SIZE_DOUBLE, dst, src1, src2);
    lastTmp = dst;
}