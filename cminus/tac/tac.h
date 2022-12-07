
#ifndef FILE_TAC
#define FILE_TAC

#include "parsenode/visitor.h"
#include "stmt.h"
#include <vector>

/**
 * Generator for Three-Address Code, which uses the visitor pattern
 */
class TACGenerator : public ParseTreeVisitor {

public:

    /**
     * Constructor
     */
    TACGenerator();

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

    // Generated statements
    std::vector<TACStatement> tac;

};

#endif