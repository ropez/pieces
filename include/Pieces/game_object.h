
#ifndef PIECES_GAME_OBJECT_H
#define PIECES_GAME_OBJECT_H

#include "Pieces/global"
#include "Pieces/Object"

#include "Pieces/SharedData"

namespace Pieces
{
class DataStream;
class FrameData;


class GameObjectAction : public SharedData
{
public:
    virtual ~GameObjectAction() {};

    virtual void operator()(framenum_t frameNum) = 0;
};

class GameObjectPrivate;

/**
 * \class GameObject
 * \brief Base class for objects defined for both host and peer.
 *
 * This is a base class that game programmers can subclass to create game
 * specific object classes.
 *
 * Subclasses can be defined for use in a host, a peer or both.
 *
 * If a subclass should be used in a host, the encode() function should be
 * reimplemented to encode an object onto a data-stream.
 *
 * If a subclass should be used in a peer, the decode() function should be
 * reimplemented to decode an object, reading from a data-stream.
 *
 * \author Robin Pedersen
 */
class GameObject : public Object
{
public:
    GameObject(objectid_t objectId);
    virtual ~GameObject();

    virtual void encode(DataStream& ds) const;

    virtual void decode(DataStream& ds);

    /**
     * Custom user action.
     */
    void setAction(int actionType, GameObjectAction* action);

    void applyAction(int actionType, framenum_t frameNum);

    /**
     * Call encode(), and insert the resulting data into \a frame.
     */
    void update(FrameData& frame) const;

    /**
     * Extract object data for this object from \a frame, and call decode().
     */
    void apply(const FrameData& frame);

private:
    DISABLE_COPY(GameObject);

    GameObjectPrivate* d;
};

} // namespace Pieces

#endif // PIECES_GAME_OBJECT_H
