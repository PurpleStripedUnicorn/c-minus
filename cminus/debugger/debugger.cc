
#include "debugger.h"
#include "lexer/token.h"
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
};

Debugger::Debugger() {

}

Debugger::~Debugger() {

}

void Debugger::lexer(std::string filename, const std::vector<Token> &tokens)
const {
    std::ofstream file(filename);
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
        file << line << std::endl;
    }
    file.close();
}