// host.cpp
#include "ball.h"

#include "Pieces/DataStream"

#include "Pieces/Debug"

using namespace pcs;

Ball::Ball(objectid_t objectId)
: GameObject(objectId)
, m_posX(0.0)
, m_posZ(0.0)
, m_angle(1.0127623)
, m_speed(10.0)
{
}

void Ball::encode(DataStream& ds) const
{
    ds << m_posX << m_posZ;
}

void Ball::decode(DataStream& ds)
{
    ds >> m_posX >> m_posZ;
}


void Ball::setPositionX(double pos)
{
    m_posX = pos;
}

void Ball::setPositionZ(double pos)
{
    m_posZ = pos;
}

void Ball::addRelativeX(double xOffset)
{
    m_posX += xOffset;
}

void Ball::addRelativeZ(double zOffset)
{
    m_posZ += zOffset;
}

double Ball::getPositionX()
{
    return m_posX;
}

double Ball::getPositionZ()
{
    return m_posZ;
}
