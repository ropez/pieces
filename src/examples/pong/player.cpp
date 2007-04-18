// host.cpp
#include "player.h"
#include "Pieces/DataStream"

#include "Pieces/Debug"

using namespace pcs;

Player::Player(objectid_t objectId, int posX)
: GameObject(objectId)
, m_movingState(Player::STATE_STOPPED)
, m_posX(posX)
, m_posZ(0.0)
{
}

void Player::encode(DataStream& ds) const
{
    ds << m_posZ;
}

void Player::setMovingState(Player::MovingState state)
{
    m_movingState = state;
}

Player::MovingState Player::getMovingState()
{
    return m_movingState;
}
