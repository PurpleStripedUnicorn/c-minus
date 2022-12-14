
#include "debugger.h"
#include "lexer/token.h"
#include "parsenode/parsenode.h"
#include "tac/stmt.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const std::unordered_map<TokenType, std::string> tokenTable = {
    { TOK_END, "END" },
    { TOK_ERR, "ERR" },
    { TOK_IF, "IF" },
    { TOK_ELSE, "ELSE" },
    { TOK_WHILE, "WHIlE" },
    { TOK_ID, "ID" },
    { TOK_TYPENAME, "TYPENAME" },
    { TOK_NUM, "NUM" },
    { TOK_COMMA, "," },
    { TOK_SEMICOL, ";" },
    { TOK_LBRACE, "(" },
    { TOK_RBRACE, ")" },
    { TOK_LCBRACE, "{" },
    { TOK_RCBRACE, "}" },
    { TOK_ASSIGN, "=" },
    { TOK_EQ, "==" },
    { TOK_PLUS, "+" },
    { TOK_TIMES, "*" },
    { TOK_MINUS, "-" },
    { TOK_DIV, "/" },
    { TOK_MOD, "%" },
};

const std::unordered_map<NodeType, std::string> nodeTypeTable = {
    { NODE_ERR, "ERR" },
    { NODE_EMPTY, "EMPTY" },
    { NODE_PROGRAM, "PROGRAM" },
    { NODE_SCOPE, "SCOPE" },
    { NODE_FUNC, "FUNC" },
    { NODE_NUM, "NUM" },
    { NODE_IDENT, "ID" },
    { NODE_ADD, "+" },
    { NODE_SUB, "-" },
    { NODE_MUL, "*" },
    { NODE_DIV, "/" },
    { NODE_MOD, "%" },
    { NODE_PRINT, "PRINT" },
    { NODE_IF, "IF" },
    { NODE_WHILE, "WHILE" },
    { NODE_DECL, "DECL" },
    { NODE_ASSIGN, "=" },
};

const std::unordered_map<TACType, std::string> tacTypes = {
    { TAC_ERR, "ERR" },
    { TAC_EMPTY, "EMPTY" },
    { TAC_PRINT, "PRINT" },
    { TAC_ADD, "ADD" },
    { TAC_SUB, "SUB" },
    { TAC_MUL, "MUL" },
    { TAC_DIV, "DIV" },
    { TAC_MOD, "MOD" },
    { TAC_MOV, "MOV" },
    { TAC_ERR, "LABEL" },
    { TAC_JUMP, "JUMP" },
    { TAC_JE, "JE" },
    { TAC_JNE, "JNE" },
    { TAC_JL, "JL" },
    { TAC_JLE, "JLE" },
    { TAC_JG, "JG" },
    { TAC_JGE, "JGE" },
};

Debugger::Debugger() : tree(nullptr), enabled(false) { }

Debugger::~Debugger() { }

void Debugger::enable() {
    enabled = true;
}

void Debugger::lexer(std::ostream &os) const {
    if (enabled) {
        for (const Token &token : tokens) {
            std::string tokenName = "??";
            if (tokenTable.find(token.type) != tokenTable.end())
                tokenName = tokenTable.find(token.type)->second;
            std::string line = token.loc.str();
            while (line.size() < 8)
                line.push_back(' ');
            line.append(tokenName);
            while (line.size() < 16)
                line.push_back(' ');
            line.append(token.content);
            os << line << std::endl;
        }
    }
}

void Debugger::parser(std::ostream &os) const {
    if (enabled)
        parser(os, tree, 0);
}

void Debugger::tac(std::ostream &os) const {
    if (enabled) {
        for (const TACStatement &stmt : tacStatements) {
            std::string name = "??";
            if (tacTypes.find(stmt.type) != tacTypes.end())
                name = tacTypes.find(stmt.type)->second;
            std::string line = stmt.loc.str();
            while (line.size() < 8)
                line.push_back(' ');
            line.append(name);
            while (line.size() < 14)
                line.push_back(' ');
            line.append(tacOperandStr(stmt.dst));
            line.append(", ");
            line.append(tacOperandStr(stmt.src1));
            line.append(", ");
            line.append(tacOperandStr(stmt.src2));
            os << line << std::endl;
        }
    }
}

void Debugger::parser(std::ostream &os, const ParseNode *node, size_t depth)
const {
    if (node == nullptr)
        return;
    os << node->loc << " ";
    for (size_t i = node->loc.str().size(); i < depth + 3; i++)
        os << "   ";
    if (nodeTypeTable.find(node->getType()) == nodeTypeTable.end())
        os << "??";
    else
        os << nodeTypeTable.find(node->getType())->second;
    os << std::endl;
    for (const ParseNode *child : node->children())
        parser(os, child, depth + 1);
}

std::string Debugger::tacOperandStr(const TACOperand &op) const {
    if (op.type == TACOP_EMPTY)
        return "";
    if (op.type == TACOP_VAR)
        return "t" + std::to_string(op.value);
    if (op.type == TACOP_IMM)
        return std::to_string(op.value);
    if (op.type == TACOP_LABEL)
        return ".L" + std::to_string(op.value);
    logger.error("Could not convert TAC operand to string");
    return "";
}