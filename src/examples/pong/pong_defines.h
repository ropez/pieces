#if !defined PONG_DEFINES_H
#define PONG_DEFINES_H


// Host specific

enum ObjectTypes
{
    TYPE_BALL,
    TYPE_PLAYER_1,
    TYPE_PLAYER_2
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



#endif //PONG_DEFINES_H
