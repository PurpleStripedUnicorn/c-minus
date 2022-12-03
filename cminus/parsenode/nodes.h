
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

#endif