
#ifndef PARSENODE_VISITOR
#define PARSENODE_VISITOR

class ParseNode;
class ProgramNode;
class ScopeNode;
class EmptyNode;
class FuncNode;
class NumberNode;
class PrintNode;


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
    virtual void visitPrint(PrintNode *node) = 0;

};

#endif