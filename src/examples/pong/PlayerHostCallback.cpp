#include "PlayerHostCallback.h"
#include "Pieces/DebugStream"

PlayerHostCallback::PlayerHostCallback(Player* player)
: pcs::GameObjectAction()
, m_player(player)
{
}

void PlayerHostCallback::operator()(pcs::framenum_t)
{
    switch(m_player->getMovingState())
    {
    case Player::STATE_UP:
        {
            PDEBUG << " Movin' up " << m_player->getObjectId();
            break;
        }
    case Player::STATE_DOWN:
        {
            PDEBUG << " Movin' down " << m_player->getObjectId();
            break;
        }
    default:
        {
            break;
        }
    }
}
