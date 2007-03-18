
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/GameObject"
#include "Pieces/HostGameObject"
#include "Pieces/PeerGameObject"

#include "Pieces/FrameData"
#include "Pieces/GameData"

#include <map>
#include <cmath>

namespace Pieces
{

// DUMMY simulation of host and peer functionality
GameData gamedata;

class GameDataSender
{
public:
    typedef std::map<objectid_t, HostObjectIface*> object_map_t;
    object_map_t objects;

    GameDataSender()
    : frameNumber(0)
    {
    }

    void sendFrame()
    {
        // Frame data
        FrameData d = gamedata.getFrameData(frameNumber - 1);

        for (object_map_t::const_iterator it = objects.begin(); it != objects.end(); ++it)
        {
            objectid_t id = it->first;
            HostObjectIface* obj = it->second;

            // Object data
            BufferStream s;
            obj->encode(s);

            d.setObjectData(id, s.data());
        }

        // "send"
        gamedata.setFrameData(frameNumber++, d);
    }

private:
    framenum_t frameNumber;
};

class GameDataReceiver
{
public:
    typedef std::map<objectid_t, PeerObjectIface*> object_map_t;
    object_map_t objects;

    void recvFrame(framenum_t frameNum)
    {
        // Frame data
        FrameData d = gamedata.getFrameData(frameNum);

        for (object_map_t::const_iterator it = objects.begin(); it != objects.end(); ++it)
        {
            objectid_t id = it->first;
            PeerObjectIface* obj = it->second;

            // Object data
            BufferStream s(d.getObjectData(id));

            // NOTE: This might throw an IOException
            obj->decode(s);
        }
    }
};

} // namespace Pieces


// Demonstration

using namespace Pieces;


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



int main()
{
    const objectid_t idBall = 100;
    const objectid_t idCar = 200;

    // Generate data (this is the "host")
    {
        std::auto_ptr<MovingBall> ball(new MovingBall(idBall));
        std::auto_ptr<HostBumperCar> car(new HostBumperCar(idCar));

        GameDataSender sender;
        sender.objects[idBall] = ball.get();
        sender.objects[idCar] = car.get();

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            ball->setPosX(std::sin(frame / 10.0));
            ball->setPosY(std::cos(frame / 10.0));
            ball->setDiam(ball->getDiam() + 1.0);

            car->speed += 0.1;
            car->speed *= 2.5;

            sender.sendFrame();
        }
    }

    // Receive data (this is the "peer")
    {
        std::auto_ptr<MovingBall> ball(new MovingBall(idBall));
        std::auto_ptr<PeerBumperCar> car(new PeerBumperCar(idCar));

        GameDataReceiver receiver;
        receiver.objects[idBall] = ball.get();
        receiver.objects[idCar] = car.get();

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            receiver.recvFrame(frame);

            DEBUG << "Moving ball, frame " << frame << ": "
                << align(40) << "posx = " << ball->getPosX()
                << align(58) << "posy = " << ball->getPosY()
                << align(76) << "diam = " << ball->getDiam();

            DEBUG << "BumberCar now running at: " << car->speed;
        }
    }
}

