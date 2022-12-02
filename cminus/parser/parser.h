
#ifndef FILE_PARSER
#define FILE_PARSER

#include "lexer/token.h"

class Lexer;
class ParseNode;

/**
 * Converts tokens into a parse tree
 */
class Parser {

public:

    /**
     * Constructor
     * @param lexer The lexer component
     */
    Parser(Lexer &lexer);

    /**
     * Destructor
     */
    ~Parser();

    /**
     * Parse the output of the lexer
     */
    void parse();

    /**
     * Get a pointer to the parse tree
     */
    ParseNode *getTree() const;

private:

    /**
     * Get the currently read token
     */
    Token cur() const;

    /**
     * Move to the next token
     */
    void next();

    /**
     * Check if we are reading past the end of the lexer output
     * @return A boolean which indicates if we are reading past the end
     */
    bool atEnd() const;

    /**
     * Parse a program
     * @return The generated parse (sub)tree
     */
    ParseNode *readProgram();

    /**
     * Parse a function
     * @return The generated parse (sub)tree
     */
    ParseNode *readFunction();

    // The lexer component
    Lexer &lexer;
    // The currently read token
    Token curToken;
    // Pointer to the generated parse tree
    ParseNode *tree;

};

#endif