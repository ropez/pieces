#include "ball_host_callback.h"

#include "config.h"

#include "Pieces/Debug"

#include <math.h>

#include "Pieces/Host"
#include "Pieces/Message"

BallUpdateCallback::BallUpdateCallback(pcs::Host* host, Ball* ball, GameState* gameState, PlayerList_t* playerList)
: pcs::GameObjectAction()
, m_host(host)
, m_gameState(gameState)
, m_ball(ball)
, m_playerList(playerList)
, m_wallHitRight(false)
, m_wallHitLeft(false)
{
}

void BallUpdateCallback::operator()(pcs::framenum_t /*frameNum*/)
{
    double angle = m_ball->getAngle();
    double velocity = m_ball->getVelocity();
    
    // Update balls position w.r.t velocity and angle.
    m_ball->addRelativeX(velocity * sin(angle));
    m_ball->addRelativeZ(velocity * cos(angle));

    // Check if ball hits walls
    
    // Check right wall
    if(m_ball->getPositionX() >= cfg::frameInsideRight - cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
        m_gameState->ballIsLostForPlayerRight = true;
        
        pcs::Message msg(MSG_SCORE_UPDATED);
        m_host->sendMessage(msg);
    }

    // Check left wall
    if(m_ball->getPositionX() <= cfg::frameInsideLeft + cfg::ballSizeHalf)
    {
        m_ball->setAngle(cfg::pi * 2 - m_ball->getAngle());
        m_gameState->ballIsLostForPlayerLeft = true;

        pcs::Message msg(MSG_SCORE_UPDATED);
        m_host->sendMessage(msg);
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

        const bool ballIsMovingTowardLeft = m_ball->getAngle() > cfg::pi ? true : false;
        
        if(ballIsMovingTowardLeft)
        {
            // Ball is moving towards left
            ballPotentialHitSide = -cfg::ballSizeHalf;
        }
        else
        {
            // Ball is moving towards right
            ballPotentialHitSide = cfg::ballSizeHalf;
        }

        ballPotentialHitSide += m_ball->getPositionX();

        // Constants that makes the tests more understandable for humans.
        const double playerSideRight  = player->getPositionX() + cfg::playerWidthHalf;
        const double playerSideLeft   = player->getPositionX() - cfg::playerWidthHalf;
        const double playerSideTop    = player->getPositionZ() + cfg::playerHeightHalf;
        const double playerSideBottom = player->getPositionZ() - cfg::playerHeightHalf;

        if((playerSideLeft <= ballPotentialHitSide) && (ballPotentialHitSide <= playerSideRight))
        {
            if((playerSideBottom <= m_ball->getPositionZ()) && (m_ball->getPositionZ() <= playerSideTop))
            {
                // The ball has hit the player.
                double centerOffset = (player->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

                if(ballIsMovingTowardLeft)
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
