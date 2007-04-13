#include "event_handler.h"
#include "config.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <iostream>

PongEventHandler::PongEventHandler(osg::ref_ptr<PlayerOSG> player1, osg::ref_ptr<PlayerOSG> player2, osg::ref_ptr<BallOSG> ball)
: osgGA::GUIEventHandler()
, m_player1(player1)
, m_player2(player2)
, m_ball(ball)
, m_player1Up(false)
, m_player1Down(false)
, m_player2Up(false)
, m_player2Down(false)
, m_waitCollisionPlayer1(0)
, m_waitCollisionPlayer2(0)
, m_scorePlayer1(0)
, m_scorePlayer2(0)
{
}

PongEventHandler::~PongEventHandler()
{
}

bool PongEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
{

    switch(ea.getEventType())
    {
    case(osgGA::GUIEventAdapter::FRAME):
        {
            // Move players
            if(m_player1Up)
            {
                m_player1->addRelativeZ(cfg::playerVelocity);
                if(m_player1->getPositionZ() + cfg::playerHeightHalf > cfg::frameInsideTop)
                {
                    m_player1->setPositionZ(cfg::frameInsideTop - cfg::playerHeightHalf);
                }
            }

            if(m_player1Down)
            {
                m_player1->addRelativeZ(-cfg::playerVelocity);
                if(m_player1->getPositionZ() - cfg::playerHeightHalf < cfg::frameInsideBottom)
                {
                    m_player1->setPositionZ(cfg::frameInsideBottom + cfg::playerHeightHalf);
                }
            }

            if(m_player2Up)
            {
                m_player2->addRelativeZ(cfg::playerVelocity);
                if(m_player2->getPositionZ() + cfg::playerHeightHalf > cfg::frameInsideTop)
                {
                    m_player2->setPositionZ(cfg::frameInsideTop - cfg::playerHeightHalf);
                }
            }
            
            if(m_player2Down)
            {
                m_player2->addRelativeZ(-cfg::playerVelocity);
                if(m_player2->getPositionZ() - cfg::playerHeightHalf < cfg::frameInsideBottom)
                {
                    m_player2->setPositionZ(cfg::frameInsideBottom + cfg::playerHeightHalf);
                }
            }


            // Check if ball hit player
            if(m_waitCollisionPlayer2 == 0)
            {
                if(m_ball->getPositionX() + cfg::ballSizeHalf >= cfg::player2XPos &&
                    cfg::player2XPos + cfg::playerWidth >= m_ball->getPositionX() + cfg::ballSizeHalf)
                {
                    if(m_player2->getPositionZ() - 50 < m_ball->getPositionZ() &&
                        m_ball->getPositionZ() < m_player2->getPositionZ() + 50)
                    {
                        m_waitCollisionPlayer2 = 10;

                        double centerOffset = (m_player2->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

                        m_ball->setAngle(osg::PI - (centerOffset * cfg::maxAngle - osg::PI_2));
                    }
                }
            }
            else
            {
                --m_waitCollisionPlayer2;
            }

            if(m_waitCollisionPlayer1 == 0)
            {
                if(m_ball->getPositionX() - cfg::ballSizeHalf <= cfg::player1XPos &&
                    cfg::player1XPos - cfg::playerWidth <= m_ball->getPositionX() + cfg::ballSizeHalf)
                {
                    if(m_player1->getPositionZ() - cfg::playerHeightHalf < m_ball->getPositionZ() &&
                        m_ball->getPositionZ() < m_player1->getPositionZ() + cfg::playerHeightHalf)
                    {
                        m_waitCollisionPlayer1 = 10;

                        double centerOffset = (m_player1->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

                        m_ball->setAngle(osg::PI * 2 - (centerOffset * -cfg::maxAngle - osg::PI_2));
                    }
                }
            }
            else
            {
                --m_waitCollisionPlayer1;
            }

            return true;
        }
    case(osgGA::GUIEventAdapter::KEYDOWN):
        {
            switch(ea.getKey())
            {
            case 'q':
                m_player1Up = true;
                if(m_player1Down)
                {
                    m_player1Down = false;
                }
                break;
            case 'a':
                m_player1Down = true;
                if(m_player1Up)
                {
                    m_player1Up = false;
                }
                break;
            case osgGA::GUIEventAdapter::KEY_Up:
                m_player2Up = true;
                if(m_player2Down)
                {
                    m_player2Down = false;
                }
                break;
            case osgGA::GUIEventAdapter::KEY_Down:
                m_player2Down = true;
                if(m_player2Up)
                {
                    m_player2Up = false;
                }
                break;
            case osgGA::GUIEventAdapter::KEY_Tab:
                {
                    m_ball->setVelocity(cfg::ballVelocity);
                    m_ball->setAngle(osg::DegreesToRadians(-90.0));
                }

            }
            return true;
        }
     case(osgGA::GUIEventAdapter::KEYUP):
        {
            switch(ea.getKey())
            {
            case 'q':
                m_player1Up = false;
                break;
            case 'a':
                m_player1Down = false;
                break;
            case osgGA::GUIEventAdapter::KEY_Up:
                m_player2Up = false;
                break;
            case osgGA::GUIEventAdapter::KEY_Down:
                m_player2Down = false;
                break;
            }
            return true;
        }
    }


    return false;
}

void PongEventHandler::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


}