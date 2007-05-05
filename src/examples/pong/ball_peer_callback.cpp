#include "BallPeerCallback.h"

#include "Pieces/Debug"

#include <iostream>

BallPeerCallback::BallPeerCallback(Ball* ball)
: pcs::GameObjectAction()
, m_ball(ball)
{
}

void BallPeerCallback::operator()(pcs::framenum_t frameNum)
{
}
