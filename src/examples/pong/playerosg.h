#if !defined PLAYEROSG_H
#define PLAYEROSG_H

#include <osg/MatrixTransform>

#include "player.h"

#include "Pieces/ReferencePointer"

class PlayerOSG : public osg::MatrixTransform
{
public:
    PlayerOSG(pcs::ReferencePointer<Player> player);
    ~PlayerOSG();

    double getPositionZ();
    void addRelativeZ(double zOffset);
    void setPositionX(double xPos);
    void setPositionZ(double zPos);

private:
    osg::ref_ptr<osg::Geode> createGeode();

    pcs::ReferencePointer<Player> m_player;
    
    double m_xPos;
    double m_zPos;

};

#endif // PLAYEROSG_H
