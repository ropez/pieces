#if !defined BALLOSG_H
#define BALLOSG_H

#include <osg/MatrixTransform>
#include "ball.h"
#include "Pieces/ReferencePointer"

class BallOSG : public osg::MatrixTransform
{
public:
    BallOSG(pcs::ReferencePointer<Ball> ball);
    ~BallOSG();

    void addRelativeZ(double zOffset);
    double getPositionX();
    void setPositionX(double xPos);
    double getPositionZ();
    void setPositionZ(double zPos);


    void setVelocity(double velocity);
    void setAngle(double angle);
    double getAngle();
    void update();

private:
    osg::ref_ptr<osg::Geode> createGeode();
    
    pcs::ReferencePointer<Ball> m_ball;
    double m_xPos;
    double m_zPos;
    double m_velocity;
    double m_angle;
    
};

#endif // BALLOSG_H