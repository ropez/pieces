#if !defined PLAYERPEERCALLBACK_H
#define PLAYERPEERCALLBACK_H

#include "Pieces/GameObjectAction"

#include "player.h"

#include "Pieces/GameObject"

class PlayerPeerCallback : public pcs::GameObjectAction
{
public:
    PlayerPeerCallback(Player* player);

    virtual void operator()(pcs::framenum_t);

private:
    Player* m_player;
};

#endif // PLAYERPEERCALLBACK_H
