#if !defined PONG_PEER_H
#define PONG_PEER_H

#include "Pieces/Peer"

#include "Pieces/GameDataEvent"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/AutoPointer"
#include "Pieces/GameObjectDB"

#include "pong_defines.h"

#include <osg/Group>

namespace pong
{

class PongPeer : public pcs::Peer
{
public:
    PongPeer(osg::ref_ptr<osg::Group> rootOSG);

    PlayerList_t* getPlayerList();
protected:
    virtual void handle(pcs::GameDataEvent* event);

    virtual void handle(pcs::MessageReceivedEvent* event);

private:
    pcs::AutoPointer<pcs::GameObjectDB> m_db;
    osg::ref_ptr<osg::Group> m_rootOSG;
    PlayerList_t m_playerList;
};

}

#endif // PONG_PEER_H
