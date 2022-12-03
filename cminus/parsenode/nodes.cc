
#include "nodes.h"

ProgramNode::ProgramNode(Loc loc) : ListNode(NODE_PROGRAM, loc) { }

FuncNode::FuncNode(ReturnType returnType, Loc loc) :
UnaryNode(NODE_FUNC, loc), returnType(returnType) { }

ScopeNode::ScopeNode(Loc loc) : ListNode(NODE_SCOPE, loc) { }

PrintNode::PrintNode(Loc loc) : UnaryNode(NODE_PRINT, loc) { }

NumberNode::NumberNode(std::string content, Loc loc) : BasicNode(NODE_NUM,
content, loc) { }