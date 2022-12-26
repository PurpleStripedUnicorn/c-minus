
#include "debugger/debugger.h"
#include "symboltable.h"

Symbol::Symbol(std::string name, ReturnType type, Loc defineLoc) : name(name),
type(type), defineLoc(defineLoc) { }

SymbolTable::SymbolTable(Debugger &debug) : debug(debug) { }

SymbolTable::~SymbolTable() { }

size_t SymbolTable::size() const {
    return symbols.size();
}

const Symbol &SymbolTable::operator[](size_t index) const {
    return symbols[index];
}

size_t SymbolTable::push(const Symbol &symbol) {
    symbols.push_back(symbol);
    return symbols.size() - 1;
}