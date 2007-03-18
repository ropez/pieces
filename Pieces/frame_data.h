
#ifndef PIECES_FRAME_DATA_H
#define PIECES_FRAME_DATA_H

#include "Pieces/global"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"

#include <map>


namespace Pieces
{


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

    // TODO: Do we need an ObjectData class, or is ByteArray sufficient? (Robin)
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

} // namespace Pieces

#endif // PIECES_FRAME_DATA_H
