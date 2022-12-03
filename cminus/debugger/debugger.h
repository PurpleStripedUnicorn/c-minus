
#ifndef FILE_DEBUG
#define FILE_DEBUG

#include <string>
#include <vector>

class ParseNode;
struct Token;

class Debugger {

public:

    /**
     * Constructor
     */
    Debugger();

    /**
     * Destructor
     */
    ~Debugger();

    /**
     * Enable the debugger
     */
    void enable();

    /**
     * Output the list of generated tokens to a debug file
     * @param os Output stream to put the output in
     */
    void lexer(std::ostream &os) const;

    /**
     * Output a textual representation of the parse tree
     * @param os Output stream to put the output in
     */
    void parser(std::ostream &os) const;
   
    // List of generated tokens
    std::vector<Token> tokens;
    // Root of the generated parse tree, not manager by this object
    ParseNode *tree;

private:

    /**
     * Output a textual representation of the parse (sub)tree
     * @param os Output stream to put the output in
     * @param node The current node of the parse tree
     * @param depth The current depth of the parse tree
     */
    void parser(std::ostream &os, const ParseNode *node, size_t depth) const;

    // Indicates if the debugger is enabled
    bool enabled;

};

#endif