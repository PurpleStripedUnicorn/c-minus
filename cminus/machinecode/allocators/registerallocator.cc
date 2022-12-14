
#include "machinecode/reg.h"
#include "registerallocator.h"
#include <iostream>

RegisterAllocator::RegisterAllocator(Debugger &debug) : freeRegisters({REG_RBX,
REG_RCX, REG_RDX, REG_RSI, REG_RDI, REG_R8, REG_R9, REG_R10, REG_R11, REG_R12,
REG_R13, REG_R14, REG_R15}), debug(debug) { }

RegisterAllocator::~RegisterAllocator() { }

MCRegister RegisterAllocator::getRegister(long long var) {
    auto res = usedRegisters.find(var);
    if (res == usedRegisters.end()) {
        if (freeRegisters.size() == 0)
            debug.logger.error("Could not assign any more registers");
        MCRegister out = *freeRegisters.begin();
        usedRegisters[var] = out;
        freeRegisters.erase(out);
    }
    return usedRegisters[var];
}