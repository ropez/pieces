#include "pong_peer.h"

#include "config.h"

// Osg subclasses
#include "playerosg.h"
#include "ballosg.h"
#include "frame.h"
#include "event_handler.h"

// Pieces subclasses
#include "ball.h"
#include "player.h"

#include "Pieces/Application"
#include "Pieces/Debug"
#include "Pieces/Message"
#include "Pieces/GameDataReceiver"
#include "Pieces/FrameData"
#include "Pieces/ReferencePointer"
#include "Pieces/Exception"

PongPeer::PongPeer(osg::ref_ptr<osg::Group> rootOSG)
: pcs::Peer()
, m_db(new pcs::GameObjectDB())
, m_rootOSG(rootOSG)
, m_playerList(0)
{
    std::string host = "localhost";
    pcs::port_t listenPort = 3333;

    if(pcs::app->argc() > 1)
    {
        host = pcs::app->arg(1);
    }

    if(pcs::app->argc() > 2)
    {
        std::stringstream ss(pcs::app->arg(2));
        ss >> listenPort;
    }

    try
    {
        // Connect to host
        pcs::SocketAddress sa(pcs::InetAddress::getHostByName(host), 2222);
        PDEBUG << "Connecting to " << sa;
        connectTo(sa);

        // Send join message (so the host will send us GameDataEvents on port 3333)
        pcs::Message message(MSG_GAME_EVENT_JOIN);
        message.set<pcs::port_t>(pcs::PR_PORT, listenPort);
        sendMessage(message);

        // Start to listen for GameDataEvents
        receiver()->listen(listenPort);
    }
    catch(const pcs::Exception& e)
    {
        PERROR << e;
        throw;
    }
}

void PongPeer::handle(pcs::GameDataEvent* event)
{
    m_db->applyFrameData(event->getFrameNumber(), event->getFrameData());
}

void PongPeer::handle(pcs::MessageReceivedEvent* event)
{
    pcs::Message message = event->getMessage();

    switch(message.getMessageType())
    {
    case pcs::OBJECT_CREATE:
        {
            int objectType = message.get<int>(pcs::PR_OBJECT_TYPE);
            pcs::objectid_t objectId = message.get<pcs::objectid_t>(pcs::PR_OBJECT_ID);

            switch (objectType)
            {
            case TYPE_BALL:
                {
                    PDEBUG << "Creating ball";
                    pcs::ReferencePointer<Ball> ball = new Ball(objectId);

                    osg::ref_ptr<BallOSG> ballOSG = new BallOSG(ball);
                    m_rootOSG->addChild(ballOSG.get());

                    m_db->insert(objectId, ball.get());
                }
                break;
            case TYPE_PLAYER:
                {
                    PDEBUG << "Creating player " << m_playerList.size() + 1;

                    pcs::ReferencePointer<Player> player = new Player(objectId);

                    osg::ref_ptr<PlayerOSG> playerOSG = new PlayerOSG(player);
                    m_rootOSG->addChild(playerOSG.get());

                    m_db->insert(objectId, player.get());
                    m_playerList.push_back(player);
                    
                }
                break;
            default:
                PWARNING << "Unknown object type: " << objectType;
                break;
            }
        }
        break;
    case pcs::OBJECT_REMOVE:
        {
            pcs::objectid_t objectId = message.get<pcs::objectid_t>(pcs::PR_OBJECT_ID);
            m_db->remove(objectId);
        }
        break;
    case MSG_SCORE_UPDATED:
        //std::cout << "Score is updated" << std::endl;
        break;
    }

}

PlayerList_t* PongPeer::getPlayerList()
{
    return &m_playerList;
}

//
//osg::ref_ptr<osg::Node> createMenu()
//{
//    osg::ref_ptr<osg::MatrixTransform> host = new osg::MatrixTransform();
////  host->addChild(osgText::Text);
//    return 0;
//}
//
