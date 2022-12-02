
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
     * @param filename The name of the file to output to
     * @param tokens The list of tokens
     */
    void lexer(std::string filename, const std::vector<Token> &tokens) const;
   
private:

};

#endif