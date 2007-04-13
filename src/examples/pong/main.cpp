#include "player.h"
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
#include "ball.h"
#include "BallPeerCallback.h"
//#include <osgText/Text>



class PongPeer : public Pieces::Peer
{
public:
    PongPeer(osgProducer::Viewer& viewer, osg::ref_ptr<BallOSG> ballOSG)
        : Pieces::Peer()
        , m_db(new Pieces::GameObjectDB())
        , m_viewer(viewer)
        , m_ballOSG(ballOSG)
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

        m_db->applyFrameData(event->getFrameData());
        
        m_db->applyAction(ACTION_DRAW, event->getFrameNumber());

        m_viewer.update();
        m_viewer.frame();

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
                    Pieces::ReferencePointer<BallPeerCallback> ballPeerCallback = new BallPeerCallback(ball.get(), m_ballOSG);
                    
                    ball->setAction(ACTION_DRAW, ballPeerCallback.get());
                    
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
    osgProducer::Viewer& m_viewer;
    osg::ref_ptr<BallOSG> m_ballOSG;
};



osg::ref_ptr<osg::Node> createMenu()
{
	osg::ref_ptr<osg::MatrixTransform> host = new osg::MatrixTransform();
//	host->addChild(osgText::Text);
	return 0;
}

osg::ref_ptr<Player> setUpPlayer(double x, double z)
{
    osg::ref_ptr<Player> player = new Player();
    player->setPositionX(x);
    player->setPositionZ(z);

    return player;
 }

osg::ref_ptr<osg::Group> setUpWorld()
{
    osg::ref_ptr<osg::Group> world = new Frame();

    return world;
}


int main(int argc, char** argv)
{

    unsigned short v = 1;
    unsigned short& w = v;

    std::cout << "Hej og velkommen, sizeof shorts er: " << sizeof(w) << std::endl;
    Pieces::Application application(argc, argv);

    osgProducer::Viewer viewer;

    viewer.setUpViewer(
        osgProducer::Viewer::TRACKBALL_MANIPULATOR |
        osgProducer::Viewer::STATE_MANIPULATOR |
        osgProducer::Viewer::HEAD_LIGHT_SOURCE |
        osgProducer::Viewer::VIEWER_MANIPULATOR |
        osgProducer::Viewer::ESCAPE_SETS_DONE);

    viewer.getCameraConfig()->getRenderSurface(0)->setWindowName("Pong");

    viewer.setClearColor(osg::Vec4(1.0, 0.6, 0.6, 1.0));

    osg::ref_ptr<Player> player1 = setUpPlayer(cfg::player1XPos, 0);
    osg::ref_ptr<Player> player2 = setUpPlayer(cfg::player2XPos, 0);

    osg::ref_ptr<BallOSG> ball = new BallOSG();
    
    osg::ref_ptr<osg::Group> world = setUpWorld();
    world->addChild(player1.get());
    world->addChild(player2.get());
    world->addChild(ball.get());

    PongEventHandler* peh = new PongEventHandler(player1, player2, ball);
    viewer.getEventHandlerList().push_back(peh);

    //osg::ref_ptr<osg::DisplaySettings> ds = new osg::DisplaySettings();
    Producer::Camera* camera = viewer.getCamera(0);
 
    Producer::Camera::Lens* lens = new Producer::Camera::Lens();
    lens->setFrustum(-640, 640, -512, 512, 2048, 10000);
    lens->setAutoAspect(true);
    camera->setLens(lens);
    

    viewer.setSceneData(world.get());
    viewer.realize();

    PongPeer pongPeer(viewer, ball);

    pongPeer.exec();

    // wait for all cull and draw threads to complete.
    viewer.sync();

    // run a clean up frame to delete all OpenGL objects.
    viewer.cleanup_frame();

    // wait for all the clean up frame to complete.
    viewer.sync();

}