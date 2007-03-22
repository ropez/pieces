
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
#include "Pieces/Datagram"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"

#include <map>
#include <set>
#include <cmath>


using namespace Pieces;
AutoPointer<Host> host;
AutoPointer<Peer> peer;


namespace Pieces
{

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
    d->socket = new UDPSocket;
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

    BufferStream bs;
    bs << d->frameNumber << frame;

    for (std::set<SocketAddress>::const_iterator it = d->receivers.begin(); it != d->receivers.end(); ++it)
    {
        Datagram dg(bs.data(), *it);
        d->socket->send(dg);
    }

    ++d->frameNumber;
}


class GameDataReceiverThreadPrivate;
class GameDataReceiverThread : public OpenThreads::Thread
{
public:
    GameDataReceiverThread(port_t port, GameData* buffer);
    ~GameDataReceiverThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(GameDataReceiverThread);

    GameDataReceiverThreadPrivate* d;
};

using namespace OpenThreads;

class GameDataReceiverThreadPrivate
{
public:
    GameDataReceiverThreadPrivate();

    Mutex mutex;

    AutoPointer<UDPSocket> socket;
    GameData* buffer;
};


GameDataReceiverThreadPrivate::GameDataReceiverThreadPrivate()
: socket(0)
, buffer(0)
{
}


GameDataReceiverThread::GameDataReceiverThread(port_t port, GameData* buffer)
: d(new GameDataReceiverThreadPrivate)
{
    d->socket = new UDPSocket;
    d->socket->bind(port);

    d->buffer = buffer;
}


GameDataReceiverThread::~GameDataReceiverThread()
{
    abort();
    delete d;
}


void GameDataReceiverThread::abort()
{
    ScopedLock<Mutex> lock(d->mutex);

    if (isRunning())
    {
        cancel();

        // Allow thread to exit
        ReverseScopedLock<Mutex> unlock(d->mutex);
        join();
    }
}


void GameDataReceiverThread::run()
{
    const size_t MAX_PACKET_SIZE = 0x1000;

    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        for (;;)
        {
            Datagram dg;
            {
                ReverseScopedLock<Mutex> unlock(d->mutex);

                dg = d->socket->receive(MAX_PACKET_SIZE);
            }

            BufferStream bs(dg.getData());

            framenum_t frameNum = 0;
            FrameData frame;
            bs >> frameNum >> frame;

            PDEBUG << "Got frame " << frameNum << " size = " << frame.size();
            d->buffer->setFrameData(frameNum, frame);

            // DUMMY: Trigger peer event
            peer->postEvent(new GameEvent(frameNum));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
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

    AutoPointer<GameDataReceiverThread> thread;

    GameData buffer;
};


GameDataReceiverPrivate::GameDataReceiverPrivate()
: thread(0)
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
        d->thread = new GameDataReceiverThread(port, &d->buffer);
        d->thread->start();
    }
    catch (const IOException& e)
    {
        PERROR << e.getMessage();
    }
}


FrameData GameDataReceiver::getFrameData(framenum_t frameNum)
{
    return d->buffer.getFrameData(frameNum);
}

} // namespace Pieces


// Demonstration


class ThreadRunningHost : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        host->exec();
    }
};

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

        ++frame;
    }

    virtual void handle(NetworkEvent* event)
    {
        try
        {
            BufferStream bf(event->getData());

            std::string str;
            bf >> str;
            PDEBUG << "From: " << event->getSenderAddress();
            PDEBUG << "Message type " << event->getMessageType();
            PDEBUG << "Data (as string): " << str;

            SocketAddress addr(event->getSenderAddress().getInetAddress(), 3333);
            PINFO << "Adding " << addr << " to receivers list";
            sender.addReceiver(addr);
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
    , receiver()
    , ball(new MovingBall(idBall))
    , car(new PeerBumperCar(idCar))
    , m_db(new GameObjectDB())
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());

        receiver.listen(3333);
    }


    GameObjectDB* db() const
    {
        return m_db.get();
    }


protected:
    void handle(GameEvent* event)
    {
        framenum_t frameNum = event->type();

        FrameData frame = receiver.getFrameData(frameNum);
        if (frame.isEmpty())
        {
            PWARNING << "Empty frame " << frameNum;
        }

        db()->apply(frame);

        PDEBUG << "Moving ball, frame " << frameNum << ": "
            << align(40) << "posx = " << ball->getPosX()
            << align(58) << "posy = " << ball->getPosY()
            << align(76) << "diam = " << ball->getDiam();

        PDEBUG << "BumberCar now running at: " << car->speed;

        if (frameNum >= 10)
            quit();
    }

private:

    GameDataReceiver receiver;
    ReferencePointer<MovingBall> ball;
    ReferencePointer<PeerBumperCar> car;

    AutoPointer<GameObjectDB> m_db;
};


int main(int argc, char** argv)
{
    if (argc > 1 && std::string(argv[1]) == "host")
    {
        host = new MyHost;
        ThreadRunningHost th;

        AutoPointer<Timer> repeating(new Timer(0, host->eventLoop()));
        repeating->setRepeating(true);
        repeating->start(500);

        host->connectionManager()->listen(2222);

        th.start();
        th.join();
    }
    else
    {
        peer = new MyPeer;
        ThreadRunningPeer tp;

        peer->connectionManager()->connectTo(SocketAddress(InetAddress::getHostByName("localhost"), 2222));

        // Say hello
        BufferStream s;
        s << "Follow the white rabbit";
        peer->connectionManager()->sendMessage(666, s.data());


        tp.start();
        tp.join();
    }
}

