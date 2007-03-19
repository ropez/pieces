
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/IOException"

#include "Pieces/Host"
#include "Pieces/Peer"

#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"

#include "Pieces/Timer"

#include "Pieces/GameObject"
#include "Pieces/HostGameObject"
#include "Pieces/PeerGameObject"

#include "Pieces/FrameData"
#include "Pieces/GameData"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"

#include <map>
#include <cmath>

namespace Pieces
{

// DUMMY simulation of host and peer functionality
OpenThreads::Mutex mutex;
GameData gamedata;

class GameDataSender
{
public:
    GameDataSender()
    : frameNumber(0)
    {
    }

    FrameData getFrameData(framenum_t frameNum) const
    {
        OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
        return gamedata.getFrameData(frameNum);
    }

    void sendFrameData(const FrameData& frame)
    {
        OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
        gamedata.setFrameData(frameNumber++, frame);
    }

private:
    framenum_t frameNumber;
};

class GameDataReceiver
{
public:
    FrameData getFrameData(framenum_t frameNum)
    {
        OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
        return gamedata.getFrameData(frameNum);
    }
};




/**
 * \class HostObjectDB
 *
 *
 * \author Robin Pedersen
 */
class HostObjectDB
{
public:
    typedef std::map<objectid_t, HostObjectIface*> map_t;

    HostObjectDB();
    ~HostObjectDB();

    void clear();

    /**
     * Returns a pointer to the object replaced, or 0 if no object was replaced.
     */
    HostObjectIface* insert(objectid_t objectId, HostObjectIface* obj);

    HostObjectIface* remove(objectid_t objectId);
    HostObjectIface* remove(map_t::iterator it);

    void update(FrameData& frame) const;

    map_t::iterator begin();
    map_t::iterator end();

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

private:
    // Disable copy operations
    HostObjectDB(const HostObjectDB&);
    HostObjectDB& operator=(const HostObjectDB&);

    map_t m_objects;
};



HostObjectDB::HostObjectDB()
    : m_objects()
{
}


HostObjectDB::~HostObjectDB()
{
}


void HostObjectDB::clear()
{
    m_objects.clear();
}


HostObjectIface* HostObjectDB::insert(objectid_t objectId, HostObjectIface* obj)
{
    HostObjectIface* o = remove(objectId);
    m_objects[objectId] = obj;
    return o;
}


HostObjectIface* HostObjectDB::remove(objectid_t objectId)
{
    map_t::iterator it = m_objects.find(objectId);

    return remove(it);
}


HostObjectIface* HostObjectDB::remove(map_t::iterator it)
{
    if (it != end())
    {
        HostObjectIface* o = it->second;
        m_objects.erase(it);
        return o;
    }
    return 0;
}


void HostObjectDB::update(FrameData& frame) const
{
    for (map_t::const_iterator it = begin(); it != end(); ++it)
    {
        objectid_t id = it->first;
        HostObjectIface* obj = it->second;

        // Object data
        BufferStream s;
        obj->encode(s);

        frame.setObjectData(id, s.data());
    }
}


HostObjectDB::map_t::iterator HostObjectDB::begin()
{
    return m_objects.begin();
}


HostObjectDB::map_t::iterator HostObjectDB::end()
{
    return m_objects.end();
}


HostObjectDB::map_t::const_iterator HostObjectDB::begin() const
{
    return m_objects.begin();
}


HostObjectDB::map_t::const_iterator HostObjectDB::end() const
{
    return m_objects.end();
}


/**
 * \class PeerObjectDB
 *
 *
 * \author Robin Pedersen
 */
class PeerObjectDB
{
public:
    typedef std::map<objectid_t, PeerObjectIface*> map_t;

    PeerObjectDB();
    ~PeerObjectDB();

    void clear();

    /**
     * Returns a pointer to the object replaced, or 0 if no object was replaced.
     */
    PeerObjectIface* insert(objectid_t objectId, PeerObjectIface* obj);

    PeerObjectIface* remove(objectid_t objectId);
    PeerObjectIface* remove(map_t::iterator it);

    void apply(const FrameData& frame);

    map_t::iterator begin();
    map_t::iterator end();

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

private:
    // Disable copy operations
    PeerObjectDB(const PeerObjectDB&);
    PeerObjectDB& operator=(const PeerObjectDB&);

    map_t m_objects;
};



PeerObjectDB::PeerObjectDB()
: m_objects()
{
}


PeerObjectDB::~PeerObjectDB()
{
}


void PeerObjectDB::clear()
{
    m_objects.clear();
}


PeerObjectIface* PeerObjectDB::insert(objectid_t objectId, PeerObjectIface* obj)
{
    PeerObjectIface* o = remove(objectId);
    m_objects[objectId] = obj;
    return o;
}


PeerObjectIface* PeerObjectDB::remove(objectid_t objectId)
{
    map_t::iterator it = m_objects.find(objectId);

    return remove(it);
}


PeerObjectIface* PeerObjectDB::remove(map_t::iterator it)
{
    if (it != end())
    {
        PeerObjectIface* o = it->second;
        m_objects.erase(it);
        return o;
    }
    return 0;
}


void PeerObjectDB::apply(const FrameData& frame)
{
    for (map_t::const_iterator it = begin(); it != end(); ++it)
    {
        objectid_t id = it->first;
        PeerObjectIface* obj = it->second;

        // Object data
        BufferStream s(frame.getObjectData(id));


        // TODO: Don't catch exception here
        try
        {
            // Decode object data into stream
            obj->decode(s);
        }
        catch (const IOException& e)
        {
            ERROR << e;
        }
    }
}


PeerObjectDB::map_t::iterator PeerObjectDB::begin()
{
    return m_objects.begin();
}


PeerObjectDB::map_t::iterator PeerObjectDB::end()
{
    return m_objects.end();
}


PeerObjectDB::map_t::const_iterator PeerObjectDB::begin() const
{
    return m_objects.begin();
}


PeerObjectDB::map_t::const_iterator PeerObjectDB::end() const
{
    return m_objects.end();
}

} // namespace Pieces


// Demonstration

using namespace Pieces;

std::auto_ptr<Host> host;

class ThreadRunningHost : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        host->exec();
    }
};

std::auto_ptr<Peer> peer;

class ThreadRunningPeer : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        peer->exec();
    }
};


/**
 * Test implementation of GameObject
 */
class MovingBall : public GameObject
{
public:
    MovingBall(objectid_t objectId)
    : GameObject(objectId)
    , m_posx(0.0)
    , m_posy(0.0)
    , m_diam(10.0)
    {
    }


    virtual void encode(DataStream& ds) const
    {
        ds << m_posx << m_posy << m_diam;
    }

    virtual void decode(DataStream& ds)
    {
        ds >> m_posx >> m_posy >> m_diam;
    }


    double getPosX() const
    {
        return m_posx;
    }


    void setPosX(double val)
    {
        m_posx = val;
    }


    double getPosY() const
    {
        return m_posy;
    }


    void setPosY(double val)
    {
        m_posy = val;
    }


    double getDiam() const
    {
        return m_diam;
    }


    void setDiam(double val)
    {
        m_diam = val;
    }

private:
    double m_posx;
    double m_posy;
    double m_diam;
};


/**
 * Test implementation of HostGameObject
 */
class HostBumperCar : public HostGameObject
{
public:
    HostBumperCar(objectid_t objectId)
    : HostGameObject(objectId)
    , speed(0)
    {
    }

    virtual void encode(DataStream& ds) const
    {
        ds << speed;
    }

    double speed;
    double host_specific_data;
};


/**
 * Test implementation of PeerGameObject
 */
class PeerBumperCar : public PeerGameObject
{
public:
    PeerBumperCar(objectid_t objectId)
    : PeerGameObject(objectId)
    , speed(0)
    {
    }

    virtual void decode(DataStream& ds)
    {
        ds >> speed;
    }

    double speed;
};


const objectid_t idBall = 100;
const objectid_t idCar = 200;


class MyHost : public Host
{
public:
    MyHost()
    : Host()
    , m_db(new HostObjectDB())
    , frame(0)
    , sender()
    , ball(new MovingBall(idBall))
    , car(new HostBumperCar(idCar))
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());
    }

    HostObjectDB* db() const
    {
        return m_db.get();
    }

protected:
    virtual void handle(TimerEvent*)
    {
        ball->setPosX(std::sin(frame / 10.0));
        ball->setPosY(std::cos(frame / 10.0));
        ball->setDiam(ball->getDiam() + 1.0);

        car->speed += 0.1;
        car->speed *= 2.5;

        FrameData frameData = sender.getFrameData(frame);
        db()->update(frameData);
        sender.sendFrameData(frameData);

        peer->postEvent(new GameEvent());
        ++frame;

        if (frame == 10)
            quit();
    }

private:
    std::auto_ptr<HostObjectDB> m_db;

    framenum_t frame;
    GameDataSender sender;
    std::auto_ptr<MovingBall> ball;
    std::auto_ptr<HostBumperCar> car;


};



class MyPeer : public Peer
{
public:
    MyPeer()
    : Peer()
    , m_db(new PeerObjectDB())
    , frame(0)
    , receiver()
    , ball(new MovingBall(idBall))
    , car(new PeerBumperCar(idCar))
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());
    }


    PeerObjectDB* db() const
    {
        return m_db.get();
    }


protected:
    void handle(GameEvent*)
    {
        db()->apply(receiver.getFrameData(frame++));

        DEBUG << "Moving ball, frame " << frame << ": "
            << align(40) << "posx = " << ball->getPosX()
            << align(58) << "posy = " << ball->getPosY()
            << align(76) << "diam = " << ball->getDiam();

        DEBUG << "BumberCar now running at: " << car->speed;

        if (frame == 10)
            quit();
    }

private:
    std::auto_ptr<PeerObjectDB> m_db;

    framenum_t frame;
    GameDataReceiver receiver;
    std::auto_ptr<MovingBall> ball;
    std::auto_ptr<PeerBumperCar> car;

};


int main()
{
    host.reset(new MyHost);
    peer.reset(new MyPeer);

    ThreadRunningHost th;
    th.start();
    ThreadRunningPeer tp;
    tp.start();

    std::auto_ptr<Timer> repeating(new Timer(0, host->eventLoop()));
    repeating->setRepeating(true);
    repeating->start(500);

    th.join();
    tp.join();
}

