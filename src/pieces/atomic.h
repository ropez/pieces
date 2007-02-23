
#ifndef PIECES_ATOMIC_H
#define PIECES_ATOMIC_H

extern "C"
{

/**
 * Increments *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_increment(unsigned long *p);

/**
 * Decrements *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_decrement(unsigned long *p);

}

#endif // NUM_ATOMIC_H
