
#include "debugger.h"
#include "lexer/token.h"
#include "parsenode/parsenode.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

const std::unordered_map<TokenType, std::string> tokenTable = {
    { TOK_END, "END" },
    { TOK_ERR, "ERR" },
    { TOK_ID, "ID" },
    { TOK_COMMA, "," },
    { TOK_LBRACE, "(" },
    { TOK_RBRACE, ")" },
    { TOK_LCBRACE, "{" },
    { TOK_RCBRACE, "}" },
    { TOK_EQ, "=" },
    { TOK_PLUS, "+" },
    { TOK_MINUS, "-" },
    { TOK_TIMES, "*" },
    { TOK_DIV, "/" },
    { TOK_MOD, "%" },
    { TOK_SEMICOL, ";" },
    { TOK_NUM, "NUM" },
    { TOK_TYPENAME, "TYPE" },
    { TOK_PRINT, "PRINT" },
};

const std::unordered_map<NodeType, std::string> nodeTypeTable = {
    { NODE_ERR, "ERR" },
    { NODE_EMPTY, "EMPTY" },
    { NODE_PROGRAM, "PROGRAM" },
    { NODE_SCOPE, "SCOPE" },
    { NODE_FUNC, "FUNC" },
    { NODE_STMT, "STMT" },
    { NODE_NUM, "NUM" },
    { NODE_ADD, "+" },
    { NODE_SUB, "-" },
    { NODE_MUL, "*" },
    { NODE_DIV, "/" },
    { NODE_MOD, "%" },
    { NODE_PRINT, "PRINT" },
};

Debugger::Debugger() : enabled(false) { }

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

void Debugger::parser(std::ostream &os, const ParseNode *node, size_t depth)
const {
    for (size_t i = 0; i < depth; i++)
        os << "   ";
    if (nodeTypeTable.find(node->getType()) == nodeTypeTable.end())
        os << "??";
    else
        os << nodeTypeTable.find(node->getType())->second;
    os << std::endl;
    for (const ParseNode *child : node->children())
        parser(os, child, depth + 1);
}