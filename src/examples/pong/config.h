#if !defined CONFIG_H
#define CONFIG_H

#include <string>

namespace cfg
{
    const double pi = 3.1415926535897932384626433832795;
    const double pi_2 = pi / 2.0;
    const double pi_4 = pi / 4.0;

    const double pi2 = pi * 2.0;
    const double pi4 = pi * 4.0;


    inline double degreesToRadians(double angle) { return angle * pi / 180.0; }

    const double frameOutsideLeft   = -640.0;
    const double frameOutsideRight  =  640.0;
    const double frameOutsideTop    =  512.0;
    const double frameOutsideBottom = -512.0;

    const double frameInsideLeft   =  -610.0;
    const double frameInsideRight  =   610.0;
    const double frameInsideTop    =   482.0;
    const double frameInsideBottom =  -482.0;
    
    const double playerHeight = 100.0;
    const double playerHeightHalf = playerHeight / 2.0;
    const double playerWidth  = 20.0;
    const double playerWidthHalf  = playerWidth / 2.0;

    const double ballSize = 20.0;
    const double ballSizeHalf = ballSize / 2.0;

    const double player1XPos = -500.0;
    const double player2XPos =  500.0;

    const double maxAngle = degreesToRadians(70.0);

    const double ballVelocity = 10.0;

    const double playerVelocity = 7.0;

    // Score board
#ifdef WIN32
    const std::string font = "ARIAL.TTF";
#else
    const std::string font = "TYPICAL_LINUX_FONT.TTF";
#endif

    const double score1PosX = -550;
    const double score1PosZ =  530;
    const double score2PosX =  550;
    const double score2PosZ =  530;

    
}

#endif // CONFIG_H
