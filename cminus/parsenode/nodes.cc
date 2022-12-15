
#include "nodes.h"

ProgramNode::ProgramNode(Loc loc) : ListNode(NODE_PROGRAM, loc) { }

FuncNode::FuncNode(Loc loc, ReturnType returnType) :
UnaryNode(NODE_FUNC, loc), returnType(returnType) { }

ScopeNode::ScopeNode(Loc loc) : ListNode(NODE_SCOPE, loc) { }

PrintNode::PrintNode(Loc loc) : UnaryNode(NODE_PRINT, loc) { }

NumberNode::NumberNode(std::string content, Loc loc) : BasicNode(NODE_NUM,
content, loc) { }

IdentifierNode::IdentifierNode(std::string content, Loc loc) :
BasicNode(NODE_IDENT, content, loc) { }

DeclarationNode::DeclarationNode(Loc loc, ReturnType declareType) :
ListNode(NODE_DECL, loc), declareType(declareType) { }

AssignNode::AssignNode(Loc loc) : BinaryNode(NODE_ASSIGN, loc) { }

AddNode::AddNode(Loc loc) : BinaryNode(NODE_ADD, loc) { }

SubNode::SubNode(Loc loc) : BinaryNode(NODE_SUB, loc) { }

MulNode::MulNode(Loc loc) : BinaryNode(NODE_MUL, loc) { }

IfNode::IfNode(Loc loc) : TernaryNode(NODE_IF, loc) { }

WhileNode::WhileNode(Loc loc) : BinaryNode(NODE_WHILE, loc) { }

EqNode::EqNode(Loc loc) : BinaryNode(NODE_EQ, loc) { }

NeqNode::NeqNode(Loc loc) : BinaryNode(NODE_NEQ, loc) { }

LtNode::LtNode(Loc loc) : BinaryNode(NODE_LT, loc) { }

LteNode::LteNode(Loc loc) : BinaryNode(NODE_LTE, loc) { }

GtNode::GtNode(Loc loc) : BinaryNode(NODE_GT, loc) { }

GteNode::GteNode(Loc loc) : BinaryNode(NODE_GTE, loc) { }