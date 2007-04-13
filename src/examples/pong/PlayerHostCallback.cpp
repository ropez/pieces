#include "PlayerHostCallback.h"

PlayerUpdateCallback::PlayerUpdateCallback(Player* player)
: Pieces::GameObjectAction()
, m_player(player)
{
}

void PlayerUpdateCallback::operator()(Pieces::framenum_t)
{
    // Collition detection
}
