
#ifndef FILE_MC_GENERATOR
#define FILE_MC_GENERATOR

#include "reg.h"
#include "stmt.h"
#include <ostream>
#include <vector>

struct TACOperand;
struct TACStatement;

class MCGenerator {

public:

    /**
     * Constructor
     * @param tac A constant reference to the input three-address code
     */
    MCGenerator(const std::vector<TACStatement> &tac);

    /**
     * Destructor
     */
    ~MCGenerator();

    /**
     * Generate machine code from the input three-address code
     */
    void generate();

    /**
     * Write the generated machine code to an output stream
     * @param os The output stream to write to
     */
    void write(std::ostream &os) const;

private:

    /**
     * Generate a machine code operand from a TAC operand
     * @param op The TAC operand
     * @return A machine code operand
     */
    MCOperand createOperand(TACOperand op);

    /**
     * Get a register for a TAC variable
     * @param var The TAC variable index
     * @warning NOT IMPLEMENTED!
     */
    MCRegister assignRegister(long long var);

    /**
     * Convert a print statement
     * @param stmt The statement to convert
     */
    void convertPrint(const TACStatement &stmt);

    /**
     * Convert a binary arithmatic TAC statement to machine code
     * @param stmt The statement to convert
     */
    void convertBinaryArithmatic(const TACStatement &stmt);

    /**
     * Convert a move TAC statement to machine code
     * @param stmt The statement to convert
     */
    void convertMove(const TACStatement &stmt);

    // Reference to the input three-address code
    const std::vector<TACStatement> &tac;
    // The generated machine code
    std::vector<MCStatement> machineCode;

};

#endif