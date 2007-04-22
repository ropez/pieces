#include "Pieces/Peer"

#include "Pieces/GameDataEvent"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/AutoPointer"
#include "Pieces/GameObjectDB"

#include <osg/Group>

class PongPeer : public pcs::Peer
{
public:
    PongPeer(osg::ref_ptr<osg::Group> rootOSG);

protected:
    virtual void handle(pcs::GameDataEvent* event);

    virtual void handle(pcs::MessageReceivedEvent* event);

private:
    pcs::AutoPointer<pcs::GameObjectDB> m_db;
    osg::ref_ptr<osg::Group> m_rootOSG;
    int m_numPlayers;

};
