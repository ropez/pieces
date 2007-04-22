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
            return false;
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
                    //m_ball->setVelocity(cfg::ballVelocity);
                    //m_ball->setAngle(osg::DegreesToRadians(-90.0));
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
