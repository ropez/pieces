
#ifndef PIECES_GAME_EVENT_H
#define PIECES_GAME_EVENT_H

#include "Pieces/Event"

namespace pcs
{


/**
 * \class GameEvent
 * \brief A game-specific event.
 *
 * This class is meant to be used as base class for game-specific events.
 * Game-events are created by the user host application, and propagated to the
 * peers by the pieces framework.
 *
 * Game events can have an associated event type, in addition to the generic
 * data storage provided by the basic Event.
 *
 * \author Robin Pedersen
 */
class GameEvent : public Event
{
    friend class AutoPointer<GameEvent>;

public:

    /**
     * Creates a game-event and sets the type property to the given \a type.
     */
    explicit GameEvent(int type = 0);

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the event type.
     */
    int type() const;

    /**
     * Set or change the event type.
     */
    void setType(int type);

protected:
    virtual ~GameEvent();

private:
    DISABLE_COPY(GameEvent);
    int m_type;
};

} // namespace pcs

#endif // PIECES_GAME_EVENT_H
