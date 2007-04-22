#if !defined BALLUPDATECALLBACK_H
#define BALLUPDATECALLBACK_H

#include "ball.h"

#include "Pieces/Host"
#include "Pieces/AutoPointer"
#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

#include "pong_defines.h"

class BallUpdateCallback : public pcs::GameObjectAction
{
public:
    BallUpdateCallback(pcs::AutoPointer<pcs::Host> host, Ball* ball, GameState* gameState, PlayerList_t* playerList);

    virtual void operator()(pcs::framenum_t);



private:
    GameState* m_gameState;
    pcs::AutoPointer<pcs::Host> m_host;
    Ball* m_ball;
    PlayerList_t* m_playerList;
    bool m_wallHitRight;
    bool m_wallHitLeft;
};

#endif //BALLUPDATECALLBACK_H
