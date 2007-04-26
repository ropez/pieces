#ifndef CHATHOST_H
#define CHATHOST_H

#include <Pieces/Host>


class ChatHost : public Pieces::Host
{
public:
    ChatHost();

protected:
    virtual void handle(Pieces::MessageReceivedEvent* event);
};

#endif
