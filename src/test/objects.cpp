
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/IOException"

#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/ConnectionManager"

#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/NetworkEvent"

#include "Pieces/Timer"

#include "Pieces/GameObject"
#include "Pieces/GameObjectDB"
#include "Pieces/ReferencePointer"

#include "Pieces/FrameData"
#include "Pieces/GameData"

#include "Pieces/TCPSocket"
#include "Pieces/TCPServer"
#include "Pieces/TCPReceiverThread"
#include "Pieces/TCPListenerThread"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"

#include <map>
#include <cmath>

namespace Pieces
{

// DUMMY simulation of host and peer "UDP" functionality
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

} // namespace Pieces


// Demonstration

using namespace Pieces;

AutoPointer<Host> host;

class ThreadRunningHost : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        host->exec();
    }
};

AutoPointer<Peer> peer;

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

    GameObjectDB* db()
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

    virtual void handle(NetworkEvent* event)
    {
        DEBUG << "Got network event, type " << event->type();

        try
        {
            BufferStream bf(event->data());

            std::string str;
            bf >> str;
            DEBUG << "From: " << event->getSenderAddress();
            DEBUG << "Data (as string): " << str;
        }
        catch (const IOException& e)
        {
            WARNING << e;
        }
    }

private:
    AutoPointer<GameObjectDB> m_db;

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

        // Test operator
        ReferencePointer<GameObject> go = ball;

        // Test operator
        if (go == ball)
        {
            DEBUG << "go == ball";
        }
        if (go == car)
        {
            DEBUG << "go == car";
        }
        // if (ball == car) -- illegal (distinct pointer types)
        // if (ball.get() == car.get()) -- also illegal
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

    AutoPointer<GameObjectDB> m_db;
};


int main()
{
    host = new MyHost;
    peer = new MyPeer;

    ThreadRunningHost th;
    th.start();
    ThreadRunningPeer tp;
    tp.start();

    AutoPointer<Timer> repeating(new Timer(0, host->eventLoop()));
    repeating->setRepeating(true);
    repeating->start(500);

    host->connectionManager()->listen(2222);

    th.join();
    tp.join();
}

