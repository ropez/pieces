#if !defined FRAME_H
#define FRAME_H

#include <osg/MatrixTransform>

class Frame : public osg::MatrixTransform
{
public:
    Frame();
    ~Frame();

    double getPositionZ();
    void addRelativeZ(double zOffset);
    void setPositionX(double xPos);
    void setPositionZ(double zPos);

private:
    osg::ref_ptr<osg::Geode> createGeode();
    
    double _xPos;
    double _zPos;

};

#endif // FRAME_H