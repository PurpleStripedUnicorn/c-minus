
#include "parsenode.h"
#include "util/loc.h"

ParseNode::ParseNode(NodeType type, Loc loc) : type(type), loc(loc) {

}

ParseNode::~ParseNode() {

}

NodeType ParseNode::getType() const {
    return type;
}

const std::vector<ParseNode *> &ParseNode::children() const {
    return childNodes;
}

ParseNode *ParseNode::getLeftChild() const {
    if (childNodes.size() < 1)
        return nullptr;
    return childNodes[0];
}

ParseNode *ParseNode::getRightChild() const {
    if (childNodes.size() < 2)
        return nullptr;
    return childNodes[1];
}