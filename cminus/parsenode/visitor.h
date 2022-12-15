
#ifndef PARSENODE_VISITOR
#define PARSENODE_VISITOR

class ParseNode;
class ProgramNode;
class ScopeNode;
class EmptyNode;
class FuncNode;
class NumberNode;
class IdentifierNode;
class PrintNode;
class DeclarationNode;
class AssignNode;
class AddNode;
class SubNode;
class MulNode;
class IfNode;
class WhileNode;
class EqNode;
class NeqNode;
class LtNode;
class LteNode;
class GtNode;
class GteNode;


/**
 * Abstract base class for visitors of the parse parse tree
 * @note The visitor pattern is not entirely adhered to!
 */
class ParseTreeVisitor {

public:

    /**
     * Constructor
     */
    ParseTreeVisitor();

    /**
     * Destructor
     */
    virtual ~ParseTreeVisitor();

    /**
     * Visit any parse node
     * This function then calls a member function which processes a specific
     * node type
     * @param node The node to visit
     */
    void visit(ParseNode *node);

    /**
     * Error nodes should be reported
     * @param node The node to report
     */
    void visitErr(ParseNode *node);

    /**
     * Empty nodes generally are visited by doing nothing, so we have a default
     * function here
     * @param node The empty node
     */
    virtual void visitEmpty(EmptyNode *node);

    virtual void visitProgram(ProgramNode *node) = 0;
    virtual void visitScope(ScopeNode *node) = 0;
    virtual void visitFunc(FuncNode *node) = 0;
    virtual void visitNumber(NumberNode *node) = 0;
    virtual void visitIdentifier(IdentifierNode *node) = 0;
    virtual void visitPrint(PrintNode *node) = 0;
    virtual void visitDeclaration(DeclarationNode *node) = 0;
    virtual void visitAssign(AssignNode *node) = 0;
    virtual void visitAdd(AddNode *node) = 0;
    virtual void visitSub(SubNode *node) = 0;
    virtual void visitMul(MulNode *node) = 0;
    virtual void visitIf(IfNode *node) = 0;
    virtual void visitWhile(WhileNode *node) = 0;
    virtual void visitEq(EqNode *node) = 0;
    virtual void visitNeq(NeqNode *node) = 0;
    virtual void visitLt(LtNode *node) = 0;
    virtual void visitLte(LteNode *node) = 0;
    virtual void visitGt(GtNode *node) = 0;
    virtual void visitGte(GteNode *node) = 0;

};

#endif