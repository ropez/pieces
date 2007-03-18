
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ValueList"
#include "Pieces/PropertyList"
#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include "Pieces/GameObject"
#include "Pieces/FrameData"

#include <map>
#include <cmath>

namespace Pieces
{



/**
 * \class GameData
 * \brief Contains all the data for all the game objects in one place.
 *
 * Implicitly shared class that contains data for all game objects, for a
 * sequence of frames.
 *
 * \author Robin Pedersen
 */
class GameData
{
public:
    GameData();

    bool hasFrameData(framenum_t frameNum) const;
    FrameData getFrameData(framenum_t frameNum) const;

    bool removeFrameData(framenum_t frameNum);
    void setFrameData(framenum_t frameNum, const FrameData& data);

private:
    typedef std::map<framenum_t, FrameData> map_t;

    class Data : public SharedData
    {
    public:
        Data();

        Data(const Data& other);
        Data& operator=(const Data& other);

        map_t frameData;
    };

    SharedDataPointer<Data> d;
};


GameData::GameData()
: d(new Data)
{
}


bool GameData::hasFrameData(framenum_t frameNum) const
{
    map_t::const_iterator it = d->frameData.find(frameNum);

    return (it != d->frameData.end());
}


FrameData GameData::getFrameData(framenum_t frameNum) const
{
    map_t::const_iterator it = d->frameData.find(frameNum);

    if (it == d->frameData.end())
        return FrameData();

    return it->second;
}


bool GameData::removeFrameData(framenum_t frameNum)
{
    map_t::iterator it = d->frameData.find(frameNum);

    if (it == d->frameData.end())
        return false;

    d->frameData.erase(it);
    return true;
}


void GameData::setFrameData(framenum_t frameNum, const FrameData& data)
{
    d->frameData[frameNum] = data;
}


GameData::Data::Data()
: SharedData()
, frameData()
{
}


GameData::Data::Data(const Data& other)
: SharedData()
, frameData(other.frameData)
{
}


GameData::Data& GameData::Data::operator=(const Data& other)
{
    frameData = other.frameData;
    return *this;
}




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





int main()
{
    objectid_t id = 100;

    // Generate data (this is the "host")
    {
        std::auto_ptr<MovingBall> ball(new MovingBall(id));

        GameDataSender sender;
        sender.objects[id] = ball.get();

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            ball->setPosX(std::sin(frame / 10.0));
            ball->setPosY(std::cos(frame / 10.0));
            ball->setDiam(ball->getDiam() + 1.0);

            sender.sendFrame();
        }
    }

    // Receive data (this is the "peer")
    {
        std::auto_ptr<MovingBall> ball(new MovingBall(id));

        GameDataReceiver receiver;
        receiver.objects[id] = ball.get();

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            receiver.recvFrame(frame);

            DEBUG << "Moving ball, frame " << frame << ": "
                << align(40) << "posx = " << ball->getPosX()
                << align(58) << "posy = " << ball->getPosY()
                << align(76) << "diam = " << ball->getDiam();
        }
    }
}

