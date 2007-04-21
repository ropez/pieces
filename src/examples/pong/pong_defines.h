#if !defined PONG_DEFINES_H
#define PONG_DEFINES_H

#include "Pieces/ReferencePointer"
#include "player.h"
#include <list>

// Host specific

typedef std::list<pcs::ReferencePointer<Player> > PlayerList_t;

enum ObjectTypes
{
    TYPE_BALL,
    TYPE_PLAYER,
};


// Common
enum MessageTypes
{
    MSG_GAME_EVENT_JOIN = 1000,
    MSG_UP_PRESSED,
    MSG_UP_RELEASED,
    MSG_DOWN_PRESSED,
    MSG_DOWN_RELEASED
};

enum ActionTypes
{
    ACTION_UPDATE,
    ACTION_DRAW
};

class GameState
{
public:
    GameState()
        : ballIsLostForPlayerLeft(false)
        , ballIsLostForPlayerRight(false)
    {
    }

    void init()
    {
        ballIsLostForPlayerLeft = false;
        ballIsLostForPlayerRight = false;
    }

    bool ballIsLostForPlayerLeft;
    bool ballIsLostForPlayerRight;

};

#endif //PONG_DEFINES_H
