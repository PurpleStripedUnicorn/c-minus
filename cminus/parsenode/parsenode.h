
#ifndef FILE_PARSENODE
#define FILE_PARSENODE

#include "util/loc.h"
#include <vector>

class ParseNode;
class ParseTreeVisitor;

/**
 * The type of a parse node
 */
enum NodeType {
    NODE_ERR,
    // Empty node
    NODE_EMPTY,
    // Main program nodes
    NODE_PROGRAM,
    NODE_SCOPE,
    NODE_FUNC,
    // Basic nodes
    NODE_NUM, NODE_IDENT,
    // Arithmatic
    NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV, NODE_MOD,
    // Print statements
    NODE_PRINT,
    // Other statements
    NODE_IF, NODE_WHILE,
    // Declarations
    NODE_DECL,
    // Assignment node
    NODE_ASSIGN,
    // Comparisons
    NODE_EQ, NODE_NEQ, NODE_LT, NODE_LTE, NODE_GT, NODE_GTE,
};

/**
 * Base class for parse nodes
 */
class ParseNode {

public:

    /**
     * Constructor
     * @param type The type of the parse node
     * @param loc The location of the parse node
     */
    ParseNode(NodeType type, Loc loc = Loc());

    /**
     * Destructor
     */
    virtual ~ParseNode();

    /**
     * Get the type of the parse node
     * @note The type of a parse node cannot be changed
     * @return The parse node type
     */
    NodeType getType() const;

    /**
     * Get the children of the parse node
     * @return A constant reference to the child nodes
     */
    virtual std::vector<ParseNode *> children() const = 0;

    /**
     * Accept function for parse tree visitors
     */
    void accept(ParseTreeVisitor *visitor);

    // Location of the parse node
    Loc loc;

protected:

    // Type of the parse node
    NodeType type;

};

#endif