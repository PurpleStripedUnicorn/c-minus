
#ifndef FILE_MC_STMT
#define FILE_MC_STMT

#include "reg.h"
#include "util/sizes.h"
#include <string>

/**
 * Type of a machine code operand. Each corresponding format of machine code
 * operand is written before the enum names
 */
enum MCOperandType {
    // Empty and error type operands
    MCOP_ERR, MCOP_EMPTY,
    // %rax
    MCOP_REG,
    // 0(%rax)
    MCOP_MEM_OFF,
    // .L0(%rax)
    MCOP_MEM_LABEL,
    // .L0
    MCOP_LABEL,
};

/**
 * Type of a machine code statement/instruction
 */
enum MCType {
    // Special error type
    MC_ERR,
    // Assembly directive
    MC_DIREC,
    // Arithmatic
    MC_ADD, MC_SUB, MC_MUL, MC_NEG,
    // Move instruction
    MC_MOVE,
    // Special print instruction
    MC_PRINT,
    // Compare instruction
    MC_COMP,
    // Jumps and branches
    MC_JE, MC_JNE, MC_JL, MC_JLE, MC_JG, MC_JGE,
    // Labels and jump
    MC_LABEL, MC_JUMP,
    // Stack operations
    MC_PUSH, MC_POP,
    // Functions
    MC_LEAVE, MC_RET, MC_CALL,
    // Memory operations
    MC_LEA,
};

/**
 * A machine code operand, which can refer to a memory address, a register, or
 * an immediate. See MCOperandType for more information on formats
 */
struct MCOperand {
    MCOperandType type;
    MCRegister reg;
    long long offset;
    std::string label;
    std::string str(DataSize size = SIZE_EMPTY) const;
};

/**
 * A machine code statement (x86)
 * Unlike TAC, these statements generally only have two operands
 * @warning Validity of these operands and compatilibity with the operation is
 * not checked
 */
struct MCStatement {
    MCType type;
    DataSize size;
    MCOperand op1, op2;
    std::string direcName, direcContent;
    std::string str() const;
};

/**
 * Get the string representation of a register
 */
std::string regToString(MCRegister reg, DataSize size);

#endif
