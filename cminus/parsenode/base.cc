
#include "base.h"

ListNode::~ListNode() {
    for (ParseNode *child : childNodes)
        delete child;
}

std::vector<ParseNode *> ListNode::children() const {
    return childNodes;
}

UnaryNode::~UnaryNode() {
    delete child;
}

std::vector<ParseNode *> UnaryNode::children() const {
    return {child};
}

BinaryNode::~BinaryNode() {
    delete leftChild;
    delete rightChild;
}

std::vector<ParseNode *> BinaryNode::children() const {
    return {leftChild, rightChild};
}

TernaryNode::~TernaryNode() {
    delete leftChild;
    delete middleChild;
    delete rightChild;
}

std::vector<ParseNode *> TernaryNode::children() const {
    return {leftChild, middleChild, rightChild};
}

BasicNode::BasicNode(NodeType type, std::string content, Loc loc) :
ParseNode(type, loc), content(content) { }

BasicNode::~BasicNode() { }

std::vector<ParseNode *> BasicNode::children() const {
    return {};
}

EmptyNode::~EmptyNode() { }

EmptyNode::EmptyNode(Loc loc) : ParseNode(NODE_EMPTY, loc) { }

std::vector<ParseNode *> EmptyNode::children() const {
    return {};
}