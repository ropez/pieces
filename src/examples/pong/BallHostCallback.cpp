// host.cpp

#include "BallHostCallback.h"
#include "config.h"
#include "Pieces/Debug"
#include <math.h>


BallUpdateCallback::BallUpdateCallback(Ball* ball)
: pcs::GameObjectAction()
, m_ball(ball)
{
}

void BallUpdateCallback::operator()(pcs::framenum_t /*frameNum*/)
{
    double angle = m_ball->getAngle();
    double velocity = m_ball->getVelocity();
    
    m_ball->addRelativeX(velocity * sin(angle));
    m_ball->addRelativeZ(velocity * cos(angle));


    // Check if ball hit wall
	if(m_ball->getPositionX() >= cfg::frameInsideRight - cfg::ballSizeHalf)
    {
		m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
//        ++m_scorePlayer1;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    if(m_ball->getPositionX() <= cfg::frameInsideLeft + cfg::ballSizeHalf)
    {
		m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
 //       ++m_scorePlayer2;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    if(m_ball->getPositionZ() >= cfg::frameInsideTop - cfg::ballSizeHalf)
    {
		m_ball->setAngle(cfg::pi - m_ball->getAngle());
    }

    if(m_ball->getPositionZ() <= cfg::frameInsideBottom + cfg::ballSizeHalf)
    {
		m_ball->setAngle(cfg::pi - m_ball->getAngle());
    }


    
    // Collition detection
}
