#include "osg_thread.h"

#include "ballosg.h"
#include "config.h"
#include "event_handler.h"
#include "frame.h"
#include "score_board.h"

#include "Pieces/TimerEvent"

namespace pong
{

OSGThread::OSGThread(osg::ref_ptr<osg::Group> root, PongPeer* peer)
: OpenThreads::Thread()
, m_viewer()
, m_root(root)
{
    m_viewer.setUpViewInWindow(100, 100, 800, 600);

    m_root->addChild(setUpWorld().get());
    m_root->addChild(new ScoreBoard(peer->getPlayerList()));

    // Create an event handler that catches events from keyboard.
    PongEventHandler* peh = new PongEventHandler(peer);
    m_viewer.addEventHandler(peh);

    osg::Camera* camera = m_viewer.getCamera();
    camera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));

    // Set up view frustum
    camera->setProjectionMatrixAsFrustum(-640, 640, -512, 512, 2048, 10000);

    // Define the root node of the scene graph.
    m_viewer.setSceneData(m_root.get());
}


OSGThread::~OSGThread()
{
    join();
}


osg::ref_ptr<osg::Group> OSGThread::setUpWorld()
{
    osg::ref_ptr<osg::Group> world = new Frame();

    return world;
}


void OSGThread::run()
{
    m_viewer.run();
}

}
