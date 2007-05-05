#include "player_host_callback.h"

#include "config.h"

#include "Pieces/DebugStream"

PlayerHostCallback::PlayerHostCallback(pcs::ReferencePointer<Player> player, GameState* gameState)
: pcs::GameObjectAction()
, m_gameState(gameState)
, m_player(player)
{
}

void PlayerHostCallback::operator()(pcs::framenum_t)
{

    if(m_player->getLocation() == Player::RIGHT && m_gameState->ballIsLostForPlayerLeft)
    {
        m_player->increaseScore();
        PINFO << "Score Player Right: " << m_player->getScore();
    }
    else if(m_player->getLocation() == Player::LEFT && m_gameState->ballIsLostForPlayerRight)
    {
        m_player->increaseScore();
        PINFO << "Score Player Left: " << m_player->getScore();
    }


    // 
    // Move player
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
