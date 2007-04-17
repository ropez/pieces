#if !defined PLAYER_HOST_CALLBACK_H
#define PLAYER_HOST_CALLBACK_H

#include "player.h"
#include "Pieces/GameObjectAction"

class PlayerHostCallback : public pcs::GameObjectAction
{
public:
    PlayerHostCallback(Player* player);

    virtual void operator()(pcs::framenum_t);

private:
    Player* m_player;
};

#endif // PLAYER_HOST_CALLBACK_H
