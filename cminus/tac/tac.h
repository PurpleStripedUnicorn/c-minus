
#ifndef FILE_TAC
#define FILE_TAC

#include "parsenode/base.h"
#include "parsenode/visitor.h"
#include "scope.h"
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
    virtual void visitIdentifier(IdentifierNode *node) override;
    virtual void visitPrint(PrintNode *node) override;
    virtual void visitDeclaration(DeclarationNode *node) override;
    virtual void visitAssign(AssignNode *node) override;
    virtual void visitAdd(AddNode *node) override;
    virtual void visitSub(SubNode *node) override;
    virtual void visitMul(MulNode *node) override;
    virtual void visitIf(IfNode *node) override;
    virtual void visitWhile(WhileNode *node) override;

private:

    /**
     * Add a TAC statement to the generated output
     * @param stmt The TAC statement
     * @note This function also ensures the debugger is used
     */
    void push(const TACStatement &stmt);
    template<class... T> void push(T... args);

    /**
     * Create a new temporary TAC operand
     * @post The tempID is updated
     * @return The newly created operand
     * @warning lastTmp is NOT updated!
     */
    TACOperand newTmp();

    /**
     * Convert a basic binary arithmatic operation
     * @param type The TAC operation type
     * @param node The node to convert to TAC
     */
    void visitBinaryStatement(TACType type, BinaryNode *node);

    // Generated statements
    std::vector<TACStatement> tac;
    // The debugger
    Debugger &debug;
    // Temporary variable counter
    long long tempID;
    // Label ID counter
    long long labelID;
    // Last temporary value that was written to (is a TAC operand)
    TACOperand lastTmp;
    // Scope manager
    ScopeManager scopes;

};

#endif