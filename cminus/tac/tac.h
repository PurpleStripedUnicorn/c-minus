
#ifndef FILE_TAC
#define FILE_TAC

#include "parsenode/visitor.h"
#include "stmt.h"
#include <vector>

class Debugger;

/**
 * Generator for Three-Address Code, which uses the visitor pattern
 */
class TACGenerator : public ParseTreeVisitor {

public:

    /**
     * Constructor
     * @param debug The debugger
     */
    TACGenerator(Debugger &debug);

    /**
     * Destructor
     */
    ~TACGenerator();

    /**
     * Get the generated three-address code (up until this point)
     * @return A constant reference to the three-address code
     */
    const std::vector<TACStatement> &getTAC() const;

    virtual void visitProgram(ProgramNode *node) override;
    virtual void visitScope(ScopeNode *node) override;
    virtual void visitFunc(FuncNode *node) override;
    virtual void visitNumber(NumberNode *node) override;
    virtual void visitPrint(PrintNode *node) override;

private:

    /**
     * Add a TAC statement to the generated output
     * @param stmt The TAC statement
     * @note This function also ensures the debugger is used
     */
    void push(const TACStatement &stmt);
    template<class... T> void push(T... args);

    // Generated statements
    std::vector<TACStatement> tac;
    // The debugger
    Debugger &debug;
    // Temporary variable counter
    long long tempID;
    // Last temporary value that was written to (is a TAC operand)
    TACOperand lastTmp;

};

#endif