
#ifndef FILE_PARSENODE_BASE
#define FILE_PARSENODE_BASE

#include "parsenode.h"
#include <string>

/**
 * List node
 * Used for example for statement lists, base program node, etc.
 */
class ListNode : public ParseNode {

public:

    using ParseNode::ParseNode;
    virtual ~ListNode();
    virtual std::vector<ParseNode *> children() const override;

    // Children of the list
    std::vector<ParseNode *> childNodes;

};

/**
 * Unary node
 * Used for example for unary minus
 */
class UnaryNode : public ParseNode {

public:

    using ParseNode::ParseNode;
    virtual ~UnaryNode();
    virtual std::vector<ParseNode *> children() const override;

    // The child of the node
    ParseNode *child;

};

/**
 * Binary node
 * Used for example for arithmatic operations, assignments, etc.
 */
class BinaryNode : public ParseNode {

public:

    using ParseNode::ParseNode;
    virtual ~BinaryNode();
    virtual std::vector<ParseNode *> children() const override;
    
    // The children of the node
    ParseNode *leftChild, *rightChild;

};

/**
 * Basic node type, a node without children that is not empty
 * This could for example be a number or a string
 */
class BasicNode : public ParseNode {

public:

    BasicNode(NodeType type, std::string content, Loc loc = Loc());
    virtual ~BasicNode();
    virtual std::vector<ParseNode *> children() const override;

    // Content of the node, could be a number, a string, etc.
    std::string content;

};

/**
 * Empty parse node
 */
class EmptyNode : public ParseNode {

public:

    EmptyNode(Loc loc = Loc());
    virtual ~EmptyNode();
    virtual std::vector<ParseNode *> children() const override;

};

#endif