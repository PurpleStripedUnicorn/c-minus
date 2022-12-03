
#include "base.h"

ListNode::~ListNode() {
    for (ParseNode *child : childNodes)
        delete child;
}

const std::vector<ParseNode *> &ListNode::children() const {
    return childNodes;
}

UnaryNode::~UnaryNode() {
    delete child;
}

const std::vector<ParseNode *> &UnaryNode::children() const {
    return {child};
}

BinaryNode::~BinaryNode() {
    delete leftChild;
    delete rightChild;
}

const std::vector<ParseNode *> &BinaryNode::children() const {
    return {leftChild, rightChild};
}

BasicNode::BasicNode(NodeType type, std::string content, Loc loc) :
ParseNode(type, loc), content(content) { }

BasicNode::~BasicNode() { }

const std::vector<ParseNode *> &BasicNode::children() const {
    return {};
}

EmptyNode::~EmptyNode() { }

EmptyNode::EmptyNode(Loc loc) : ParseNode(NODE_EMPTY, loc) { }

const std::vector<ParseNode *> &EmptyNode::children() const {
    return {};
}