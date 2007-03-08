
#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"


namespace Pieces
{
class EventHandler;


class Event
{
    friend class EventLoop;
    friend class std::auto_ptr<Event>;

public:

    explicit Event();

    bool isUserDefined() const;

    void setData(const ByteArray& data);
    ByteArray data() const;

protected:
    virtual ~Event();

    virtual void trigger(EventHandler* h);

private:

    Event(const Event&);
    Event& operator=(const Event&);

    ByteArray m_data;
};

} // namespace Pieces

#endif // PIECES_EVENT_H
