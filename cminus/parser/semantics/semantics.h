
#ifndef FILE_PARSER_SEMANTICS
#define FILE_PARSER_SEMANTICS

#include "parsenode/nodes.h"
#include "parsenode/visitor.h"
#include "scope.h"
#include "symboltable.h"
#include <unordered_map>
#include <vector>

class Debugger;

/**
 * Class used to determine return types of parse nodes
 */
class SemanticsVisitor : public ParseTreeVisitor {

public:

    /**
     * Constructor
     * @param debug The debugger
     * @param symbolTable The main symbol table
     */
    SemanticsVisitor(Debugger &debug, SymbolTable &symbolTable);

    /**
     * Destructor
     */
    ~SemanticsVisitor();

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
    virtual void visitEq(EqNode *node) override;
    virtual void visitNeq(NeqNode *node) override;
    virtual void visitLt(LtNode *node) override;
    virtual void visitLte(LteNode *node) override;
    virtual void visitGt(GtNode *node) override;
    virtual void visitGte(GteNode *node) override;

private:

    // The debugger
    Debugger &debug;

    // The symbol table
    SymbolTable &symbolTable;

    // The scope manager, to keep track of scoping of variables/symbols
    // Has a stack that keeps track of scopes
    ScopeManager scopeManager;

};

#endif