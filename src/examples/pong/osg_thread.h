#ifndef OSG_THREAD_H
#define OSG_THREAD_H

#include "OpenThreads/Thread"

#include "playerosg.h"
#include "pong_peer.h"


#include <osgViewer/Viewer>

namespace pong
{

/**
 * \class OSGThread
 * \brief The thread that updates the graphics.
 *
 *  Creates and initalize an osgProducer::Viewer object, that will serve as display.
 *
 * \author Joakim Simonsson
 */
class OSGThread : public OpenThreads::Thread
{
public:

    /**
     *
     */
    OSGThread(osg::ref_ptr<osg::Group> root, PongPeer* peer);

    /**
     *
     */
    ~OSGThread();


protected:
    virtual void run();

private:
    //DISABLE_COPY(OSGThread);

    osg::ref_ptr<osg::Group> setUpWorld();

    osgViewer::Viewer m_viewer;
    osg::ref_ptr<osg::Group> m_root;
};

}

#endif // OSG_THREAD_H
