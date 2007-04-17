
#ifndef OSG_THREAD_H
#define OSG_THREAD_H

#include "OpenThreads/Thread"
#include <osgProducer/Viewer>
#include "playerosg.h"

/**
 * \class EventLoopThread
 * \brief A thread that runs an event loop.
 *
 * EventLoop::exec() blocks the calling thread, and the event handler
 * is called on the same thread. This is a convenience class that runs an
 * eventloop in a background thread, and calls the event handler in this
 * thread.
 *
 * \author Joakim Simonsson
 */
class OSGThread : public OpenThreads::Thread
{
public:

    /**
     * Create an event loop thread that will send events to the given \a handler.
     */
    OSGThread(osg::ref_ptr<osg::Group> root);

    /**
     * Quits the event loop and joins the thread.
     */
    ~OSGThread();


protected:
    virtual void run();

private:
    //DISABLE_COPY(OSGThread);

    osg::ref_ptr<PlayerOSG> setUpPlayer(double x, double z);
    osg::ref_ptr<osg::Group> setUpWorld();

    osgProducer::Viewer m_viewer;
    osg::ref_ptr<osg::Group> m_root;
};

#endif // OSG_THREAD_H
