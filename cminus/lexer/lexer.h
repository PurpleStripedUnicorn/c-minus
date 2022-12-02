
#ifndef FILE_LEXER
#define FILE_LEXER

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
    */
   Lexer(const std::string &txt);

   /**
    * Destructor
   */
  ~Lexer();

    /**
     * Read in a token and return it, if we have reached the end of the input
     * text, a token with type TOK_END will be returned
     * @return The read token
     * @post Position in the text is updated
    */
   Token get();

   /**
    * Check we have reached the end of the input text
    * @return A boolean indicating if the end of the text is reached
   */
  bool atEnd() const;

private:

    // The text the compiler reads in from a file
    const std::string &txt;
    // Record the current position in the input text
    size_t pos;

};

#endif