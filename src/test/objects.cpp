
#include "Pieces/Application"

#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/ConnectionManager"
#include "Pieces/Message"
#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataSender"

#include "Pieces/EventLoop"
#include "Pieces/TimerEvent"
#include "Pieces/GameDataEvent"
#include "Pieces/NetworkEvent"

#include "Pieces/Timer"

#include "Pieces/GameObject"
#include "Pieces/GameObjectDB"
#include "Pieces/GameObjectAction"
#include "Pieces/ReferencePointer"

#include "Pieces/FrameData"
#include "Pieces/GameData"

#include "OpenThreads/Thread"

#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/IOException"
#include "Pieces/InvalidKeyException"

#include <map>
#include <cmath>


using namespace Pieces;
AutoPointer<Host> host;
AutoPointer<Peer> peer;


enum ObjectType
{
    MOVING_BALL,
    BUMPER_CAR
};


enum ActionType
{
    NO_ACTION,

    DEBUG_ACTION
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
        PDEBUG << "Created MovingBall, id = " << getObjectId();
    }


    ~MovingBall()
    {
        PDEBUG << "Deleted MovingBall, id = " << getObjectId();
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


class DebugMovingBall : public GameObjectAction
{
public:
    DebugMovingBall(MovingBall* ball)
    : GameObjectAction()
    , m_ball(ball)
    {
    }

    virtual void operator()(framenum_t frameNum)
    {
        PDEBUG << "Moving ball, frame " << frameNum << ": "
            << align(40) << "posx = " << m_ball->getPosX()
            << align(58) << "posy = " << m_ball->getPosY()
            << align(76) << "diam = " << m_ball->getDiam();
    }

private:
    MovingBall* m_ball;
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
        PDEBUG << "Created HostBumperCar, id = " << getObjectId();
    }

    ~HostBumperCar()
    {
        PDEBUG << "Deleted HostBumperCar, id = " << getObjectId();
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
        PDEBUG << "Created PeerBumperCar, id = " << getObjectId();
    }

    ~PeerBumperCar()
    {
        PDEBUG << "Deleted PeerBumperCar, id = " << getObjectId();
    }


    virtual void decode(DataStream& ds)
    {
        ds >> speed;
    }

    double speed;
};


class DebugBumperCar : public GameObjectAction
{
public:
    DebugBumperCar(PeerBumperCar* car)
    : GameObjectAction()
    , m_car(car)
    {
    }

    virtual void operator()(framenum_t)
    {
        PDEBUG << "BumberCar now running at: " << m_car->speed;
    }

private:
    PeerBumperCar* m_car;
};


const port_t portMessage = 2222;

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
    , ball(0)
    , car(0)
    , m_timer(0)
    {
        startGame();
    }

    GameObjectDB* db()
    {
        return m_db.get();
    }

    void startGame()
    {
        {
            ball = new MovingBall(idBall);
            db()->insert(idBall, ball.get());

            Message message(OBJECT_CREATE);
            message.set(PR_OBJECT_TYPE, MOVING_BALL);
            message.set(PR_OBJECT_ID, idBall);

            connectionManager()->sendMessage(message);
        }

        {
            car = new HostBumperCar(idCar);
            db()->insert(idCar, car.get());

            Message message(OBJECT_CREATE);
            message.set(PR_OBJECT_TYPE, BUMPER_CAR);
            message.set(PR_OBJECT_ID, idCar);

            connectionManager()->sendMessage(message);
        }

        m_timer = new Timer(0, eventLoop());
        m_timer->setRepeating(true);
        m_timer->start(500);
    }

protected:
    virtual void handle(TimerEvent*)
    {
        ball->setPosX(std::sin(frame / 10.0));
        ball->setPosY(std::cos(frame / 10.0));
        ball->setDiam(ball->getDiam() + 1.0);

        car->speed += 0.1;
        car->speed *= 2.5;

        FrameData frameData;
        try
        {
            frameData = sender.getFrameData(frame);
        }
        catch (const InvalidKeyException&)
        {
            frameData = FrameData();
        }

        db()->update(frameData);
        sender.sendFrameData(frameData);

        ++frame;
    }

    virtual void handle(NetworkEvent* event)
    {
        if (event->type() == NetworkEvent::RECEIVED_MESSAGE)
        {
            Message message = event->getMessage();

            if (message.getMessageType() == GAMEDATA_CONNECT)
            {
                // TODO: Move this functionality to an internal event handler
                port_t port = message.get<port_t>(PR_PORT);

                SocketAddress addr(event->getSenderAddress().getInetAddress(), port);
                PINFO << "Adding " << addr << " to receivers list";
                sender.addReceiver(addr);
            }
        }
    }

private:
    AutoPointer<GameObjectDB> m_db;

    framenum_t frame;
    GameDataSender sender;
    ReferencePointer<MovingBall> ball;
    ReferencePointer<HostBumperCar> car;

    AutoPointer<Timer> m_timer;
};



class MyPeer : public Peer
{
public:
    MyPeer()
    : Peer()
    , receiver(new GameDataReceiver(eventLoop()))
    , m_db(new GameObjectDB())
    {
        connectTo(SocketAddress(InetAddress::getHostByName("localhost"), portMessage));

        // Connect to data channel
        const port_t portData = 3333;

        Message message(GAMEDATA_CONNECT);
        message.set(PR_PORT, portData);

        connectionManager()->sendMessage(message);

        receiver->listen(portData);
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

        for (GameObjectDB::map_t::iterator it = db()->begin(); it != db()->end(); ++it)
        {
            it->second->applyAction(DEBUG_ACTION, frameNum);
        }
    }

    void handle(NetworkEvent* event)
    {
        if (event->type() == NetworkEvent::RECEIVED_MESSAGE)
        {
            Message message = event->getMessage();

            if (message.getMessageType() == OBJECT_CREATE)
            {
                int objectType = message.get<int>(PR_OBJECT_TYPE);
                objectid_t objectId = message.get<objectid_t>(PR_OBJECT_ID);

                switch (objectType)
                {
                case MOVING_BALL:
                    {
                        ReferencePointer<MovingBall> ball = new MovingBall(objectId);
                        ball->setAction(DEBUG_ACTION, new DebugMovingBall(ball.get()));
                        db()->insert(objectId, ball.get());
                    }
                    break;
                case BUMPER_CAR:
                    {
                        ReferencePointer<PeerBumperCar> car = new PeerBumperCar(objectId);
                        car->setAction(DEBUG_ACTION, new DebugBumperCar(car.get()));
                        db()->insert(objectId, car.get());
                    }
                    break;
                default:
                    PWARNING << "Unknown object type: " << objectType;
                    return;
                }
            }
        }
    }

private:

    AutoPointer<GameDataReceiver> receiver;
    AutoPointer<GameObjectDB> m_db;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    try
    {
        if (app->argc() > 1 && app->arg(1) == "host")
        {
            host = new MyHost;
            host->startListening(portMessage);
            host->exec();
        }
        else
        {
            peer = new MyPeer;
            peer->exec();
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

