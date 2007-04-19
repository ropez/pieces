#include "PlayerHostCallback.h"

#include "config.h"

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
            m_player->addRelativeZ(cfg::playerVelocity);
            if(m_player->getPositionZ() + cfg::playerHeightHalf > cfg::frameInsideTop)
            {
                m_player->setPositionZ(cfg::frameInsideTop - cfg::playerHeightHalf);
            }
        }
        break;
    case Player::STATE_DOWN:
        {
            m_player->addRelativeZ(-cfg::playerVelocity);
            if(m_player->getPositionZ() - cfg::playerHeightHalf < cfg::frameInsideBottom)
            {
                m_player->setPositionZ(cfg::frameInsideBottom + cfg::playerHeightHalf);
            }
        }
        break;
    default:
        break;
    }
}
