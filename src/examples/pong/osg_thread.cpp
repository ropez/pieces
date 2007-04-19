#include "osg_thread.h"

#include "ballosg.h"
#include "config.h"
#include "event_handler.h"
#include "frame.h"

OSGThread::OSGThread(osg::ref_ptr<osg::Group> root, pcs::Peer& peer)
: OpenThreads::Thread()
, m_viewer()
, m_root(root)
{
    m_viewer.setUpViewer(
        osgProducer::Viewer::TRACKBALL_MANIPULATOR |
        osgProducer::Viewer::STATE_MANIPULATOR |
        osgProducer::Viewer::HEAD_LIGHT_SOURCE |
        osgProducer::Viewer::VIEWER_MANIPULATOR |
        osgProducer::Viewer::ESCAPE_SETS_DONE);

    m_viewer.getCameraConfig()->getRenderSurface(0)->setWindowName("Pong");

    m_viewer.setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));

    osg::ref_ptr<osg::Group> world = setUpWorld();
    
    m_root->addChild(world.get());    

    PongEventHandler* peh = new PongEventHandler(peer);
    m_viewer.getEventHandlerList().push_back(peh);

    //osg::ref_ptr<osg::DisplaySettings> ds = new osg::DisplaySettings();
    Producer::Camera* camera = m_viewer.getCamera(0);

    Producer::Camera::Lens* lens = new Producer::Camera::Lens();
    lens->setFrustum(-640, 640, -512, 512, 2048, 10000);
    lens->setAutoAspect(true);
    camera->setLens(lens);


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
    
    m_viewer.realize();


    while(!m_viewer.done())
    {
        m_viewer.sync();
        m_viewer.update();
        m_viewer.frame();
    }

    // wait for all cull and draw threads to complete.
    m_viewer.sync();

    // run a clean up frame to delete all OpenGL objects.
    m_viewer.cleanup_frame();

    // wait for all the clean up frame to complete.
    m_viewer.sync();

}
