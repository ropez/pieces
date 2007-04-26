#include "score_board.h"

#include <osgText/Text>
#include <osg/Geode>
#include "config.h"

#include "pong_defines.h"

#include <sstream>

class ScoreCallback : public osg::NodeCallback
{
public:
    ScoreCallback(PlayerList_t* playerList, osg::ref_ptr<osgText::Text> score1, osg::ref_ptr<osgText::Text> score2)
        : osg::NodeCallback()
        , m_playerList(playerList)
        , m_score1(score1)
        , m_score2(score2)
    {
    }

    virtual void operator () (osg::Node* node, osg::NodeVisitor* nv)
    {

        int counter = 0;

        for(PlayerList_t::iterator it = m_playerList->begin(); it != m_playerList->end(); ++it)
        {
            int currentScore = (*it)->getScore();
            std::stringstream scoreAsString;
            scoreAsString << currentScore;

            osg::ref_ptr<osgText::Text> text = 0;
            switch(counter)
            {
            case 0:
                text = m_score1;
                break;
            case 1:
                text = m_score2;
                break;
            }
            
            if(text.valid())
            {
                text->setText(scoreAsString.str());
            }

            ++counter;
        }
        traverse(node, nv);
    }

private:
    PlayerList_t* m_playerList;
    osg::ref_ptr<osgText::Text> m_score1;
    osg::ref_ptr<osgText::Text> m_score2;

};

ScoreBoard::ScoreBoard(PlayerList_t* playerList)
: osg::MatrixTransform()
, m_playerList(playerList)
{
    createGeode();

    
}

void ScoreBoard::createGeode()
{
    osg::ref_ptr<osgText::Text> scorePlayer1 = new osgText::Text();
    scorePlayer1->setAutoRotateToScreen(true);
    scorePlayer1->setFont(cfg::font);
    scorePlayer1->setPosition(osg::Vec3(cfg::score1PosX, 0.0, cfg::score1PosZ));
    scorePlayer1->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    scorePlayer1->setFontResolution(30, 30);
    scorePlayer1->setAlignment(osgText::Text::CENTER_BOTTOM_BASE_LINE);
    scorePlayer1->setText("0");

    osg::ref_ptr<osgText::Text> scorePlayer2 = new osgText::Text();
    scorePlayer2->setAutoRotateToScreen(true);
    scorePlayer2->setFont(cfg::font);
    scorePlayer2->setPosition(osg::Vec3(cfg::score2PosX, 0.0, cfg::score2PosZ));
    scorePlayer2->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    scorePlayer2->setFontResolution(30, 30);
    scorePlayer2->setAlignment(osgText::Text::CENTER_BOTTOM_BASE_LINE);
    scorePlayer2->setText("0");

    setUpdateCallback(new ScoreCallback(m_playerList, scorePlayer1, scorePlayer2));

    osg::Geode* score1 = new osg::Geode();
    score1->addDrawable(scorePlayer1.get());
    addChild(score1);

    osg::Geode* score2 = new osg::Geode();
    score2->addDrawable(scorePlayer2.get());
    addChild(score2);

}
