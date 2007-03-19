
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/IOException"

#include "Pieces/Host"
#include "Pieces/Peer"

#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"

#include "Pieces/Timer"

#include "Pieces/GameObject"
#include "Pieces/ReferencePointer"

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
 * \class GameObjectDB
 *
 *
 * \author Robin Pedersen
 */
class GameObjectDB
{
public:
    typedef ReferencePointer<GameObject> ptr_t;
    typedef std::map<objectid_t, ptr_t> map_t;

    GameObjectDB();
    ~GameObjectDB();

    void clear();

    /**
     * Returns a pointer to the object replaced, or 0 if no object was replaced.
     */
    ptr_t insert(objectid_t objectId, GameObject* obj);

    ptr_t remove(objectid_t objectId);
    ptr_t remove(map_t::iterator it);

    void update(FrameData& frame) const;
    void apply(const FrameData& frame);

    map_t::iterator begin();
    map_t::iterator end();

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

private:
    // Disable copy operations
    GameObjectDB(const GameObjectDB&);
    GameObjectDB& operator=(const GameObjectDB&);

    map_t m_objects;
};



GameObjectDB::GameObjectDB()
: m_objects()
{
}


GameObjectDB::~GameObjectDB()
{
}


void GameObjectDB::clear()
{
    m_objects.clear();
}


GameObjectDB::ptr_t GameObjectDB::insert(objectid_t objectId, GameObject* obj)
{
    ptr_t tmp = remove(objectId);
    m_objects[objectId] = obj;
    return tmp;
}


GameObjectDB::ptr_t GameObjectDB::remove(objectid_t objectId)
{
    map_t::iterator it = m_objects.find(objectId);

    return remove(it);
}


GameObjectDB::ptr_t GameObjectDB::remove(map_t::iterator it)
{
    if (it != end())
    {
        ptr_t tmp = it->second;
        m_objects.erase(it);
        return tmp;
    }
    return 0;
}


void GameObjectDB::update(FrameData& frame) const
{
    for (map_t::const_iterator it = begin(); it != end(); ++it)
    {
        objectid_t id = it->first;
        const ptr_t obj = it->second;

        // Object data
        BufferStream s;
        obj->encode(s);

        frame.setObjectData(id, s.data());
    }
}


void GameObjectDB::apply(const FrameData& frame)
{
    for (map_t::iterator it = begin(); it != end(); ++it)
    {
        objectid_t id = it->first;
        ptr_t obj = it->second;

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


GameObjectDB::map_t::iterator GameObjectDB::begin()
{
    return m_objects.begin();
}


GameObjectDB::map_t::iterator GameObjectDB::end()
{
    return m_objects.end();
}


GameObjectDB::map_t::const_iterator GameObjectDB::begin() const
{
    return m_objects.begin();
}


GameObjectDB::map_t::const_iterator GameObjectDB::end() const
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
 * Test implementation of host-specific GameObject
 */
class HostBumperCar : public GameObject
{
public:
    HostBumperCar(objectid_t objectId)
    : GameObject(objectId)
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
 * Test implementation of peer-specific GameObject
 */
class PeerBumperCar : public GameObject
{
public:
    PeerBumperCar(objectid_t objectId)
    : GameObject(objectId)
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
    , m_db(new GameObjectDB())
    , frame(0)
    , sender()
    , ball(new MovingBall(idBall))
    , car(new HostBumperCar(idCar))
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());
    }

    GameObjectDB* db() const
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
    std::auto_ptr<GameObjectDB> m_db;

    framenum_t frame;
    GameDataSender sender;
    ReferencePointer<MovingBall> ball;
    ReferencePointer<HostBumperCar> car;
};



class MyPeer : public Peer
{
public:
    MyPeer()
    : Peer()
    , frame(0)
    , receiver()
    , ball(new MovingBall(idBall))
    , car(new PeerBumperCar(idCar))
    , m_db(new GameObjectDB())
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());
    }


    GameObjectDB* db() const
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

    framenum_t frame;
    GameDataReceiver receiver;
    ReferencePointer<MovingBall> ball;
    ReferencePointer<PeerBumperCar> car;

    std::auto_ptr<GameObjectDB> m_db;
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

