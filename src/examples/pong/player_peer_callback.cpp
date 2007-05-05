#include "PlayerPeerCallback.h"

#include "config.h"

#include "Pieces/Debug"

#include <iostream>

PlayerPeerCallback::PlayerPeerCallback(Player* player)
: pcs::GameObjectAction()
, m_player(player)
{
}

void PlayerPeerCallback::operator()(pcs::framenum_t frameNum)
{
    //m_player->setRelativeZ();
}
