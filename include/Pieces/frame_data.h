
#ifndef PIECES_FRAME_DATA_H
#define PIECES_FRAME_DATA_H

#include "Pieces/global"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"

#include <map>


namespace pcs
{
class DataStream;


/**
 * \class FrameData frame_data.h <Pieces/FrameData>
 * \brief Contains game data for one single frame.
 *
 * This class represents a collection of data for all game objects in a single
 * frame. It is used by the game data system (see GameDataSender and
 * GameDataReceiver) as the basic data container.
 *
 * Data is represented as a ByteArray for each game object, indexed by
 * \link GameObject::getObjectId() object id \endlink.
 *
 * Frame data is usually created in the host user application. It starts with a
 * FrameData object that is either empty or contains data from the previous
 * frame. Then is calls \link GameObject::updateFrameData updateFrameData() \endlink
 * on all game object before sending the data to the peers by calling
 * \link GameDataSender::sendFrameData sender()->sendFrameData() \endlink in the
 * Host instance. For convenience, the game objects can be stored in a GameObjectDB,
 * to make it easier to call the update fucntion in all objects. The update function
 * then calls \link GameObject::encode encode() \endlink which should be implemented
 * by the user to encode the object's member variables.
 *
 * The frame data is then sent to all connected peers, which will get a
 * GameDataEvent that contains the frame data and a frame number. The peer then
 * typically calls \link GameObject::applyFrameData applyFrameData() \endlink on
 * all game objects, which calls \link GameObject::decode decode() \endlink that
 * the user should implement to update the object's member variables.
 *
 * Frame data can be buffered in either host or peer application using a GameData
 * container.
 *
 * This class uses \ref implicit_sharing.
 *
 * \author Robin Pedersen
 */
class FrameData
{
public:

    /**
     * Map type used internally to index data.
     */
    typedef std::map<objectid_t, ByteArray> map_t;

    /**
     * Pair type used by the internal map.
     */
    typedef map_t::value_type pair_t;

    /**
     * Create an empty data container.
     */
    FrameData();

    /**
     * Returns the number of objects the frame data object contains encoded
     * data for.
     */
    size_t size() const;

    /**
     * Returns true if size() == 0.
     */
    bool isEmpty() const;

    /**
     * Returns a start iterator that can be used to loop through all data.
     */
    map_t::const_iterator begin() const;

    /**
     * Returns an end iterator that can be used to loop through all data.
     */
    map_t::const_iterator end() const;

    /**
     * Returns true if it has data for the given object id.
     */
    bool hasObjectData(objectid_t objectId) const;

    /**
     * Returns the data for the given object id.
     */
    ByteArray getObjectData(objectid_t objectId) const;

    /**
     * Remove all data.
     */
    void clear();

    /**
     * Remove data for a specific object.
     */
    bool removeObjectData(objectid_t objectId);

    /**
     * Insert or replace data for a given object.
     */
    void setObjectData(objectid_t objectId, const ByteArray& data);

private:

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

/**
 * Write the frame data \a fd to the data stream \a ds.
 *
 * \relates FrameData
 */
DataStream& operator<<(DataStream& ds, const FrameData& fd);

/**
 * Read the frame data \a fd from the data stream \a ds.
 *
 * \relates FrameData
 */
DataStream& operator>>(DataStream& ds, FrameData& fd);

} // namespace pcs

#endif // PIECES_FRAME_DATA_H
