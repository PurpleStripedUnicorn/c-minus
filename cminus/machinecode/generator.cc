
#include "allocators/registerallocator.h"
#include "generator.h"
#include "reg.h"
#include "tac/stmt.h"
#include <iostream>
#include <vector>

const std::string appendMachineCode = R"!--!(.LC0:
                .string "%d\n"
                .globl  writeinteger
writeinteger:
                pushq   %rbp
                movl    %edi, %esi
                leaq    .LC0(%rip), %rdi
                call    printf
                popq    %rbp
                ret)!--!";

MCGenerator::MCGenerator(const std::vector<TACStatement> &tac) : tac(tac) { }

MCGenerator::~MCGenerator() { }

void MCGenerator::generate() {
    machineCode.push_back(MCStatement("globl", "main"));
    machineCode.push_back(MCStatement(MC_LABEL, SIZE_EMPTY, MCOperand("main")));
    machineCode.push_back(MCStatement(MC_PUSH, SIZE_QUAD, MCOperand(REG_RBP)));
    machineCode.push_back(MCStatement(MC_MOVE, SIZE_QUAD, MCOperand(REG_RSP),
    MCOperand(REG_RBP)));
    machineCode.push_back(MCStatement(MC_SUB, SIZE_QUAD, MCOperand(0),
    MCOperand(REG_RSP)));
    for (const TACStatement &stmt : tac) {
        switch (stmt.type) {
            case TAC_EMPTY:
                break;
            case TAC_PRINT:
                convertPrint(stmt);
                break;
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
                convertBinaryArithmatic(stmt);
                break;
            case TAC_MOV:
                convertMove(stmt);
                break;
            default:
                std::cerr << "Could not convert some TAC statement to machine "
                "code at " << stmt.loc << std::endl;
                exit(1);
        }
    }
    machineCode.push_back(MCStatement(MC_MOVE, SIZE_QUAD, MCOperand(0),
    MCOperand(REG_RAX)));
    machineCode.push_back(MCStatement(MC_LEAVE));
    machineCode.push_back(MCStatement(MC_RET));
}

void MCGenerator::write(std::ostream &os) const {
    for (const MCStatement &stmt : machineCode)
        os << stmt.str() << std::endl;
    os << appendMachineCode << std::endl;
}

MCOperand MCGenerator::createOperand(TACOperand op) {
    switch (op.type) {
        case TACOP_IMM:
            return MCOperand(op.value);
        case TACOP_LABEL:
            return MCOperand(".L" + std::to_string(op.value));
        case TACOP_VAR:
            return MCOperand(assignRegister(op.value));
        default: break;
    }
    std::cerr << "Could not convert TAC operand to MC operand." << std::endl;
    exit(1);
    return MCOperand();
}

MCRegister MCGenerator::assignRegister(long long var) {
    return regAllocator.getRegister(var);
}

void MCGenerator::convertPrint(const TACStatement &stmt) {
    // [1] mov src rdi
    // [2] call writeinteger
    MCOperand src = createOperand(stmt.src1);
    machineCode.push_back(MCStatement(MC_MOVE, SIZE_QUAD, src,
    MCOperand(REG_RDI)));
    machineCode.push_back(MCStatement(MC_CALL, SIZE_EMPTY,
    MCOperand("writeinteger")));
}

void MCGenerator::convertMove(const TACStatement &stmt) {
    // [1] mov src1 dst
    MCOperand op1 = createOperand(stmt.src1);
    MCOperand dst = createOperand(stmt.dst);
    machineCode.push_back(MCStatement(MC_MOVE, SIZE_QUAD, op1, dst));
}

void MCGenerator::convertBinaryArithmatic(const TACStatement &stmt) {
    // [1] mov src1 dst
    // [2] op src2 dst
    MCType type;
    switch (stmt.type) {
        case TAC_ADD: type = MC_ADD; break;
        case TAC_SUB: type = MC_SUB; break;
        case TAC_MUL: type = MC_MUL; break;
        default: break;
    }
    MCOperand op1 = createOperand(stmt.src1);
    MCOperand op2 = createOperand(stmt.src2);
    MCOperand dst = createOperand(stmt.dst);
    machineCode.push_back(MCStatement(MC_MOVE, SIZE_QUAD, op1, dst));
    machineCode.push_back(MCStatement(type, SIZE_QUAD, op2, dst));
}