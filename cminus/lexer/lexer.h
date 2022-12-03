
#ifndef FILE_LEXER
#define FILE_LEXER

#include "debugger/debugger.h"
#include "token.h"
#include <string>

/**
 * The lexer reads in the characters for the main input stream and converts them
 * to tokens
 */
class Lexer {

public:

    /**
     * Constructor
     * @param txt The text that needs to be compiled
     * @param debug The debugger
     */
    Lexer(const std::string &txt, Debugger &debug);

    /**
     * Destructor
     */
    ~Lexer();

    /**
     * Read in a token and return it, also informs debugger
     * @return The read token
     * @note The "getToken" function is executed in this function
     */
    Token get();

    /**
     * Check we have reached the end of the input text
     * @return A boolean indicating if the end of the text is reached
     */
    bool atEnd() const;

private:

    /**
     * Read in a token and return it, if we have reached the end of the input
     * text, a token with type TOK_END will be returned
     * @return The read token
     * @post Position in the text is updated
     */
    Token getToken();

    /**
     * The current token being read, if the lexer is at the end of the text this
     * returns a newline character
     * @return The character at the current position
     */
    char cur() const;

    /**
     * Move to the next token in the input stream
     * @post position is incremented
     */
    void next();

    /**
     * Read in an identifier
     * @return The identifier that was read as a token
     * @post position is updated
     */
    Token readID();

    /**
     * Read in a number
     * @return The number that was read as a token
     * @post position is updated
     */
    Token readNum();

    // The text the compiler reads in from a file
    const std::string &txt;
    // Record the current position in the input text
    size_t pos;
    // Current location of reading (line and column)
    Loc loc;
    // Last saved location, which is only updated to the current location at the
    // start of get()
    Loc savedLoc;
    // The debugger
    Debugger &debug;

};

#endif