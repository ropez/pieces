// Peer Callback

#include "BallPeerCallback.h"
#include <iostream>
#include "Pieces/Debug"


BallPeerCallback::BallPeerCallback(Ball* ball, osg::ref_ptr<BallOSG> ballOSG)
: Pieces::GameObjectAction()
, m_ball(ball)
, m_ballOSG(ballOSG)
{
}

void BallPeerCallback::operator()(Pieces::framenum_t frameNum)
{
    if(m_ballOSG.valid())
    {
        m_ballOSG->setPositionX(m_ball->getPositionX());
        m_ballOSG->setPositionZ(m_ball->getPositionZ());
    }
}
