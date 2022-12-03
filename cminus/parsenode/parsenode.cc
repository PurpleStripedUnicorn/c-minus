
#include "parsenode.h"
#include "util/loc.h"

ParseNode::ParseNode(NodeType type, Loc loc) : loc(loc), type(type) {

}

ParseNode::~ParseNode() {

}

NodeType ParseNode::getType() const {
    return type;
}