
#include "parsenode.h"
#include "util/loc.h"

ParseNode::ParseNode(NodeType type, Loc loc) : type(type), loc(loc) {

}

ParseNode::~ParseNode() {

}

NodeType ParseNode::getType() const {
    return type;
}