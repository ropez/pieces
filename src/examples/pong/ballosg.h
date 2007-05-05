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

    void update();

private:
    osg::ref_ptr<osg::Geode> createGeode();
    
    pcs::ReferencePointer<Ball> m_ball;
    
};

#endif // BALLOSG_H
