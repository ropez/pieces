#include "pong_peer.h"
#include "Pieces/Application"
#include "osg_thread.h"

int main(int argc, char** argv)
{
    pcs::Application application(argc, argv);

    osg::ref_ptr<osg::Group> root = new osg::Group();


    osgProducer::Viewer* viewer = new osgProducer::Viewer();
    pcs::AutoPointer<PongPeer> pongPeer(new PongPeer(root.get()));

    OSGThread osgThread(root, pongPeer.get());

    // Start graphics thread.
    osgThread.start();

    // Start network loop
    pongPeer->exec();

}
