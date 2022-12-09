
#include "debugger/debugger.h"
#include "parsenode/nodes.h"
#include "parsenode/parsenode.h"
#include "stmt.h"
#include "tac.h"

TACGenerator::TACGenerator(Debugger &debug) : debug(debug) { }

TACGenerator::~TACGenerator() { }

void TACGenerator::visitProgram(ParseNode *node) {
    
}

void TACGenerator::visitScope(ParseNode *node) {

}

void TACGenerator::visitFunc(ParseNode *node) {

}

void TACGenerator::visitStmt(ParseNode *node) {

}

void TACGenerator::visitBasic(ParseNode *node) {

}

void TACGenerator::visitArithmatic(ParseNode *node) {

}

void TACGenerator::visitPrint(ParseNode *node) {

}

void TACGenerator::add(const TACStatement &stmt) {
    debug.tacStatements.push_back(stmt);
    tac.push_back(stmt);
}