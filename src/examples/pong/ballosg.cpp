#include "ballosg.h"
#include "config.h"
#include <osg/Geode>
#include <osg/Geometry>

#include <iostream>

class BallOSGUpdateCallback : public osg::NodeCallback
{
public:
    BallOSGUpdateCallback(Pieces::ReferencePointer<Ball> ball)
        : osg::NodeCallback()
        , m_ball(ball)
    {
    }

    void operator() (osg::Node* node, osg::NodeVisitor* nv)
    {
        BallOSG* ballOSG = dynamic_cast<BallOSG*>(node);
        
        if(ballOSG)
        {
            ballOSG->setMatrix(osg::Matrix::translate(osg::Vec3(m_ball->getPositionX(), 0.0, m_ball->getPositionZ())));
        }

        traverse(node, nv);
    }

private:
    Pieces::ReferencePointer<Ball> m_ball;
};

BallOSG::BallOSG(Pieces::ReferencePointer<Ball> ball)
: osg::MatrixTransform()
, m_ball(ball)
, m_xPos(0.0)
, m_zPos(0.0)
, m_velocity(0.0)
, m_angle(0.0)
{
    addChild(createGeode().get());
    setUpdateCallback(new BallOSGUpdateCallback(ball));
}

BallOSG::~BallOSG()
{
}

void BallOSG::update()
{
    osg::Vec3 currPos = getMatrix().getTrans();
    currPos.x() += m_velocity * sin(m_angle);
    currPos.z() += m_velocity * cos(m_angle);
    
    setMatrix(osg::Matrix::translate(currPos.x(), currPos.y(), currPos.z()));
    
}

osg::ref_ptr<osg::Geode> BallOSG::createGeode()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    // create Geometry object to store all the vetices and lines primtive.
    osg::ref_ptr<osg::Geometry> polyGeom = new osg::Geometry();
        
    // note, anticlockwsie ordering.
    const double halfBallSize = cfg::ballSize / 2;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
    vertices->push_back(osg::Vec3(-halfBallSize, 0.0, -halfBallSize));
    vertices->push_back(osg::Vec3( halfBallSize, 0.0, -halfBallSize));
    vertices->push_back(osg::Vec3( halfBallSize, 0.0,  halfBallSize));
    vertices->push_back(osg::Vec3(-halfBallSize, 0.0,  halfBallSize));
    
    // pass the created vertex array to the points geometry object.
    polyGeom->setVertexArray(vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    // add a white color, colors take the form r,g,b,a with 0.0 off, 1.0 full on.
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // pass the color arry to points geometry, note the binding to tell the geometry
    // that only use one color for the whole object.
    polyGeom->setColorArray(colors.get());
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

void BallOSG::setPositionX(double xPos)
{
    m_xPos = xPos;
    setMatrix(osg::Matrix::translate(osg::Vec3(m_xPos, 0.0, m_zPos)));
}

void BallOSG::setPositionZ(double zPos)
{
    m_zPos = zPos;
    setMatrix(osg::Matrix::translate(osg::Vec3(m_xPos, 0.0, m_zPos)));
}

void BallOSG::addRelativeZ(double zOffset)
{
    m_zPos += zOffset;
    setPositionZ(m_zPos);
}

void BallOSG::setVelocity(double velocity)
{
    m_velocity = velocity;
}

void BallOSG::setAngle(double angle)
{
    m_angle = angle;
}

double BallOSG::getAngle()
{
    return m_angle;
}

double BallOSG::getPositionX()
{
    return getMatrix().getTrans().x();
}

double BallOSG::getPositionZ()
{
    return getMatrix().getTrans().z();
}
