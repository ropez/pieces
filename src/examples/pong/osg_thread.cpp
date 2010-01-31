#include "osg_thread.h"

#include "ballosg.h"
#include "config.h"
#include "event_handler.h"
#include "frame.h"
#include "score_board.h"

#include "Pieces/TimerEvent"


OSGThread::OSGThread(osg::ref_ptr<osg::Group> root, PongPeer* peer)
: OpenThreads::Thread()
, m_viewer()
, m_root(root)
{
    m_viewer.setUpViewInWindow(100, 100, 800, 600);
//     m_viewer.setUpViewer(
//         osgProducer::Viewer::TRACKBALL_MANIPULATOR |
//         osgProducer::Viewer::STATE_MANIPULATOR |
//         osgProducer::Viewer::HEAD_LIGHT_SOURCE |
//         osgProducer::Viewer::VIEWER_MANIPULATOR |
//         osgProducer::Viewer::ESCAPE_SETS_DONE);

//     m_viewer.getCameraConfig()->getRenderSurface(0)->setWindowName("Pong");

//     m_viewer.setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
 
    m_root->addChild(setUpWorld().get());
    m_root->addChild(new ScoreBoard(peer->getPlayerList()));

    // Create an event handler that catches events from keyboard.
    PongEventHandler* peh = new PongEventHandler(peer);
    m_viewer.addEventHandler(peh);

    osg::Camera* camera = m_viewer.getCamera();
    camera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
    
    // Set up view frustum
    camera->setProjectionMatrixAsFrustum(-640, 640, -512, 512, 2048, 10000);
//     osg::Camera::Lens* lens = new osg::Camera::Lens();
//     lens->setFrustum(-640, 640, -512, 512, 2048, 10000);
//     lens->setAutoAspect(true);
//     camera->setLens(lens);
    
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
    
//     m_viewer.realize();
// 
//     for(;;)
//     {
//         m_viewer.sync();
//         m_viewer.update();
//         m_viewer.frame();
//     }
// 
//     // wait for all cull and draw threads to complete.
//     m_viewer.sync();
// 
//     // run a clean up frame to delete all OpenGL objects.
//     m_viewer.cleanup_frame();
// 
//     // wait for all the clean up frame to complete.
//     m_viewer.sync();

}
