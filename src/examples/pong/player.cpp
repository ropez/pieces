#include "player.h"
#include "Pieces/DataStream"

#include "Pieces/Debug"

using namespace pcs;

Player::Player(objectid_t objectId)
: GameObject(objectId)
, m_peerAddress()
, m_movingState(Player::STATE_STOPPED)
, m_posX(0.0)
, m_posZ(0.0)
{
}

void Player::encode(DataStream& ds) const
{
    ds << m_posX << m_posZ;
}

void Player::decode(DataStream& ds)
{
    ds >> m_posX >> m_posZ;
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

Player::MovingState Player::getMovingState() const
{
    return m_movingState;
}

void Player::setDownPressed(bool pressed)
{
    m_downIsPressed = pressed;
}
bool Player::isDownPressed() const
{
    return m_downIsPressed;
}

void Player::setUpPressed(bool pressed)
{
    m_upIsPressed = pressed;
}
bool Player::isUpPressed() const
{
    return m_upIsPressed;
}


void Player::addRelativeZ(double offset)
{
    m_posZ += offset;
}

void Player::setPositionZ(double pos)
{
    m_posZ = pos;
}

void Player::setPositionX(double pos)
{
    m_posX = pos;
}

double Player::getPositionZ() const
{
    return m_posZ;
}

double Player::getPositionX() const
{
    return m_posX;
}
