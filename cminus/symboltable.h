
#ifndef FILE_SYMBOLTABLE
#define FILE_SYMBOLTABLE

#include "util/loc.h"
#include "util/types.h"
#include <string>
#include <vector>

class Debugger;

/**
 * A symbol in the symbol table, containing return type and definition location
 */
struct Symbol {
    std::string name;
    ReturnType type;
    Loc defineLoc;
};

/**
 * A generic symbol table
 * Contains a list of symbols that can be referenced
 */
class SymbolTable {

public:

    /**
     * Constructor
     * @param debug The debugger
     */
    SymbolTable(Debugger &debug);

    /**
     * Destructor
     */
    ~SymbolTable();

    /**
     * Get the number of symbols
     * @return The number of symbols registered in the symbol table
     */
    size_t size() const;

    /**
     * Get a certain symbol from the symbol
     * @param index The index of the symbol
     * @return A constant reference to the symbol
     */
    const Symbol &operator[](size_t index) const;

    /**
     * Add a symbol to the symbol table, and get the new ID
     * @param symbol The symbol to add
     * @return The unique ID that is assigned to this symbol
     */
    size_t push(const Symbol &symbol);

private:

    // The list of defined symbols, the index in the list indicates the unique
    // ID that is assigned to this symbol
    std::vector<Symbol> symbols;

};

#endif