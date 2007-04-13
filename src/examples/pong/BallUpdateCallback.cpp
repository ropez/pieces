// host.cpp

#include "BallUpdateCallback.h"

#include "Pieces/Debug"
#include <math.h>

const double frameOutsideLeft   = -640.0;
const double frameOutsideRight  =  640.0;
const double frameOutsideTop    =  512.0;
const double frameOutsideBottom = -512.0;

const double frameInsideLeft   =  -610.0;
const double frameInsideRight  =   610.0;
const double frameInsideTop    =   482.0;
const double frameInsideBottom =  -482.0;

const double ballSize = 20.0;
const double ballSizeHalf = ballSize / 2;

const double pI = 3.1415926535897932384626433832795;


BallUpdateCallback::BallUpdateCallback(Ball* ball)
: Pieces::GameObjectAction()
, m_ball(ball)
{
}

void BallUpdateCallback::operator()(Pieces::framenum_t /*frameNum*/)
{
    double angle = m_ball->getAngle();
    double velocity = m_ball->getVelocity();
    
    m_ball->addRelativeX(velocity * sin(angle));
    m_ball->addRelativeZ(velocity * cos(angle));


    // Check if ball hit wall
    if(m_ball->getPositionX() >= frameInsideRight - ballSizeHalf)
    {
        m_ball->setAngle(pI * 2 - m_ball->getAngle());
//        ++m_scorePlayer1;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    if(m_ball->getPositionX() <= frameInsideLeft + ballSizeHalf)
    {
        m_ball->setAngle(pI * 2 - m_ball->getAngle());
 //       ++m_scorePlayer2;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    if(m_ball->getPositionZ() >= frameInsideTop - ballSizeHalf)
    {
        m_ball->setAngle(pI - m_ball->getAngle());
    }

    if(m_ball->getPositionZ() <= frameInsideBottom + ballSizeHalf)
    {
        m_ball->setAngle(pI - m_ball->getAngle());
    }


    
    // Collition detection
}
