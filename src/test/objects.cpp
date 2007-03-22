
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

#include "Pieces/UDPSocket"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"

#include <map>
#include <set>
#include <cmath>

namespace Pieces
{

// DUMMY simulation of host and peer "UDP" functionality
OpenThreads::Mutex mutex;
GameData gamedata;


class GameDataSenderPrivate;
class GameDataSender
{
public:
    GameDataSender();
    ~GameDataSender();

    void addReceiver(const SocketAddress& socket);
    void removeReceiver(const SocketAddress& socket);

    FrameData getFrameData(framenum_t frameNum) const;

    void sendFrameData(const FrameData& frame);

private:
    DISABLE_COPY(GameDataSender);

    GameDataSenderPrivate* d;
};


class GameDataSenderPrivate
{
public:
    GameDataSenderPrivate();

    AutoPointer<UDPSocket> socket;
    std::set<SocketAddress> receivers;

    framenum_t frameNumber;
    GameData buffer;
};


GameDataSenderPrivate::GameDataSenderPrivate()
: socket(0)
, frameNumber(0)
, buffer()
{
}


GameDataSender::GameDataSender()
: d(new GameDataSenderPrivate)
{
}


GameDataSender::~GameDataSender()
{
    delete d;
}


void GameDataSender::addReceiver(const SocketAddress& address)
{
    d->receivers.insert(address);
}


void GameDataSender::removeReceiver(const SocketAddress& address)
{
    d->receivers.erase(address);
}


FrameData GameDataSender::getFrameData(framenum_t frameNum) const
{
    return d->buffer.getFrameData(frameNum);
}


void GameDataSender::sendFrameData(const FrameData& frame)
{
    d->buffer.setFrameData(d->frameNumber, frame);

    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
    gamedata.setFrameData(d->frameNumber++, frame);
}


class GameDataReceiverPrivate;
class GameDataReceiver
{
public:
    GameDataReceiver();
    ~GameDataReceiver();

    void listen(port_t port);

    FrameData getFrameData(framenum_t frameNum);

private:
    DISABLE_COPY(GameDataReceiver);

    GameDataReceiverPrivate* d;
};


class GameDataReceiverPrivate
{
public:
    GameDataReceiverPrivate();

    AutoPointer<UDPSocket> socket;

    GameData buffer;
};


GameDataReceiverPrivate::GameDataReceiverPrivate()
: socket(0)
, buffer()
{
}


GameDataReceiver::GameDataReceiver()
: d(new GameDataReceiverPrivate)
{
}


GameDataReceiver::~GameDataReceiver()
{
    delete d;
}


void GameDataReceiver::listen(port_t port)
{
    try
    {
        AutoPointer<UDPSocket> tmp(new UDPSocket());
        tmp->bind(port);

        d->socket = tmp;
    }
    catch (const IOException& e)
    {
        PERROR << e.getMessage();
    }
}


FrameData GameDataReceiver::getFrameData(framenum_t frameNum)
{
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
    return gamedata.getFrameData(frameNum);
}

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
        PDEBUG << "Got network event, type " << event->type();

        try
        {
            BufferStream bf(event->getData());

            std::string str;
            bf >> str;
            PDEBUG << "From: " << event->getSenderAddress();
            PDEBUG << "Data (as string): " << str;
        }
        catch (const IOException& e)
        {
            PWARNING << e;
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
            PDEBUG << "go == ball";
        }
        if (go == car)
        {
            PDEBUG << "go == car";
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

        PDEBUG << "Moving ball, frame " << frame << ": "
            << align(40) << "posx = " << ball->getPosX()
            << align(58) << "posy = " << ball->getPosY()
            << align(76) << "diam = " << ball->getDiam();

        PDEBUG << "BumberCar now running at: " << car->speed;

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

