#if !defined BALLUPDATECALLBACK_H
#define BALLUPDATECALLBACK_H

#include "ball.h"

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

#include "pong_defines.h"

class BallUpdateCallback : public pcs::GameObjectAction
{
public:
    BallUpdateCallback(Ball* ball, PlayerList_t* playerList);

    virtual void operator()(pcs::framenum_t);

private:
    Ball* m_ball;
    PlayerList_t* m_playerList;
};

#endif //BALLUPDATECALLBACK_H
