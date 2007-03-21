#if !defined CONFIG_H
#define CONFIG_H

#include <osg/math>

namespace cfg
{
    const double frameOutsideLeft   = -640.0;
    const double frameOutsideRight  =  640.0;
    const double frameOutsideTop    =  512.0;
    const double frameOutsideBottom = -512.0;

    const double frameInsideLeft   =  -610.0;
    const double frameInsideRight  =   610.0;
    const double frameInsideTop    =   482.0;
    const double frameInsideBottom =  -482.0;
    
    const double playerHeight = 100.0;
    const double playerHeightHalf = playerHeight / 2;
    const double playerWidth  = 20.0;

    const double ballSize = 20.0;
    const double ballSizeHalf = ballSize / 2;

    const double player1XPos = -500.0;
    const double player2XPos =  500.0;

    const double maxAngle = osg::DegreesToRadians(70.0);

    const double ballVelocity = 10.0;

    const double playerVelocity = 7.0;
}

#endif // CONFIG_H