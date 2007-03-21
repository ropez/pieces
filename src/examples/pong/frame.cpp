#include "frame.h"
#include "config.h"
#include <osg/Geode>
#include <osg/Geometry>

Frame::Frame()
: osg::MatrixTransform()
, _xPos(0.0)
, _zPos(0.0)
{
    addChild(createGeode().get());
}

Frame::~Frame()
{
}

osg::ref_ptr<osg::Geode> Frame::createGeode()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    // create Geometry object to store all the vetices and lines primtive.
    osg::ref_ptr<osg::Geometry> polyGeom = new osg::Geometry();
    
    
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    // note, anticlockwsie ordering.
    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameOutsideTop));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft,  0.0, cfg::frameOutsideTop));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft,  0.0, cfg::frameInsideTop));
    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameInsideTop));

    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameInsideBottom));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft,  0.0, cfg::frameInsideBottom));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft,  0.0, cfg::frameOutsideBottom));
    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameOutsideBottom));

    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameInsideTop));
    vertices->push_back(osg::Vec3(cfg::frameInsideRight,  0.0, cfg::frameInsideTop));
    vertices->push_back(osg::Vec3(cfg::frameInsideRight,  0.0, cfg::frameInsideBottom));
    vertices->push_back(osg::Vec3(cfg::frameOutsideRight, 0.0, cfg::frameInsideBottom));

    vertices->push_back(osg::Vec3(cfg::frameInsideLeft,  0.0,  cfg::frameInsideTop));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft, 0.0,  cfg::frameInsideTop));
    vertices->push_back(osg::Vec3(cfg::frameOutsideLeft, 0.0,  cfg::frameInsideBottom));
    vertices->push_back(osg::Vec3(cfg::frameInsideLeft,  0.0,  cfg::frameInsideBottom));

    // pass the created vertex array to the points geometry object.
    polyGeom->setVertexArray(vertices.get());

    osg::Vec4Array* colors = new osg::Vec4Array;
    // add a white color, colors take the form r,g,b,a with 0.0 off, 1.0 full on.
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // pass the color arry to points geometry, note the binding to tell the geometry
    // that only use one color for the whole object.
    polyGeom->setColorArray(colors);
    polyGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

    // set the normal in the same way color.
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    polyGeom->setNormalArray(normals.get());
    polyGeom->setNormalBinding(osg::Geometry::BIND_OVERALL);


    // This time we simply use primitive, and hardwire the number of coords to use 
    // since we know up front,
    polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertices->size()));

    // add the points geomtry to the geode.
    geode->addDrawable(polyGeom.get());

    return geode;
}

void Frame::setPositionX(double xPos)
{
    _xPos = xPos;
    setMatrix(osg::Matrix::translate(osg::Vec3(_xPos, 0.0, _zPos)));
}

void Frame::setPositionZ(double zPos)
{
    _zPos = zPos;
    setMatrix(osg::Matrix::translate(osg::Vec3(_xPos, 0.0, _zPos)));
}

double Frame::getPositionZ()
{
    return _zPos;
}

void Frame::addRelativeZ(double zOffset)
{
    _zPos += zOffset;
    setPositionZ(_zPos);
}