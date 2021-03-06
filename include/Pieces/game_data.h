/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PIECES_GAME_DATA_H
#define PIECES_GAME_DATA_H

#include "Pieces/global"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/FrameData"


namespace pcs
{

/**
 * \class GameData game_data.h <Pieces/GameData>
 * \brief Container of frame data.
 *
 * This class is provided for convenience. It contains a set of FrameData
 * objects, indexed by frame number. It can be used to buffer data sent from
 * a Host or received by a Peer.
 *
 * Some users of Pieces might want to keep old frame data. This might be used
 * by the host to go back and view a previous snapshot of the game when handling
 * some event that a peer send during an earlier frame.
 *
 * It can also be used to keep frames in a peer that has not yet been displayed,
 * due to synchronization between traffic and graphics rendering.
 *
 * The GameData has an upper limit to the number of frames it contains, when this
 * number is exceeded, the oldest frame is removed.
 *
 * This class uses \ref implicit_sharing.
 *
 * \author Robin Pedersen
 */
class GameData
{
public:

    /**
     * Create a game-data object with an upper limit of \a maxFrames.
     */
    explicit GameData(size_t maxFrames);

    /**
     * Copy contructor.
     */
    GameData(const GameData& other);

    /**
     * Assignment operator.
     */
    GameData& operator=(const GameData& other);

    /**
     * Returns true is the given frame exists.
     */
    bool hasFrameData(framenum_t frameNum) const;

    /**
     * Returns the data for the given frame, or throws an InvalidKeyException
     * if it doesn't exist.
     */
    FrameData getFrameData(framenum_t frameNum) const;

    /**
     * Remove the data for the given frame number.
     *
     * Returns true if remove, or false if no such frame existed.
     */
    bool removeFrameData(framenum_t frameNum);

    /**
     * Insert or replace the data for the given frame.
     */
    void setFrameData(framenum_t frameNum, const FrameData& frameData);

private:
    typedef std::map<framenum_t, FrameData> map_t;

    class Data : public SharedData
    {
    public:
        Data();

        size_t maxFrames;
        map_t frameData;

    private:
        friend class SharedDataPointer<Data>;

        Data(const Data& other);
        ~Data() {}

        DISABLE_ASSIGNMENT(Data);
    };

    SharedDataPointer<Data> d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_H
