
#include "parsenode.h"
#include "util/loc.h"
#include "visitor.h"

ParseNode::ParseNode(NodeType type, Loc loc) : loc(loc), type(type) {

}

ParseNode::~ParseNode() {

}

NodeType ParseNode::getType() const {
    return type;
}

void ParseNode::accept(ParseTreeVisitor *visitor) {
    visitor->visit(this);
}