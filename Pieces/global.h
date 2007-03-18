
#ifndef PIECES_GLOBAL_H
#define PIECES_GLOBAL_H


namespace Pieces
{

// NOTE: We could also use Universally unique identifiers (e.g. 550e8400-e29b-41d4-a716-446655440000). They take 16 bytes, I have the code we need. (Robin)
typedef unsigned long objectid_t;

// NOTE: Using 32-bit frame number is enough for about 118 weeks, with 60 frames per second. Enough?
typedef unsigned long framenum_t;

} // namespace Pieces

#endif // PIECES_GLOBAL_H
