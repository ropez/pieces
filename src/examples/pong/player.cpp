// host.cpp
#include "player.h"
#include "Pieces/DataStream"

#include "Pieces/Debug"

using namespace Pieces;

Player::Player(objectid_t objectId, int posX)
: GameObject(objectId)
, m_posX(posX)
, m_posZ(0.0)
{
}

void Player::encode(DataStream& ds) const
{
    ds << m_posZ;
}

