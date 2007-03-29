
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/IOException"

#include "Pieces/Application"

#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/ConnectionManager"
#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataSender"

#include "Pieces/EventLoop"
#include "Pieces/TimerEvent"
#include "Pieces/GameDataEvent"
#include "Pieces/NetworkEvent"

#include "Pieces/Timer"

#include "Pieces/GameObject"
#include "Pieces/GameObjectDB"
#include "Pieces/ReferencePointer"

#include "Pieces/FrameData"
#include "Pieces/GameData"

#include "OpenThreads/Thread"

#include <map>
#include <cmath>


using namespace Pieces;
AutoPointer<Host> host;
AutoPointer<Peer> peer;


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

            // TODO: Replace this by a special message from the peer to the host, handled by pieces that tells the host to start sending data to a port selected by the peer.
            // To be able to implement features like this, we must handle all events on an internal event handler before they are sent to the user application.
            // I suggest adding a internal event handler class to both Peer and Host classes.
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
    , receiver(new GameDataReceiver(eventLoop()))
    , ball(new MovingBall(idBall))
    , car(new PeerBumperCar(idCar))
    , m_db(new GameObjectDB())
    {
        db()->insert(idBall, ball.get());
        db()->insert(idCar, car.get());

        receiver->listen(3333);
    }


    GameObjectDB* db() const
    {
        return m_db.get();
    }


protected:
    void handle(GameDataEvent* event)
    {
        framenum_t frameNum = event->getFrameNumber();

        FrameData frame = event->getFrameData();
        db()->apply(frame);

        PDEBUG << "Moving ball, frame " << frameNum << ": "
            << align(40) << "posx = " << ball->getPosX()
            << align(58) << "posy = " << ball->getPosY()
            << align(76) << "diam = " << ball->getDiam();

        PDEBUG << "BumberCar now running at: " << car->speed;
    }

private:

    AutoPointer<GameDataReceiver> receiver;
    ReferencePointer<MovingBall> ball;
    ReferencePointer<PeerBumperCar> car;

    AutoPointer<GameObjectDB> m_db;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    if (app->argc() > 1 && app->arg(1) == "host")
    {
        host = new MyHost;

        AutoPointer<Timer> repeating(new Timer(0, host->eventLoop()));
        repeating->setRepeating(true);
        repeating->start(500);

        host->connectionManager()->listen(2222);

        host->exec();
    }
    else
    {
        peer = new MyPeer;

        peer->connectionManager()->connectTo(SocketAddress(InetAddress::getHostByName("localhost"), 2222));

        // Say hello
        BufferStream s;
        s << "Follow the white rabbit";
        peer->connectionManager()->sendMessage(666, s.data());

        peer->exec();
    }
}

