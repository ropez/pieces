#if !defined PLAYER_HOST_CALLBACK_H
#define PLAYER_HOST_CALLBACK_H

#include "Pieces/GameObjectAction"

#include "player.h"
#include "pong_defines.h"

#include "Pieces/ReferencePointer"
#include "timer.h"

class PlayerHostCallback : public pcs::GameObjectAction
{
public:
    PlayerHostCallback(pcs::ReferencePointer<Player> player, GameState* gameState);

    virtual void operator()(pcs::framenum_t);

private:
    pcs::ReferencePointer<Player> m_player;
    GameState* m_gameState;
    Timer_t m_lastTick;
};

#endif // PLAYER_HOST_CALLBACK_H
