
#include "debugger/debugger.h"
#include "symboltable.h"

SymbolTable::SymbolTable(Debugger &debug) { }

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