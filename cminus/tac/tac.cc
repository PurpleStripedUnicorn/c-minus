
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
        "declared in this scope", node->loc);
    lastTmp = TACOperand(TACOP_VAR, id);
}

void TACGenerator::visitPrint(PrintNode *node) {
    node->child->accept(this);
    push(node->loc, TAC_PRINT, SIZE_DOUBLE, TACOperand(), lastTmp);
}

void TACGenerator::visitDeclaration(DeclarationNode *node) {
    for (ParseNode *child : node->childNodes) {
        std::string name;
        if (child->getType() == NODE_IDENT)
            name = static_cast<IdentifierNode *>(child)->content;
        else
            name = static_cast<IdentifierNode *>(static_cast<AssignNode *>
            (child)->leftChild)->content;
        if (scopes.find(name, false) != -1)
            debug.logger.error("The name \"" + name + "\" was already declared "
            "in this scope", node->loc);
        scopes.add(name, tempID++);
        if (child->getType() == NODE_ASSIGN)
            child->accept(this);
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
    //   je .L1, [left], 0      or      jle .L1, [left.first], [left.second]
    //   [middle]
    //   jmp .L2            (for if-else)
    // .L1
    //   [right]            (for if-else)
    // .L2                  (for if-else)
    TACOperand label1(TACOP_LABEL, labelID++);
    TACOperand zero(TACOP_IMM, 0);
    if (isCompareOp(node->leftChild)) {
        ifNotCondition(static_cast<BinaryNode *>(node->leftChild), label1);
    } else {
        node->leftChild->accept(this);
        push(node->loc, TAC_JE, SIZE_DOUBLE, label1, lastTmp, zero);
    }
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
    // .L1
    //   je .L2, [left], 0      or      jle .L2, [left.first], [left.second]
    //   [middle]
    //   jmp .L1
    // .L2
    TACOperand label1(TACOP_LABEL, labelID++);
    TACOperand label2(TACOP_LABEL, labelID++);
    TACOperand zero(TACOP_IMM, 0);
    push(node->loc, TAC_LABEL, SIZE_EMPTY, label1);
    if (isCompareOp(node->leftChild)) {
        ifNotCondition(static_cast<BinaryNode *>(node->leftChild), label2);
    } else {
        node->leftChild->accept(this);
        push(node->loc, TAC_JE, SIZE_DOUBLE, label2, lastTmp, zero);
    }
    node->rightChild->accept(this);
    push(node->loc, TAC_JUMP, SIZE_EMPTY, label1);
    push(node->loc, TAC_LABEL, SIZE_EMPTY, label2);
}

void TACGenerator::visitEq(EqNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
}

void TACGenerator::visitNeq(NeqNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
}

void TACGenerator::visitLt(LtNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
}

void TACGenerator::visitLte(LteNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
}

void TACGenerator::visitGt(GtNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
}

void TACGenerator::visitGte(GteNode *node) {
    debug.logger.error("Comparisons outside if or while are not implemented",
    node->loc);
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

bool TACGenerator::isCompareOp(const ParseNode *node) {
    NodeType type = node->getType();
    return type == NODE_EQ || type == NODE_NEQ || type == NODE_LT || type ==
    NODE_LTE || type == NODE_GT || type == NODE_GTE;
}

void TACGenerator::ifNotCondition(BinaryNode *node, TACOperand label) {
    TACType type;
    switch (node->getType()) {
        case NODE_EQ: type = TAC_JNE; break;
        case NODE_NEQ: type = TAC_JE; break;
        case NODE_LT: type = TAC_JGE; break;
        case NODE_LTE: type = TAC_JG; break;
        case NODE_GT: type = TAC_JLE; break;
        case NODE_GTE: type = TAC_JL; break;
        default: break;
    }
    node->leftChild->accept(this);
    TACOperand src1 = lastTmp;
    node->rightChild->accept(this);
    TACOperand src2 = lastTmp;
    push(node->loc, type, SIZE_DOUBLE, label, src1, src2);
}