#if !defined PLAYER_H
#define PLAYER_H

#include <osg/MatrixTransform>

class Player : public osg::MatrixTransform
{
public:
    Player();
    ~Player();

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