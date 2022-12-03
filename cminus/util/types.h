
#ifndef FILE_TYPES
#define FILE_TYPES

#include <string>

/**
 * Return types
 */
enum ReturnType {
    RT_VOID,
    RT_INT,
    RT_UINT,
    RT_INT8,
    RT_UINT8
};

/**
 * Convert a string to a return type
 * @note Throws an error and exits if type is inavlid
 */
ReturnType toReturnType(const std::string &txt);

#endif