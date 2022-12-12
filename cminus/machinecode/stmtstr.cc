
#include "stmt.h"
#include "stmtstr.h"
#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<MCType, MCFormat> mcOpTable = {
    { MC_ADD, MCFormat("add", true) },
    { MC_SUB, MCFormat("sub", true) },
    { MC_MUL, MCFormat("imul", true) },
    { MC_NEG, MCFormat("neg", true) },
    { MC_MOVE, MCFormat("mov", true) },
    { MC_COMP, MCFormat("cmp", true) },
    { MC_JE, MCFormat("je") },
    { MC_JNE, MCFormat("jne") },
    { MC_JL, MCFormat("jl", "jb") },
    { MC_JLE, MCFormat("jle", "jbe") },
    { MC_JG, MCFormat("jg", "ja") },
    { MC_JGE, MCFormat("jge", "jae") },
    { MC_JUMP, MCFormat("jmp") },
    { MC_PUSH, MCFormat("push", true) },
    { MC_POP, MCFormat("pop", true) },
    { MC_LEAVE, MCFormat("leave") },
    { MC_RET, MCFormat("ret") },
    { MC_CALL, MCFormat("call") },
    { MC_LEA, MCFormat("lea", true) },
};

std::string mcOperandString(const MCOperand &op, DataSize size) {
    switch (op.type) {
        case MCOP_ERR:
            std::cerr << "Found an ERROR type manchine code instruction." <<
            std::endl;
            exit(1);
            return "";
        case MCOP_EMPTY:
            return "";
        case MCOP_REG:
            return "%" + regToString(op.reg, size);
        case MCOP_MEM_OFF:
            return std::to_string(op.value) + "(%" + regToString(op.reg, size) +
            ")";
        case MCOP_MEM_LABEL:
            return op.label + "(%" + regToString(op.reg, size) + ")";
        case MCOP_LABEL:
            return op.label;
        case MCOP_IMM:
            return "$" + std::to_string(op.value);
    }
    return "";
}

std::string mcStatementString(const MCStatement &stmt) {
    if (stmt.type == MC_DIREC) {
        std::string out = "                ." + stmt.direcName + " ";
        while (out.size() < 24)
            out.push_back(' ');
        out.append(stmt.direcContent);
        return out;
    }
    if (stmt.type == MC_LABEL)
        return stmt.op1.str() + ":";
    if (mcOpTable.find(stmt.type) == mcOpTable.end()) {
        std::cerr << "Could not generate string for machine code operand type"
        << std::endl;
        exit(1);
    }
    MCFormat opFormat = mcOpTable.find(stmt.type)->second;
    std::string opName = opFormat.name;
    if (opFormat.hasSigned && stmt.isSigned)
        opName = opFormat.signedName;
    if (opFormat.hasSize) {
        switch (stmt.size) {
            case SIZE_EMPTY:
                std::cerr << "Attempted to append size but no size was given."
                << std::endl;
                exit(1);
            case SIZE_BYTE: opName.push_back('b'); break;
            case SIZE_WORD: opName.push_back('w'); break;
            case SIZE_DOUBLE: opName.push_back('l'); break;
            case SIZE_QUAD: opName.push_back('q'); break;
            default: break;
        }
    }
    std::string out = "                " + opName;
    if (stmt.op1.type == MCOP_EMPTY)
        return out;
    out.push_back(' ');
    while (out.size() < 24)
        out.push_back(' ');
    out.append(stmt.op1.str(stmt.size));
    if (stmt.op2.type == MCOP_EMPTY)
        return out;
    out.append(", ");
    out.append(stmt.op2.str(stmt.size));
    return out;
}

std::string regToString(MCRegister reg, DataSize size) {
    if (reg >= REG_R8) {
        std::string out = "r" + std::to_string(static_cast<int>(reg));
        switch (size) {
            case SIZE_BYTE: out.push_back('b'); break;
            case SIZE_WORD: out.push_back('w'); break;
            case SIZE_DOUBLE: out.push_back('d'); break;
            default: break;
        }
        return out;
    }
    std::string out;
    switch (reg) {
        case REG_RAX: out = "ax"; break;
        case REG_RBX: out = "bx"; break;
        case REG_RCX: out = "cx"; break;
        case REG_RDX: out = "dx"; break;
        case REG_RSI: out = "si"; break;
        case REG_RDI: out = "di"; break;
        case REG_RBP: out = "bp"; break;
        case REG_RSP: out = "sp"; break;
        default: break;
    }
    // NOTE: We do not use 'h' byte registers here
    if (size == SIZE_BYTE) {
        if (out.back() == 'x')
            out.back() = 'l';
        else
            out.push_back('l');
    }
    if (size == SIZE_DOUBLE)
        out = "e" + out;
    if (size == SIZE_QUAD)
        out = "r" + out;
    return out;
}