#if !defined SCORE_BOARD_H
#define SCORE_BOARD_H

#include <osg/MatrixTransform>


#include "pong_defines.h"

namespace pong
{

class ScoreBoard : public osg::MatrixTransform
{
public:
    ScoreBoard(PlayerList_t* playerList);

private:
    void createGeode();
    PlayerList_t* m_playerList;

};

}

#endif // SCORE_BOARD_H
