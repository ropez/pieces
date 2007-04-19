#if !defined BALLPEERCALLBACK_H
#define BALLPEERCALLBACK_H

#include "Pieces/GameObjectAction"

#include "ball.h"

#include "Pieces/GameObject"

class BallPeerCallback : public pcs::GameObjectAction
{
public:
    BallPeerCallback(Ball* ball);

    virtual void operator()(pcs::framenum_t);

private:
    Ball* m_ball;
};

#endif // BALLPEERCALLBACK_H

