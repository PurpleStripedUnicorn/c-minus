
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
     * @return A constant reference to the current token
     */
    const Token &cur() const;

    /**
     * Move to the next token
     */
    void next();

    /**
     * Get the location of the current token being read
     * @return The location as a Loc object
     */
    Loc getLoc() const;

    /**
     * Check if we are reading past the end of the lexer output
     * @return A boolean which indicates if we are reading past the end
     */
    bool atEnd() const;

    /**
     * Indicates wether the current token has the given type
     * @param type The type of the token to match
     * @return A boolean indicating if the current token type is the same
     */
    bool accept(TokenType type) const;

    /**
     * Expect a token of a certain type
     * @post If the expect type is not matched, the compiler exits
     */
    void expect(TokenType type) const;

    /**
     * Parse a program
     * @return The generated parse (sub)tree
     */
    ParseNode *readProgram();

    /**
     * Parse a function
     * @return The generated parse (sub)tree
     */
    ParseNode *readFunc();

    /**
     * Parse a code "statement", which can be both a single "line", or a scope
     * if '{' is read
     * @return The generated parse (sub)tree
     */
    ParseNode *readStmt();

    /**
     * Parse a scope
     * @return The generated parse (sub)tree
     */
    ParseNode *readScope();

    /**
     * Parse a print statement
     * @return The generated parse (sub)tree
     */
    ParseNode *readPrint();

    /**
     * Prase a single number
     * @return The generated parse (sub)tree
     */
    ParseNode *readNum();

    // The lexer component
    Lexer &lexer;
    // The currently read token
    Token curToken;
    // Pointer to the generated parse tree
    ParseNode *tree;

};

#endif