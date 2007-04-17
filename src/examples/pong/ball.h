#if !defined BALL_H
#define BALL_H

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

class Ball : public pcs::GameObject
{
public:
    Ball(pcs::objectid_t objectId);

    void encode(pcs::DataStream& ds) const;
    void decode(pcs::DataStream& ds);

    void setPositionZ(double pos);
    void setPositionX(double pos);

    void addRelativeX(double xOffset);
    void addRelativeZ(double zOffset);

    
    double getPositionZ();
    double getPositionX();

    void setAngle(double angle) {m_angle = angle;}
    double getAngle() { return m_angle;}
    double getVelocity() { return m_speed;}

private:
    double m_posX;
    double m_posZ;
    double m_angle;
    double m_speed;
};

#endif //BALL_H
