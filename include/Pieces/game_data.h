
#ifndef PIECES_GAME_DATA_H
#define PIECES_GAME_DATA_H

#include "Pieces/global"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/FrameData"


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
    void setFrameData(framenum_t frameNum, const FrameData& frameData);

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

} // namespace Pieces

#endif // PIECES_GAME_DATA_H
