#if !defined BALLUPDATECALLBACK_H
#define BALLUPDATECALLBACK_H

#include "ball.h"

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"

class BallUpdateCallback : public Pieces::GameObjectAction
{
public:
    BallUpdateCallback(Ball* ball);

    virtual void operator()(Pieces::framenum_t);

private:
    Ball* m_ball;
};

#endif //BALLUPDATECALLBACK_H
