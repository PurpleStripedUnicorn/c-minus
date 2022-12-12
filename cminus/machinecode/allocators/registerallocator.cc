
#include "machinecode/reg.h"
#include "registerallocator.h"
#include <iostream>

RegisterAllocator::RegisterAllocator() : freeRegisters({REG_RBX,
REG_RCX, REG_RDX, REG_RSI, REG_RDI, REG_R8, REG_R9, REG_R10, REG_R11, REG_R12,
REG_R13, REG_R14, REG_R15}) { }

RegisterAllocator::~RegisterAllocator() { }

MCRegister RegisterAllocator::getRegister(long long var) {
    auto res = usedRegisters.find(var);
    if (res == usedRegisters.end()) {
        if (freeRegisters.size() == 0) {
            std::cerr << "Could not assign any more registers." << std::endl;
            exit(1);
        }
        MCRegister out = *freeRegisters.begin();
        usedRegisters[var] = out;
        freeRegisters.erase(out);
    }
    return usedRegisters[var];
}