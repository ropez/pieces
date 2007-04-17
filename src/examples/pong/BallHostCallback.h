#if !defined BALLUPDATECALLBACK_H
#define BALLUPDATECALLBACK_H

#include "ball.h"

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

class BallUpdateCallback : public pcs::GameObjectAction
{
public:
    BallUpdateCallback(Ball* ball);

    virtual void operator()(pcs::framenum_t);

private:
    Ball* m_ball;
};

#endif //BALLUPDATECALLBACK_H
