#include "event_handler.h"

#include "config.h"
#include "pong_defines.h"

#include "Pieces/Message"

#include <osg/Geode>
#include <osg/Geometry>

#include <iostream>

PongEventHandler::PongEventHandler(pcs::Peer& peer)
: osgGA::GUIEventHandler()
, m_peer(peer)
, m_player1(0)
, m_player2(0)
, m_ball(0)
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
            //// Move players
            //if(m_player1Up)
            //{
            //    m_player1->addRelativeZ(cfg::playerVelocity);
            //    if(m_player1->getPositionZ() + cfg::playerHeightHalf > cfg::frameInsideTop)
            //    {
            //        m_player1->setPositionZ(cfg::frameInsideTop - cfg::playerHeightHalf);
            //    }
            //}

            //if(m_player1Down)
            //{
            //    m_player1->addRelativeZ(-cfg::playerVelocity);
            //    if(m_player1->getPositionZ() - cfg::playerHeightHalf < cfg::frameInsideBottom)
            //    {
            //        m_player1->setPositionZ(cfg::frameInsideBottom + cfg::playerHeightHalf);
            //    }
            //}

            //if(m_player2Up)
            //{
            //    m_player2->addRelativeZ(cfg::playerVelocity);
            //    if(m_player2->getPositionZ() + cfg::playerHeightHalf > cfg::frameInsideTop)
            //    {
            //        m_player2->setPositionZ(cfg::frameInsideTop - cfg::playerHeightHalf);
            //    }
            //}
            //
            //if(m_player2Down)
            //{
            //    m_player2->addRelativeZ(-cfg::playerVelocity);
            //    if(m_player2->getPositionZ() - cfg::playerHeightHalf < cfg::frameInsideBottom)
            //    {
            //        m_player2->setPositionZ(cfg::frameInsideBottom + cfg::playerHeightHalf);
            //    }
            //}

            //if(m_ball.valid())
            //{

            //    // Check if ball hit player
            //    if(m_waitCollisionPlayer2 == 0)
            //    {
            //        if(m_ball->getPositionX() + cfg::ballSizeHalf >= cfg::player2XPos &&
            //            cfg::player2XPos + cfg::playerWidth >= m_ball->getPositionX() + cfg::ballSizeHalf)
            //        {
            //            if(m_player2->getPositionZ() - 50 < m_ball->getPositionZ() &&
            //                m_ball->getPositionZ() < m_player2->getPositionZ() + 50)
            //            {
            //                m_waitCollisionPlayer2 = 10;

            //                double centerOffset = (m_player2->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

            //                m_ball->setAngle(osg::PI - (centerOffset * cfg::maxAngle - osg::PI_2));
            //            }
            //        }
            //    }
            //    else
            //    {
            //        --m_waitCollisionPlayer2;
            //    }

            //    if(m_waitCollisionPlayer1 == 0)
            //    {
            //        if(m_ball->getPositionX() - cfg::ballSizeHalf <= cfg::player1XPos &&
            //            cfg::player1XPos - cfg::playerWidth <= m_ball->getPositionX() + cfg::ballSizeHalf)
            //        {
            //            if(m_player1->getPositionZ() - cfg::playerHeightHalf < m_ball->getPositionZ() &&
            //                m_ball->getPositionZ() < m_player1->getPositionZ() + cfg::playerHeightHalf)
            //            {
            //                m_waitCollisionPlayer1 = 10;

            //                double centerOffset = (m_player1->getPositionZ() - m_ball->getPositionZ()) / cfg::playerHeightHalf;

            //                m_ball->setAngle(osg::PI * 2 - (centerOffset * -cfg::maxAngle - osg::PI_2));
            //            }
            //        }
            //    }
            //    else
            //    {
            //        --m_waitCollisionPlayer1;
            //    }
            //}

            return true;
        }
    case(osgGA::GUIEventAdapter::KEYDOWN):
        {
            switch(ea.getKey())
            {
            case osgGA::GUIEventAdapter::KEY_Up:
                {
                    if(!m_player2Up)
                    {
                        m_player2Up = true;

                        pcs::Message msg(MSG_UP_PRESSED);
                        m_peer.sendMessage(msg);
                    }
                    break;
                }
            case osgGA::GUIEventAdapter::KEY_Down:
                {
                    
                    if(!m_player2Down)
                    {
                        m_player2Down = true;

                        pcs::Message msg(MSG_DOWN_PRESSED);
                        m_peer.sendMessage(msg);
                    }
                    break;
                }
            case osgGA::GUIEventAdapter::KEY_Tab:
                {
                    m_ball->setVelocity(cfg::ballVelocity);
                    m_ball->setAngle(osg::DegreesToRadians(-90.0));
                    break;
                }

            }
            return true;
        }
    case(osgGA::GUIEventAdapter::KEYUP):
        {
            switch(ea.getKey())
            {
            case osgGA::GUIEventAdapter::KEY_Up:
                {
                    m_player2Up = false;
                    pcs::Message msg(MSG_UP_RELEASED);
                    m_peer.sendMessage(msg);

                    break;
                }
            case osgGA::GUIEventAdapter::KEY_Down:
                {
                    m_player2Down = false;

                    pcs::Message msg(MSG_DOWN_RELEASED);
                    m_peer.sendMessage(msg);

                    break;
                }
            }
            return true;
        }
    }


    return false;
}

void PongEventHandler::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


}