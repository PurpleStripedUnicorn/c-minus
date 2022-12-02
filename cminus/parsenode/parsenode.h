
#ifndef FILE_PARSENODE
#define FILE_PARSENODE

#include "util/loc.h"

enum NodeType {
    NODE_ERR,
    // Base nodes
    NODE_PROGRAM,
    NODE_SCOPE,
    NODE_FUNC,
    NODE_STMT,
    // Arithmatic
    NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV, NODE_MOD
};

/**
 * Abstract base class for parse nodes
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
     * @return The parse node type
     */
    NodeType getType() const;

private:

    // Type of the parse node
    NodeType type;
    // Location of the parse node
    Loc loc;

};

#endif