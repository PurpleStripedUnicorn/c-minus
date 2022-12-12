
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

IfNode::IfNode(bool hasElse, Loc loc) : TernaryNode(NODE_IF, loc) { }

WhileNode::WhileNode(Loc loc) : BinaryNode(NODE_WHILE, loc) { }