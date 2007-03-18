
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
    framenum_t getFrameNumber() const;

protected:

    virtual void encode(DataStream& ds) const = 0;
    virtual void decode(DataStream& ds) = 0;

//     virtual void handle(ObjectEvent* event);

private:
    // Disable copy operations
    GameObject(const GameObject&);
    GameObject& operator=(const GameObject&);

    void setFrameNumber(framenum_t number);

    objectid_t m_objectId;
    framenum_t m_frameNum;
};


GameObject::GameObject(objectid_t objectId)
: m_objectId(objectId)
, m_frameNum(0)
{
}


GameObject::~GameObject()
{
}


objectid_t GameObject::getObjectId() const
{
    return m_objectId;
}


framenum_t GameObject::getFrameNumber() const
{
    return m_frameNum;
}


void GameObject::setFrameNumber(framenum_t number)
{
    m_frameNum = number;
}



// DUMMY simulation of host and peer functionality
ValueList frames;

class GameDataSender
{
public:

    void sendFrame(GameObject& obj)
    {
        BufferStream s;
        obj.encode(s);

        frames.addValue(s.data());
    }
};

class GameDataReceiver
{
public:

    void recvFrame(int number, GameObject& obj)
    {
        BufferStream s(frames.getValue(number));
        obj.decode(s);
        obj.setFrameNumber(number);
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

        for (int i = 0; i < 10; ++i)
        {
            ball.setPosX(std::sin(i / 10.0));
            ball.setPosY(std::cos(i / 10.0));
            ball.setDiam(ball.getDiam() + 1.0);

            sender.sendFrame(ball);
        }
    }

    // Receive data (this is the "peer")
    {
        GameDataReceiver receiver;
        MovingBall ball(100);

        for (int i = 0; i < 10; ++i)
        {
            receiver.recvFrame(i, ball);
            DEBUG << "Moving ball, frame " << ball.getFrameNumber() << ": "
                << align(40) << "posx = " << ball.getPosX()
                << align(58) << "posy = " << ball.getPosY()
                << align(76) << "diam = " << ball.getDiam();
        }
    }
}

