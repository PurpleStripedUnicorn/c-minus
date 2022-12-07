
#ifndef FILE_SIZES
#define FILE_SIZES

/**
 * A general enum to indicate a data size
 * (in powers of two)
 * @note The enum value corresponds with the amount of bytes the size type would
 * take up in memory
 */
enum DataSize {
    SIZE_EMPTY = 0,
    SIZE_BYTE = 1,
    SIZE_WORD = 2,
    SIZE_DOUBLE = 4,
    SIZE_QUAD = 8,
};

#endif