
#ifndef PIECES_GAME_DATA_EVENT_H
#define PIECES_GAME_DATA_EVENT_H

#include "Pieces/Event"

namespace Pieces
{


/**
 * \class GameDataEvent
 * \brief A game data event.
 *
 *
 *
 *
 * \author Tord Heimdal
 */
class GameDataEvent : public Event
{
    friend class AutoPointer<GameDataEvent>;

public:

    /**
     * Creates an event of the given type, from the given sender.
     */
    GameDataEvent(framenum_t frameNum);

    /**
     * Returnes the frame number of the event.
     */
    framenum_t getFrameNumber() const;

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

protected:
    virtual ~GameDataEvent();

private:
    DISABLE_COPY(GameDataEvent);

    framenum_t m_frameNum;
};

} // namespace Pieces

#endif // PIECES_GAME_DATA_EVENT_H
