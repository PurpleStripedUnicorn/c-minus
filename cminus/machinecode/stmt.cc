
#include "stmt.h"
#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<MCType, std::string> mcOpTable = {
    { MC_ADD, "add" },
    { MC_SUB, "sub" },
    { MC_MUL, "mul" },
    { MC_NEG, "neg" },
    { MC_MOVE, "mov" },
    { MC_COMP, "cmp" },
    { MC_JE, "je" },
    { MC_JNE, "jne" },
    { MC_JL, "jl" },
    { MC_JLE, "jle" },
    { MC_JG, "jg" },
    { MC_JGE, "jge" },
    { MC_JUMP, "jmp" },
    { MC_PUSH, "push" },
    { MC_POP, "pop" },
    { MC_LEAVE, "leave" },
    { MC_RET, "ret" },
    { MC_CALL, "call" },
    { MC_LEA, "lea" },
};

std::string MCOperand::str(DataSize size) const {
    switch (type) {
        case MCOP_ERR:
            std::cerr << "Found an ERROR type manchine code instruction." <<
            std::endl;
            exit(1);
            return "";
        case MCOP_EMPTY:
            return "";
        case MCOP_REG:
            return "%" + regToString(reg, size);
        case MCOP_MEM_OFF:
            return std::to_string(value) + "(%" + regToString(reg, size) + ")";
        case MCOP_MEM_LABEL:
            return label + "(%" + regToString(reg, size) + ")";
        case MCOP_LABEL:
            return label;
        case MCOP_IMM:
            return "$" + std::to_string(value);
    }
    return "";
}

std::string MCStatement::str() const {
    if (type == MC_DIREC) {
        std::string out = "                ." + direcName + " ";
        while (out.size() < 24)
            out.push_back(' ');
        out.append(direcContent);
        return out;
    }
    if (type == MC_LABEL)
        return op1.str() + ":";
    if (mcOpTable.find(type) == mcOpTable.end()) {
        std::cerr << "Could not generate string for machine code operand type"
        << std::endl;
        exit(1);
    }
    std::string opName = mcOpTable.find(type)->second;
    std::string out = "                " + opName;
    if (op1.type == MCOP_EMPTY)
        return out;
    out.push_back(' ');
    while (out.size() < 24)
        out.push_back(' ');
    out.append(op1.str(size));
    if (op2.type == MCOP_EMPTY)
        return out;
    out.append(", ");
    out.append(op2.str(size));
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