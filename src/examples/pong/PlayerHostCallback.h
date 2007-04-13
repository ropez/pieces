#if !defined PLAYERUPDATE_H
#define PLAYERUPDATE_H

#include "player.h"
#include "Pieces/GameObjectAction"

class PlayerUpdateCallback : public Pieces::GameObjectAction
{
public:
    PlayerUpdateCallback(Player* player);

    virtual void operator()(Pieces::framenum_t);

private:
    Player* m_player;
};

#endif // PLAYERUPDATE_H
