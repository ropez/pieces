
#ifndef PIECES_ATOMIC_H
#define PIECES_ATOMIC_H

#include <cctype>

extern "C"
{

/**
 * Increments *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_increment(__uint32_t *p);

/**
 * Decrements *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_decrement(__uint32_t *p);

}

#endif // NUM_ATOMIC_H
