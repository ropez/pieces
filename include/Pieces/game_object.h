
#ifndef PIECES_GAME_OBJECT_H
#define PIECES_GAME_OBJECT_H

#include "Pieces/global"
#include "Pieces/Object"


namespace pcs
{
class DataStream;
class FrameData;
class GameObjectAction;
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

    /**
     * Creates a game object with the given \a objectId.
     */
    GameObject(objectid_t objectId);

    /**
     * Virtual destructor to make sure objects are correctly deleted.
     *
     * When using reference pointers, it's normally never necessary to delete
     * an object manually.
     */
    virtual ~GameObject();

    /**
     * Get the frame number of the data applied to this object.
     */
    framenum_t getFrameNumber() const;

    /**
     * Encode object state onto the data stream.
     *
     * This function must be reimplemented in game object classes used in a
     * host process to make it possible to transfer object data to peers.
     *
     * The implementation must be compatible with the corresponding decode()
     * function.
     *
     * The default implementation does nothing.
     */
    virtual void encode(DataStream& ds) const;

    /**
     * Decode object state from a data stream.
     *
     * This function must be reimplemented in game object classes used in a
     * peer process to make it possible to use object data transferred from
     * the host.
     *
     * The implementation must be compatible with the corresponding encode()
     * function.
     *
     * The default implementation does nothing.
     */
    virtual void decode(DataStream& ds);

    /**
     * Call encode(), and insert the resulting data into \a frameData.
     */
    void updateFrameData(FrameData& frameData) const;

    /**
     * Extract object data for this object from \a frameData, and call decode().
     *
     * If data for this object is found, and the operation succeeds,
     * getFrameNumber() will return \a frameNum afterwards.
     */
    void applyFrameData(framenum_t frameNum, const FrameData& frameData);

    /**
     * Custom user action.
     *
     * This function adds a reference to the \a action object. If the reference
     * counter becomes 0 when the function is replaced or the game object
     * deleted, the action function is deleted.
     *
     * The \a action function should not contain a reference pointer to this
     * game object, but a normal pointer is OK.
     */
    void setAction(int actionType, GameObjectAction* action);

    /**
     * Call the action function assiciated with this object for the given
     * \a actionType.
     *
     * If no action is set for this action-type, it throws an InvalidKeyException.
     * If a null-pointer is set for this action, this function does nothing.
     */
    void applyAction(int actionType, framenum_t frameNum);

private:
    DISABLE_COPY(GameObject);

    GameObjectPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_OBJECT_H
