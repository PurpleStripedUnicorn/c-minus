
#ifndef FILE_REGISTERALLOCATOR
#define FILE_REGISTERALLOCATOR

#include "debugger/debugger.h"
#include "machinecode/reg.h"
#include <set>
#include <unordered_map>

class RegisterAllocator {

public:

    /**
     * Constructor
     * @param debug The debugger
     */
    RegisterAllocator(Debugger &debug);

    /**
     * Destructor
     */
    ~RegisterAllocator();

    /**
     * Retrieve a register for a given TAC variable ID
     * @param var The TAC variable ID
     * @return The register belonging to the TAC variable
     * @note Allocates a new register if necessary, or just returns an already
     * assigned register
     * @warning Throws an error if there are no free registers left and a new
     * register needs to be assigned
     */
    MCRegister getRegister(long long var);

private:

    // All registers that are still free to be used
    std::set<MCRegister> freeRegisters;
    // Allocated registers, where the TAC variable IDs are mapped to register
    // numbers
    std::unordered_map<long long, MCRegister> usedRegisters;
    // The debugger
    Debugger &debug;

};

#endif