
#ifndef PIECES_GAME_DATA_EVENT_H
#define PIECES_GAME_DATA_EVENT_H

#include "Pieces/Event"
#include "Pieces/FrameData"


namespace pcs
{


/**
 * \class GameDataEvent
 * \brief A game data event.
 *
 * \author Tord Heimdal
 */
class GameDataEvent : public Event
{
    friend class AutoPointer<GameDataEvent>;

public:

    GameDataEvent(framenum_t frameNum, const FrameData& frameData);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    /**
     * Returnes the frame number of the event.
     */
    framenum_t getFrameNumber() const;

    FrameData getFrameData() const;

protected:
    virtual ~GameDataEvent();

private:
    DISABLE_COPY(GameDataEvent);

    framenum_t m_frameNum;
    FrameData m_frameData;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_EVENT_H
