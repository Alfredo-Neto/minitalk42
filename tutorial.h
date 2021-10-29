#ifndef TUTORIAL_H
# define TUTORIAL_H

typedef enum e_flags
{
    STRING_LIMIT_CHARS = 1 << 0,  // 1 * 2^0 = 1 = 0b01
    STRING_HAS_LETTER_N = 1 << 1, // 1 * 2^1 = 2 = 0b10
    STRING_HAS_LETTER_O = 1 << 2, // 1 * 2^2 = 4 = 0b100
    STRING_HAS_LETTER_P = 1 << 3  // 1 * 2^3 = 8 = 0b1000
}t_flags;

#endif