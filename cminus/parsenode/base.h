
#ifndef FILE_PARSENODE_BASE
#define FILE_PARSENODE_BASE

#include "parsenode.h"
#include <vector>
#include <string>

class CodeBlockNode;
class FuncNode;
class ProgramNode;
class StmtNode;

/**
 * Program parse node
 */
class ProgramNode : ParseNode {

public:

    ProgramNode();
    virtual ~ProgramNode();

private:

    // Functions contained in the program
    std::vector<FuncNode *> funcs;

};

/**
 * Function parse node
 */
class FuncNode : ParseNode {

public:

    FuncNode();
    virtual ~FuncNode();

private:
    // Code block that contains the contents of the function
    CodeBlockNode *child;

};

#endif