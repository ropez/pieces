
#ifndef PIECES_GAME_DATA_EVENT_H
#define PIECES_GAME_DATA_EVENT_H

#include "Pieces/Event"
#include "Pieces/FrameData"


namespace pcs
{


/**
 * \class GameDataEvent game_data_event.h <Pieces/GameDataEvent>
 * \brief A game data event.
 *
 * A Peer receives this kind of event after the GameDataReceiver (Peer::receiver())
 * has received a frame data packet.
 *
 * The peer should handle the event by saving the data for later use, of applying
 * it directly to it's game objects.
 *
 * \author Tord Heimdal
 */
class GameDataEvent : public Event
{
    friend class AutoPointer<GameDataEvent>;

public:

    /**
     * Creates an event with the given frame number and frame data.
     */
    GameDataEvent(framenum_t frameNum, const FrameData& frameData);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the frame number of the event.
     */
    framenum_t getFrameNumber() const;

    /**
     * Returns the frame data.
     */
    FrameData getFrameData() const;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~GameDataEvent();

private:
    DISABLE_COPY(GameDataEvent);

    framenum_t m_frameNum;
    FrameData m_frameData;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_EVENT_H
