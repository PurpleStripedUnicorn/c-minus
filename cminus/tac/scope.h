
#ifndef FILE_TAC_SCOPE
#define FILE_TAC_SCOPE

#include <vector>
#include <string>
#include <unordered_map>

class ScopeManager {

public:

    /**
     * Constructor
     */
    ScopeManager();

    /**
     * Destructor
     */
    ~ScopeManager();

    /**
     * Add a new (empty) scope to the top of the scope stack
     */
    void pushScope();

    /**
     * Remove the top scope from the scope stack
     * @note If the scope stack is empty, nothing happens
     */
    void popScope();

    /**
     * Find a variable on the scope stack, starts searching from the top
     * @param name The name of the variable
     * @param fullDepth Indicates if the full depth of the scope stack should be
     * searched, or just the top scope
     * @return The TAC variable index of the variable, or -1 if the variable was
     * not found
     */
    long long find(std::string name, bool fullDepth = true) const;

    /**
     * Add a variable to the current scope
     * @param name The name of the variable
     * @param tacName The TAC variable index of the variable
     * @warning Does not check if the variable was already defined in the
     * current scope!
     */
    void add(std::string name, long long tacName);

private:

    // Contains all variables in the current and parent scopes
    // Sends a variable name to its corresponding TAC variable index
    std::vector<std::unordered_map<std::string, long long>> scopeStack;

};

#endif