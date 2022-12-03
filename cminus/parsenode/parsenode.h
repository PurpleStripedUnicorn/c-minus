
#ifndef FILE_PARSENODE
#define FILE_PARSENODE

#include "util/loc.h"
#include <vector>

class ParseNode;

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
    NODE_STMT,
    // Basic nodes
    NODE_NUM,
    // Arithmatic
    NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV, NODE_MOD,
    // Print statements
    NODE_PRINT,
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
    virtual const std::vector<ParseNode *> &children() const = 0;

    // Location of the parse node
    Loc loc;

protected:

    // Type of the parse node
    NodeType type;

};

#endif