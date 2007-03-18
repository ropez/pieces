
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ValueList"
#include "Pieces/PropertyList"
#include "Pieces/BufferStream"
#include "Pieces/Debug"


#include <map>
#include <cmath>

namespace Pieces
{
class GameDataSender;
class GameDataReceiver;

// NOTE: We could also use Universally unique identifiers (e.g. 550e8400-e29b-41d4-a716-446655440000). They take 16 bytes, I have the code we need. (Robin)
typedef unsigned long objectid_t;

// NOTE: Using 32-bit frame number is enough for about 118 weeks, with 60 frames per second. Enough?
typedef unsigned long framenum_t;


class GameObject
{
    friend class GameDataSender;
    friend class GameDataReceiver;

public:
    GameObject(objectid_t objectId);
    virtual ~GameObject();

    objectid_t getObjectId() const;

protected:

    virtual void encode(DataStream& ds) const = 0;
    virtual void decode(DataStream& ds) = 0;

//     virtual void handle(ObjectEvent* event);

private:
    // Disable copy operations
    GameObject(const GameObject&);
    GameObject& operator=(const GameObject&);

    objectid_t m_objectId;
};


GameObject::GameObject(objectid_t objectId)
: m_objectId(objectId)
{
}


GameObject::~GameObject()
{
}


objectid_t GameObject::getObjectId() const
{
    return m_objectId;
}




/**
 * \class FrameData
 * \brief Contains game data for one single frame.
 *
 * Implicitly shared class that contains data for all game objects, for a
 * sequence of frames.
 *
 * \author Robin Pedersen
 */
class FrameData
{
public:
    FrameData();

    bool hasObjectData(objectid_t objectId) const;
    ByteArray getObjectData(objectid_t objectId) const;

    bool removeObjectData(objectid_t objectId);
    void setObjectData(objectid_t objectId, const ByteArray& data);

private:

    // TODO: Do we need an ObjectData class, or is ByteArray sufficiant? (Robin)
    typedef std::map<objectid_t, ByteArray> map_t;

    class Data : public SharedData
    {
    public:
        Data();

        Data(const Data& other);
        Data& operator=(const Data& other);

        map_t objectData;
    };

    SharedDataPointer<Data> d;
};


FrameData::FrameData()
: d(new Data)
{
}


bool FrameData::hasObjectData(objectid_t objectId) const
{
    map_t::const_iterator it = d->objectData.find(objectId);

    return (it != d->objectData.end());
}


ByteArray FrameData::getObjectData(objectid_t objectId) const
{
    map_t::const_iterator it = d->objectData.find(objectId);

    if (it == d->objectData.end())
        return ByteArray();

    return it->second;
}


bool FrameData::removeObjectData(objectid_t objectId)
{
    map_t::iterator it = d->objectData.find(objectId);

    if (it == d->objectData.end())
        return false;

    d->objectData.erase(it);
    return true;
}


void FrameData::setObjectData(objectid_t objectId, const ByteArray& data)
{
    d->objectData[objectId] = data;
}


FrameData::Data::Data()
: SharedData()
, objectData()
{
}


FrameData::Data::Data(const Data& other)
: SharedData()
, objectData(other.objectData)
{
}


FrameData::Data& FrameData::Data::operator=(const Data& other)
{
    objectData = other.objectData;
    return *this;
}


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
    GameDataSender()
    : frameNumber(0)
    {
    }

    void sendFrame(GameObject& obj)
    {
        // Object data
        BufferStream s;
        obj.encode(s);

        // Frame data
        FrameData d = gamedata.getFrameData(frameNumber - 1);
        d.setObjectData(obj.getObjectId(), s.data());

        // "send"
        gamedata.setFrameData(frameNumber++, d);
    }

private:
    framenum_t frameNumber;
};

class GameDataReceiver
{
public:

    void recvFrame(framenum_t frameNum, GameObject& obj)
    {
        // Frame data
        FrameData d = gamedata.getFrameData(frameNum);

        // Object data
        BufferStream s(d.getObjectData(obj.getObjectId()));

        // NOTE: This might throw an IOException
        obj.decode(s);
    }
};

} // namespace Pieces


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
    // Generate data (this is the "host")
    {
        GameDataSender sender;
        MovingBall ball(100);

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            ball.setPosX(std::sin(frame / 10.0));
            ball.setPosY(std::cos(frame / 10.0));
            ball.setDiam(ball.getDiam() + 1.0);

            sender.sendFrame(ball);
        }
    }

    // Receive data (this is the "peer")
    {
        GameDataReceiver receiver;
        MovingBall ball(100);

        for (framenum_t frame = 0; frame < 10; ++frame)
        {
            receiver.recvFrame(frame, ball);
            DEBUG << "Moving ball, frame " << frame << ": "
                << align(40) << "posx = " << ball.getPosX()
                << align(58) << "posy = " << ball.getPosY()
                << align(76) << "diam = " << ball.getDiam();
        }
    }
}

