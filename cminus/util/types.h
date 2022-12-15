
#ifndef FILE_TYPES
#define FILE_TYPES

#include <string>

/**
 * Return types
 */
enum ReturnType {
    RT_VOID,
    RT_BOOL,
    RT_INT8,
    RT_INT16,
    RT_INT32,
    RT_INT64,
    RT_UINT8,
    RT_UINT16,
    RT_UINT32,
    RT_UINT64,
};

/**
 * Convert a string to a return type
 * @note Throws an error and exits if type is inavlid
 */
ReturnType toReturnType(const std::string &txt);

#endif