#if !defined PLAYER_H
#define PLAYER_H

#include <osg/MatrixTransform>

class PlayerOSG : public osg::MatrixTransform
{
public:
    PlayerOSG();
    ~PlayerOSG();

    double getPositionZ();
    void addRelativeZ(double zOffset);
    void setPositionX(double xPos);
    void setPositionZ(double zPos);

private:
    osg::ref_ptr<osg::Geode> createGeode();
    
    double _xPos;
    double _zPos;

};

#endif // PLAYER_H
