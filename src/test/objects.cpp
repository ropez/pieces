
#include "Pieces/Application"

#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/Message"
#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataSender"

#include "Pieces/EventLoop"
#include "Pieces/TimerEvent"
#include "Pieces/GameDataEvent"
#include "Pieces/MessageReceivedEvent"

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


enum ObjectType
{
    MOVING_BALL,
    BUMPER_CAR
};


enum ActionType
{
    NO_ACTION,

    UPDATE_ACTION,
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
        if (frameNum != m_ball->getFrameNumber())
            PWARNING << "Different frame numbers";

        PDEBUG << "Moving ball, frame " << frameNum << ": "
            << align(40) << "posx = " << m_ball->getPosX()
            << align(58) << "posy = " << m_ball->getPosY()
            << align(76) << "diam = " << m_ball->getDiam();
    }

private:
    MovingBall* m_ball;
};


class UpdateMovingBall : public GameObjectAction
{
public:
    UpdateMovingBall(MovingBall* ball)
    : GameObjectAction()
    , m_ball(ball)
    {
    }

    virtual void operator()(framenum_t frameNum)
    {
        m_ball->setPosX(std::sin(frameNum / 10.0));
        m_ball->setPosY(std::cos(frameNum / 10.0));
        m_ball->setDiam(m_ball->getDiam() + 1.0);
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


class UpdateBumperCar : public GameObjectAction
{
public:
    UpdateBumperCar(HostBumperCar* car)
    : GameObjectAction()
    , m_car(car)
    {
    }

    virtual void operator()(framenum_t)
    {
        m_car->speed += 0.1;
        m_car->speed *= 2.5;
    }

private:
    HostBumperCar* m_car;
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

    virtual void operator()(framenum_t frameNum)
    {
        if (frameNum != m_car->getFrameNumber())
            PWARNING << "Different frame numbers";

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
            ReferencePointer<MovingBall> ball = new MovingBall(idBall);
            ball->setAction(UPDATE_ACTION, new UpdateMovingBall(ball.get()));
            db()->insert(idBall, ball.get());

            sendCreateObject(idBall, MOVING_BALL);
        }

        m_timer = new Timer(0, eventLoop());
        m_timer->setRepeating(true);
        m_timer->start(500);
    }

protected:
    virtual void handle(TimerEvent*)
    {
        framenum_t frameNum = sender()->getFrameNumber();

        if (frameNum % 10 == 0)
        {
            switch (frameNum / 10 % 2)
            {
            case 0:
                {
                    ReferencePointer<HostBumperCar> car = new HostBumperCar(idCar);
                    car->setAction(UPDATE_ACTION, new UpdateBumperCar(car.get()));
                    db()->insert(idCar, car.get());

                    sendCreateObject(idCar, BUMPER_CAR);
                }
                break;
            case 1:
                {
                    sendRemoveObject(idCar);

                    db()->remove(idCar);
                }
                break;
            }
        }

        db()->applyAction(UPDATE_ACTION, frameNum);

        FrameData frameData;
        db()->updateFrameData(frameData);
        sender()->sendFrameData(frameData);
    }

    virtual void handle(MessageReceivedEvent* event)
    {
        Message message = event->getMessage();

        if (message.getMessageType() == GAMEDATA_CONNECT)
        {
            // TODO: Move this functionality to an internal event handler
            port_t port = message.get<port_t>(PR_PORT);

            SocketAddress addr(event->getSenderAddress().getInetAddress(), port);
            PINFO << "Adding " << addr << " to receivers list";
            sender()->addReceiver(addr);
        }
    }

private:
    AutoPointer<GameObjectDB> m_db;
    AutoPointer<Timer> m_timer;
};



class MyPeer : public Peer
{
public:
    MyPeer(port_t portData)
    : Peer()
    , m_data(10)
    , m_db(new GameObjectDB())
    {
        connectTo(SocketAddress(InetAddress::getHostByName("localhost"), portMessage));

        // Connect to data channel
        Message message(GAMEDATA_CONNECT);
        message.set(PR_PORT, portData);

        sendMessage(message);

        receiver()->listen(portData);
    }


    GameObjectDB* db() const
    {
        return m_db.get();
    }


protected:
    void handle(GameDataEvent* event)
    {
        framenum_t frameNum = event->getFrameNumber();

        FrameData frameData = event->getFrameData();
        m_data.setFrameData(event->getFrameNumber(), frameData);
        db()->applyFrameData(event->getFrameNumber(), frameData);
        db()->applyAction(DEBUG_ACTION, frameNum);
    }

    void handle(MessageReceivedEvent* event)
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
        else if (message.getMessageType() == OBJECT_REMOVE)
        {
            objectid_t objectId = message.get<objectid_t>(PR_OBJECT_ID);
            db()->remove(objectId);
        }
    }

private:
    GameData m_data;

    AutoPointer<GameObjectDB> m_db;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    try
    {
        if (app->argc() > 1 && app->arg(1) == "host")
        {
            AutoPointer<Host> host(new MyHost);
            host->startListening(portMessage);
            host->exec();
        }
        else
        {
            port_t portData = 3333;
            if (app->argc() > 1)
            {
                portData = atoi(app->arg(1).c_str());
            }

            AutoPointer<Peer> peer(new MyPeer(portData));
            peer->exec();
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

