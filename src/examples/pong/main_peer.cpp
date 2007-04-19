#include "playerosg.h"
#include "ballosg.h"
#include "frame.h"
#include "event_handler.h"
#include "config.h"

#include "pong_defines.h"

#include "Pieces/Application"
#include "Pieces/Peer"
#include "Pieces/GameDataEvent"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/AutoPointer"
#include "Pieces/GameObjectDB"
#include "Pieces/Debug"
#include "Pieces/Message"
#include "Pieces/GameDataReceiver"
#include "Pieces/FrameData"
#include "Pieces/Global"
#include "Pieces/ReferencePointer"

#include "osg_thread.h"
#include "ball.h"
#include "BallPeerCallback.h"
#include "player.h"
#include "PlayerPeerCallback.h"
//#include <osgText/Text>



class PongPeer : public pcs::Peer
{
public:
    PongPeer(osg::ref_ptr<osg::Group> rootOSG)
        : pcs::Peer()
        , m_db(new pcs::GameObjectDB())
        , m_rootOSG(rootOSG)
    {
        std::string host = "localhost";

        if (pcs::app->argc() > 1)
        {
            host = pcs::app->arg(1);
        }

        pcs::SocketAddress sa(pcs::InetAddress::getHostByName(host), 2222);

        PDEBUG << "Connecting to " << sa;

        connectTo(sa);

        // Join game
        {
            pcs::Message message(MSG_GAME_EVENT_JOIN);
            message.set<pcs::port_t>(pcs::PR_PORT, 3333);
            sendMessage(message);
        }

        receiver()->listen(3333);
    }

protected:

    virtual void handle(pcs::GameDataEvent* event)
    {
        pcs::FrameData frameData = event->getFrameData();

        m_db->applyFrameData(event->getFrameNumber(), event->getFrameData());

        m_db->applyAction(ACTION_DRAW, event->getFrameNumber());
    }

    virtual void handle(pcs::MessageReceivedEvent* event)
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
                        pcs::ReferencePointer<BallPeerCallback> ballPeerCallback = new BallPeerCallback(ball.get());
                        ball->setAction(ACTION_DRAW, ballPeerCallback.get());

                        osg::ref_ptr<BallOSG> ballOSG = new BallOSG(ball);
                        m_rootOSG->addChild(ballOSG.get());

                        m_db->insert(objectId, ball.get());
                    }
                    break;
                case TYPE_PLAYER_1:
                    {
                        PDEBUG << "Creating player 1";
                        pcs::ReferencePointer<Player> player = new Player(objectId, cfg::player1XPos);
                        player->setAction(ACTION_DRAW, new PlayerPeerCallback(player.get()));

                        osg::ref_ptr<PlayerOSG> playerOSG = new PlayerOSG(player);
                        m_rootOSG->addChild(playerOSG.get());

                        m_db->insert(objectId, player.get());
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
        }
    }

private:
    pcs::AutoPointer<pcs::GameObjectDB> m_db;
    osg::ref_ptr<osg::Group> m_rootOSG;

};



osg::ref_ptr<osg::Node> createMenu()
{
    osg::ref_ptr<osg::MatrixTransform> host = new osg::MatrixTransform();
//  host->addChild(osgText::Text);
    return 0;
}


int main(int argc, char** argv)
{

    pcs::Application application(argc, argv);

    osg::ref_ptr<osg::Group> root = new osg::Group();
    
    PongPeer pongPeer(root.get());

    OSGThread osgThread(root.get(), pongPeer);

        
    // Start graphics thread.
    osgThread.start();

    // Start network loop
    pongPeer.exec();

}
