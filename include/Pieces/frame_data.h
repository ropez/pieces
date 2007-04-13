
#ifndef PIECES_FRAME_DATA_H
#define PIECES_FRAME_DATA_H

#include "Pieces/global"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"

#include <map>


namespace Pieces
{
class DataStream;


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
    // TODO: Do we need an ObjectData class, or is ByteArray sufficient? (Robin)
    typedef std::map<objectid_t, ByteArray> map_t;
    typedef map_t::value_type pair_t;

    FrameData();

    size_t size() const;
    bool isEmpty() const;

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

    bool hasObjectData(objectid_t objectId) const;
    ByteArray getObjectData(objectid_t objectId) const;

    void clear();
    bool removeObjectData(objectid_t objectId);
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

DataStream& operator<<(DataStream& ds, const FrameData& fd);
DataStream& operator>>(DataStream& ds, FrameData& fd);

} // namespace Pieces

#endif // PIECES_FRAME_DATA_H
