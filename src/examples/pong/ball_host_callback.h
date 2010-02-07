#if !defined BALLUPDATECALLBACK_H
#define BALLUPDATECALLBACK_H

#include "ball.h"

#include "Pieces/Host"
#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

#include "pong_defines.h"

#include "timer.h"

namespace pong
{

class BallUpdateCallback : public pcs::GameObjectAction
{
public:
    BallUpdateCallback(pcs::Host* host, Ball* ball, GameState* gameState, PlayerList_t* playerList);

    virtual void operator()(pcs::framenum_t);



private:
    Timer_t m_lastTick;
    GameState* m_gameState;
    pcs::Host* m_host;
    Ball* m_ball;
    PlayerList_t* m_playerList;
    bool m_wallHitRight;
    bool m_wallHitLeft;
};

}

#endif //BALLUPDATECALLBACK_H
