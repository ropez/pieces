#include "BallHostCallback.h"

#include "config.h"

#include "Pieces/Debug"

#include <math.h>


BallUpdateCallback::BallUpdateCallback(Ball* ball, PlayerList_t* playerList)
: pcs::GameObjectAction()
, m_ball(ball)
, m_playerList(playerList)
{
}

void BallUpdateCallback::operator()(pcs::framenum_t /*frameNum*/)
{
    double angle = m_ball->getAngle();
    double velocity = m_ball->getVelocity();
    
    m_ball->addRelativeX(velocity * sin(angle));
    m_ball->addRelativeZ(velocity * cos(angle));

    // Check if ball hits walls

    // Check right wall
    if(m_ball->getPositionX() >= cfg::frameInsideRight - cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
//        ++m_scorePlayer1;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    // Check left wall
    if(m_ball->getPositionX() <= cfg::frameInsideLeft + cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
 //       ++m_scorePlayer2;
//        std::cout << "Player1:\t" << m_scorePlayer1 << "\tPlayer2:\t" << m_scorePlayer2 << "\r";
    }

    // Check top wall
    if(m_ball->getPositionZ() >= cfg::frameInsideTop - cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi - m_ball->getAngle());
    }

    // Check bottom wall
    if(m_ball->getPositionZ() <= cfg::frameInsideBottom + cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi - m_ball->getAngle());
    }


    // Make angle in the interval [0, 2*PI)  (If someone knows a better way to do this,
    // please let me know, Joakim)
    m_ball->setAngle(fmod(cfg::pi2 + fmod(m_ball->getAngle(), cfg::pi2), cfg::pi2));
    

    // Check if ball hit a player
    for(PlayerList_t::iterator it = m_playerList->begin(); it != m_playerList->end(); ++it)
    {
        pcs::ReferencePointer<Player> player = (*it);
        
        double ballPotentialHitSide = 0.0;
        double playerPotentialHitSide = 0.0;

        if(m_ball->getAngle() > cfg::pi)
        {
            // Ball is moving towards left
            ballPotentialHitSide = -cfg::ballSizeHalf;
            playerPotentialHitSide = cfg::playerWidth;
        }
        else
        {
            // Ball is moving towards right
            ballPotentialHitSide = cfg::ballSizeHalf;
            playerPotentialHitSide = -cfg::playerWidth;
        }

        ballPotentialHitSide += m_ball->getPositionX();
        playerPotentialHitSide += player->getPositionX();

        // Constants that makes the tests more understandable for humans.
        double playerSideRight  = player->getPositionX() + cfg::playerWidthHalf;
        double playerSideLeft   = player->getPositionX() - cfg::playerWidthHalf;
        double playerSideTop    = player->getPositionZ() + cfg::playerHeightHalf;
        double playerSideBottom = player->getPositionZ() - cfg::playerHeightHalf;

        if((playerSideLeft <= ballPotentialHitSide) && (ballPotentialHitSide <= playerSideRight))
        {
            if((playerSideBottom <= m_ball->getPositionZ()) && (m_ball->getPositionZ() <= playerSideTop))
            {
                // The ball has hit the player.
                double centerOffset = (player->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

                if(m_ball->getAngle() > cfg::pi)
                {
                    // Ball is moving towards left
                    m_ball->setAngle(cfg::pi2 - (centerOffset * -cfg::maxAngle - cfg::pi_2));
                }
                else
                {
                    // Ball is moving towards right
                    m_ball->setAngle(cfg::pi - (centerOffset * cfg::maxAngle - cfg::pi_2));
                }

                // This "break" is a tiny optimization, since we assume the ball cannot hit both players in the same frame.
                break; 
            }
        }
    }

    // Make angle in the interval [0, 2*PI)  (If someone knows a better way to do this,
    // please let me know, Joakim)
    m_ball->setAngle(fmod(cfg::pi2 + fmod(m_ball->getAngle(), cfg::pi2), cfg::pi2));

}
