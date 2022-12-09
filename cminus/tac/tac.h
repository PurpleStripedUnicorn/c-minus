
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

    virtual void visitProgram(ParseNode *node) override;
    virtual void visitScope(ParseNode *node) override;
    virtual void visitFunc(ParseNode *node) override;
    virtual void visitStmt(ParseNode *node) override;
    virtual void visitBasic(ParseNode *node) override;
    virtual void visitArithmatic(ParseNode *node) override;
    virtual void visitPrint(ParseNode *node) override;

private:

    /**
     * Add a TAC statement to the generated output
     * @param stmt The TAC statement
     * @note This function also ensures the debugger is used
     */
    void add(const TACStatement &stmt);

    // Generated statements
    std::vector<TACStatement> tac;
    // The debugger
    Debugger &debug;

};

#endif