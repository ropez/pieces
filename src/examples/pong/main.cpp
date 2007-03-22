#include "player.h"
#include "ball.h"
#include "frame.h"
#include "event_handler.h"
#include "config.h"

#include <osgProducer/Viewer>

#include <osgText/Text>

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

int main()
{
    osgProducer::Viewer viewer;
    viewer.setUpViewer(
        osgProducer::Viewer::TRACKBALL_MANIPULATOR |
        osgProducer::Viewer::STATE_MANIPULATOR |
        osgProducer::Viewer::HEAD_LIGHT_SOURCE |
        osgProducer::Viewer::VIEWER_MANIPULATOR |
        osgProducer::Viewer::ESCAPE_SETS_DONE);
    viewer.getCameraConfig()->getRenderSurface(0)->setWindowName("Pong");

    viewer.setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));

    osg::ref_ptr<Player> player1 = setUpPlayer(cfg::player1XPos, 0);
    osg::ref_ptr<Player> player2 = setUpPlayer(cfg::player2XPos, 0);

    osg::ref_ptr<Ball> ball = new Ball();
    
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

    while(!viewer.done())
    {
        viewer.sync();
        viewer.update();
        viewer.frame();
    }

    // wait for all cull and draw threads to complete.
    viewer.sync();

    // run a clean up frame to delete all OpenGL objects.
    viewer.cleanup_frame();

    // wait for all the clean up frame to complete.
    viewer.sync();

}