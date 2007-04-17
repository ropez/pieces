#if !defined BALLPEERCALLBACK_H
#define BALLPEERCALLBACK_H

#include "ball.h"

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"
#include "ballosg.h"

class BallPeerCallback : public pcs::GameObjectAction
{
public:
    BallPeerCallback(Ball* ball, osg::ref_ptr<BallOSG> ballOSG);

    virtual void operator()(pcs::framenum_t);

private:
    Ball* m_ball;
    osg::ref_ptr<BallOSG> m_ballOSG;
};

#endif // BALLPEERCALLBACK_H
