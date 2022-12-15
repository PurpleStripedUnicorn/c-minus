
#include "types.h"
#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<std::string, ReturnType> returnTypeMap = {
    { "void", RT_VOID },
    { "bool", RT_BOOL },
    { "int", RT_INT32 },
    { "unsigned", RT_UINT32 },
    { "int8_t", RT_INT8 },
    { "uint8_t", RT_UINT8 },
};

ReturnType toReturnType(const std::string &txt) {
    if (returnTypeMap.find(txt) != returnTypeMap.end())
        return returnTypeMap.find(txt)->second;
    std::cerr << "Searching for an invalid return type '" << txt << "'."
    << std::endl;
    exit(1);
}