#include "PlayerHostCallback.h"

PlayerUpdateCallback::PlayerUpdateCallback(Player* player)
: pcs::GameObjectAction()
, m_player(player)
{
}

void PlayerUpdateCallback::operator()(pcs::framenum_t)
{
    // Collition detection
}
