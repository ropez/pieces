#ifndef CHATHOST_H
#define CHATHOST_H

#include <Pieces/Host>

namespace qchat
{

class ChatHost : public pcs::Host
{
public:
    ChatHost();

protected:
    virtual void handle(pcs::MessageReceivedEvent* event);
};

}

#endif
