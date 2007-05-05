#include "ball.h"

#include "config.h"

#include "Pieces/DataStream"

#include "Pieces/Debug"

Ball::Ball(pcs::objectid_t objectId)
: GameObject(objectId)
, m_posX(0.0)
, m_posZ(0.0)
, m_angle(1.0127623)
, m_speed(cfg::ballVelocity)
{
}

void Ball::encode(pcs::DataStream& ds) const
{
    ds << m_posX << m_posZ;
}

void Ball::decode(pcs::DataStream& ds)
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

double Ball::getPositionX() const
{
    return m_posX;
}

double Ball::getPositionZ() const
{
    return m_posZ;
}
