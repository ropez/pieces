#include "pong_peer.h"
#include "Pieces/Application"
#include "osg_thread.h"

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
