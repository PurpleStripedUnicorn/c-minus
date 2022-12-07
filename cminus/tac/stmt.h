
#ifndef FILE_TAC_STMT
#define FILE_TAC_STMT

#include "util/sizes.h"

/**
 * Type of a TAC statement
 */
enum TACType {
    // Internal types
    TAC_ERR, TAC_EMPTY,
    // Print statements are special
    TAC_PRINT,
    // Arithmatic
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV, TAC_MOD,
    // Move operation
    TAC_MOV,
    // Jumps and branches
    TAC_LABEL, TAC_JUMP,
};

/**
 * Type of a TAC operand, which can be an immediate, a variable or a label
 * reference/definition. An empty operand is also an option because not all
 * statements require three operands
 */
enum TACOperandType {
    TACOP_EMPTY, TACOP_VAR, TACOP_IMM, TACOP_LABEL
};

/**
 * A TAC operand, of which there are generally three
 */
struct TACOperand {
    TACOperand(TACOperandType type = TACOP_EMPTY, long long value = 0) :
    type(type), value(value) { };
    TACOperandType type;
    long long value;
};

/**
 * A TAC statement, which contains the statement type, the data size of the
 * operation and the operands, of which there are generally three. One of the
 * operands is the destination and the others are source operands
 */
struct TACStatement {
    TACStatement(TACType type = TAC_EMPTY, DataSize size = SIZE_EMPTY,
    TACOperand dst = TACOperand(), TACOperand src1 = TACOperand(),
    TACOperand src2 = TACOperand()) : type(type), size(size), dst(dst),
    src1(src1), src2(src2) { };
    TACType type;
    DataSize size;
    TACOperand dst, src1, src2;
};

#endif