#if !defined PLAYEROSG_H
#define PLAYEROSG_H

#include <osg/MatrixTransform>

#include "player.h"

#include "Pieces/ReferencePointer"

namespace pong
{

class PlayerOSG : public osg::MatrixTransform
{
public:
    PlayerOSG(pcs::ReferencePointer<Player> player);
    ~PlayerOSG();

private:
    osg::ref_ptr<osg::Geode> createGeode();

    pcs::ReferencePointer<Player> m_player;

};

}

#endif // PLAYEROSG_H
