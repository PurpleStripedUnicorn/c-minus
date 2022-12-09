
#ifndef FILE_MC_STMT
#define FILE_MC_STMT

#include <string>

/**
 * Type of a machine code operand
 */
enum MCOperandType {
    MCOP_ERR,
    MCOP_MEM,
    MCOP_REG,
    MCOP_LABEL
};

/**
 * Type of a machine code statement/instruction
 */
enum MCType {
    // Special error type
    MC_ERR,
    // Arithmatic
    MC_ADD, MC_SUB, MC_MUL, MC_NEG,
    // Move instruction
    MC_MOVE,
    // Special print instruction
    MC_PRINT,
    // 
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
 * an immediate
 * @note The stored "value" here, can refer to a register or an immediate,
 * depending on the operand type. Offset is only used in the case of a memory
 * reference.
 * @note In case of a memory 
 */
struct MCOperand {
    // TODO: improve this to allow all instructions!
    MCOperandType type;
    long long value, offset;
    std::string label;
    std::string str() const;
};

/**
 * A machine code statement (x86)
 * Unlike TAC, these statements generally only have two operands
 * @warning Validity of these operands and compatilibity with the operation is
 * not checked
 */
struct MCStatement {
    MCType type;
    MCOperand op1, op2;
    std::string str() const;
};

#endif
