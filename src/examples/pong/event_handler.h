#if !defined EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <osgGA/GUIEventHandler>
#include "player.h"
#include "ballosg.h"

class PongEventHandler : public osgGA::GUIEventHandler
{
public:
    PongEventHandler(osg::ref_ptr<Player> player1, osg::ref_ptr<Player> player2, osg::ref_ptr<BallOSG> ball);
    ~PongEventHandler();
    
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
private:
    osg::ref_ptr<Player> m_player1;
    osg::ref_ptr<Player> m_player2;
    osg::ref_ptr<BallOSG> m_ball;
    bool m_player1Up;
    bool m_player1Down;
    bool m_player2Up;
    bool m_player2Down;


    int m_waitCollisionPlayer1;
    int m_waitCollisionPlayer2;

    int m_scorePlayer1;
    int m_scorePlayer2;
    
};

#endif // EVENT_HANDLER_H