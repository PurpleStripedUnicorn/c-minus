
#ifndef FILE_MC_STMTSTR
#define FILE_MC_STMTSTR

#include "reg.h"
#include "stmt.h"
#include "util/sizes.h"
#include <ostream>
#include <string>

struct MCOperand;
struct MCStatement;

/**
 * The formatting of a specific x86 instruction. Indicates if there are special
 * signed versions, if it depends on size, etc.
 * @note The enum type of the machine code operation is not included because it
 * should be the key of a map!
 */
struct MCFormat {
    MCFormat(std::string name, bool hasSize = false) : name(name),
    hasSigned(false), hasSize(hasSize) { }
    MCFormat(std::string name, std::string signedName, bool hasSize = false) :
    name(name), signedName(signedName), hasSigned(true), hasSize(hasSize) { }
    std::string name;
    std::string signedName;
    bool hasSigned;
    bool hasSize;
};

/**
 * Convert a machine code operand to a string
 * @param op The machine code operand
 * @param size The data size of the instruction
 * @return A string representation of the machine code operand
 */
std::string mcOperandString(const MCOperand &op, DataSize size);

/**
 * Convert a machine code statement to a string (without trailing line ending)
 * @param stmt The statement to convert
 * @return A string representation of the statement, as in GNU assembly
 */
std::string mcStatementString(const MCStatement &stmt);

/**
 * Convert a register to a string representation
 * @param reg The register to convert
 * @param size The data size of the register
 * @return A string representation of the register
 */
std::string regToString(MCRegister reg, DataSize size);

#endif