
#ifndef FILE_NODES
#define FILE_NODES

#include "base.h"
#include "util/types.h"
#include <string>

/**
 * Base node of the parse tree
 */
class ProgramNode : public ListNode {
public:
    ProgramNode(Loc loc = Loc());
};

/**
 * Function definition
 * @note The child of the function is the main scope of the function
 */
class FuncNode : public UnaryNode {
public:
    FuncNode(Loc loc = Loc(), ReturnType returnType = RT_VOID);
    // Return type of the function
    ReturnType returnType;
    // Name of the function
    std::string name;
};

/**
 * Nested scope
 */
class ScopeNode : public ListNode {
public:
    ScopeNode(Loc loc = Loc());
};

/**
 * Print statement
 */
class PrintNode : public UnaryNode {
public:
    PrintNode(Loc loc = Loc());
};

/**
 * Number parse node
 */
class NumberNode : public BasicNode {
public:
    NumberNode(std::string content, Loc loc = Loc());
};

/**
 * Identifier parse node
 */
class IdentifierNode : public BasicNode {
public:
    IdentifierNode(std::string content, Loc loc = Loc());
};

/**
 * Declaration parse node
 */
class DeclarationNode : public ListNode {
public:
    DeclarationNode(Loc loc = Loc(), ReturnType declareType = RT_VOID);
    // The type the variables are declared as
    ReturnType declareType;
};

/**
 * Assignment parse node
 */
class AssignNode : public BinaryNode {
public:
    AssignNode(Loc loc = Loc());
};

/**
 * Addition
 */
class AddNode : public BinaryNode {
public:
    AddNode(Loc loc = Loc());
};

/**
 * Subtraction
 */
class SubNode : public BinaryNode {
public:
    SubNode(Loc loc = Loc());
};

/**
 * Multiplication
 */
class MulNode : public BinaryNode {
public:
    MulNode(Loc loc = Loc());
};

/**
 * If-statements
 * First child is the condition, second is the "if" code and third is the "else"
 * code
 */
class IfNode : public TernaryNode {
public:
    IfNode(Loc loc = Loc());
    bool hasElse;
};

/**
 * While loops
 * First child is the condition, second is the looped code
 */
class WhileNode : public BinaryNode {
public:
    WhileNode(Loc loc = Loc());
};

/**
 * Equality comparison
 */
class EqNode : public BinaryNode {
public:
    EqNode(Loc loc = Loc());
};

/**
 * Non-equality comparison
 */
class NeqNode : public BinaryNode {
public:
    NeqNode(Loc loc = Loc());
};

/**
 * Less than comparison
 */
class LtNode : public BinaryNode {
public:
    LtNode(Loc loc = Loc());
};

/**
 * Less than or equal comparison
 */
class LteNode : public BinaryNode {
public:
    LteNode(Loc loc = Loc());
};

/**
 * Greater than comparison
 */
class GtNode : public BinaryNode {
public:
    GtNode(Loc loc = Loc());
};

/**
 * Greater than or equal comparison
 */
class GteNode : public BinaryNode {
public:
    GteNode(Loc loc = Loc());
};

#endif