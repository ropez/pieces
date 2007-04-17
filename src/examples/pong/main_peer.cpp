#include "playerosg.h"
#include "ballosg.h"
#include "frame.h"
#include "event_handler.h"
#include "config.h"

#include <osgProducer/Viewer>
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
//#include <osgText/Text>



class PongPeer : public Pieces::Peer
{
public:
    PongPeer(osg::ref_ptr<osg::Group> rootOSG)
        : Pieces::Peer()
        , m_db(new Pieces::GameObjectDB())
        , m_rootOSG(rootOSG)
    {
        std::string host = "localhost";

        if (Pieces::app->argc() > 1)
        {
            host = Pieces::app->arg(1);
        }

        Pieces::SocketAddress sa(Pieces::InetAddress::getHostByName(host), 2222);

        PDEBUG << "Connecting to " << sa;

        connectTo(sa);

        // Join game
        {
            Pieces::Message message(MSG_GAME_EVENT_JOIN);
            message.set<Pieces::port_t>(Pieces::PR_PORT, 3333);
            sendMessage(message);
        }

        receiver()->listen(3333);
    }

protected:

    virtual void handle(Pieces::GameDataEvent* event)
    {
        Pieces::FrameData frameData = event->getFrameData();

        m_db->applyFrameData(event->getFrameNumber(), event->getFrameData());

        m_db->applyAction(ACTION_DRAW, event->getFrameNumber());
    }

    virtual void handle(Pieces::MessageReceivedEvent* event)
    {
        Pieces::Message message = event->getMessage();

        if (message.getMessageType() == Pieces::OBJECT_CREATE)
        {
            int objectType = message.get<int>(Pieces::PR_OBJECT_TYPE);
            Pieces::objectid_t objectId = message.get<Pieces::objectid_t>(Pieces::PR_OBJECT_ID);

            switch (objectType)
            {
            case TYPE_BALL:
                {
                    PDEBUG << "Creating ball";
                    Pieces::ReferencePointer<Ball> ball = new Ball(objectId);
                    Pieces::ReferencePointer<BallPeerCallback> ballPeerCallback = new BallPeerCallback(ball.get(), 0);
                    ball->setAction(ACTION_DRAW, ballPeerCallback.get());

                    osg::ref_ptr<BallOSG> ballOSG = new BallOSG(ball);
                    m_rootOSG->addChild(ballOSG.get());


                    m_db->insert(objectId, ball.get());

                    break;
                }
            default:
                PWARNING << "Unknown object type: " << objectType;
                return;
            }
        }
        else if (message.getMessageType() == Pieces::OBJECT_REMOVE)
        {
            Pieces::objectid_t objectId = message.get<Pieces::objectid_t>(Pieces::PR_OBJECT_ID);
            m_db->remove(objectId);
        }
    }

private:
    Pieces::AutoPointer<Pieces::GameObjectDB> m_db;
    osg::ref_ptr<osg::Group> m_rootOSG;
};



osg::ref_ptr<osg::Node> createMenu()
{
	osg::ref_ptr<osg::MatrixTransform> host = new osg::MatrixTransform();
//	host->addChild(osgText::Text);
	return 0;
}


int main(int argc, char** argv)
{

    Pieces::Application application(argc, argv);

    osg::ref_ptr<osg::Group> root = new osg::Group();
    
    // Start graphics thread.
    OSGThread osgThread(root.get());

    // Start network loop
    PongPeer pongPeer(root.get());

    osgThread.start();
    pongPeer.exec();

}