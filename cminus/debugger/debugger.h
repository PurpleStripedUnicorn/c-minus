
#ifndef FILE_DEBUG
#define FILE_DEBUG

#include <string>
#include <vector>

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
     * Output a list of tokens to a debug file
     * @param os Output stream to put the output in
     * @param tokens The list of tokens
     */
    void lexer(std::ostream &os, const std::vector<Token> &tokens) const;

    /**
     * Output a textual representation of the parse tree
     * @param os Output stream to put the output in
     * @param node The base node of the parse tree
     * @param depth The current depth of the parse tree, default 0
     */
    void parser(std::ostream &os, const ParseNode *node, size_t depth = 0)
    const;
   
private:

};

#endif