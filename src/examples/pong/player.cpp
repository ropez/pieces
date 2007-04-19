#include "player.h"
#include "Pieces/DataStream"

#include "Pieces/Debug"

using namespace pcs;

Player::Player(objectid_t objectId, int posX)
: GameObject(objectId)
, m_peerAddress()
, m_movingState(Player::STATE_STOPPED)
, m_posX(posX)
, m_posZ(0.0)
{
}

void Player::encode(DataStream& ds) const
{
    ds << m_posZ;
}

void Player::decode(DataStream& ds)
{
    ds >> m_posZ;
}

const pcs::SocketAddress& Player::getPeerAddress()
{
    return m_peerAddress;
}

void Player::setPeerAddress(const pcs::SocketAddress& peerAddress)
{
    m_peerAddress = peerAddress;
}

void Player::setMovingState(Player::MovingState state)
{
    m_movingState = state;
}

Player::MovingState Player::getMovingState()
{
    return m_movingState;
}

void Player::addRelativeZ(double zOffset)
{
    m_posZ += zOffset;
}

void Player::setPositionZ(double posZ)
{
    m_posZ = posZ;
}

double Player::getPositionZ() const
{
    return m_posZ;
}

double Player::getPositionX() const
{
    return m_posX;
}
