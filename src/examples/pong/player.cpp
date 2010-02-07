#include "player.h"
#include "Pieces/DataStream"

#include "Pieces/Debug"

namespace pong
{

Player::Player(pcs::objectid_t objectId)
: GameObject(objectId)
, m_peerAddress()
, m_location(Player::LEFT)
, m_movingState(Player::STATE_STOPPED)
, m_score(0)
, m_posX(0.0)
, m_posZ(0.0)
{
}

void Player::encode(pcs::DataStream& ds) const
{
    ds << m_posX << m_posZ << m_score;
}

void Player::decode(pcs::DataStream& ds)
{
    ds >> m_posX >> m_posZ >> m_score;
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

void Player::setLocation(Player::Location location)
{
    m_location = location;
}

Player::Location Player::getLocation() const
{
    return m_location;
}

void Player::increaseScore()
{
    ++m_score;
}

int Player::getScore() const
{
    return m_score;
}

}
