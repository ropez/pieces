// host.cpp

#include "Pieces/Application"
#include "Pieces/Host"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/GameDataSender"
#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"
#include "Pieces/GameObjectDB"
#include "Pieces/FrameData"
#include "Pieces/Timer"

#include "Pieces/Debug"

#include "ball.h"
#include "BallHostCallback.h"
#include "Player.h"
#include "PlayerHostCallback.h"
#include "pong_defines.h"

using namespace pcs;


/**
 * This host only acts as a message server forwarding events (messages)
 * to all peers, and assigns object ids to characters for each peer that joins
 * the game.
 *
 * The host doesn't use the Character class, and doesn't really know anything
 * about the actual "game".
 */
const objectid_t idBall = 10000;

class RunnerHost : public Host
{
public:
    RunnerHost()
        : pcs::Host()
        , m_dbBalls(new GameObjectDB())
    {
        startListening(2222);

        PDEBUG << "Creating ball";
        

        ReferencePointer<Ball> ball = new Ball(idBall);
        ReferencePointer<BallUpdateCallback> ballUpd = new BallUpdateCallback(ball.get());

        ball->setAction(ACTION_UPDATE, ballUpd.get());
        m_dbBalls->insert(idBall, ball.get());

        sendCreateObject(idBall, TYPE_BALL);

        m_timer = new Timer(eventLoop());
        m_timer->setRepeating(true);
        m_timer->start(20);
    }

protected:

    virtual void handle(TimerEvent*)
    {
        m_dbBalls->applyAction(ACTION_UPDATE, sender()->getFrameNumber());

        FrameData frameData;
        m_dbBalls->updateFrameData(frameData);

        if (frameData.size())
        {
            sender()->sendFrameData(frameData);
        }
        else
        {
            PWARNING << "Empty frame data";
        }
    }


    virtual void handle(MessageReceivedEvent* event)
    {
        Message message = event->getMessage();

        switch(message.getMessageType())
        {
        case MSG_GAME_EVENT_JOIN:
            {
                pcs::port_t port = message.get<port_t>(PR_PORT);

                SocketAddress peer = event->getSenderAddress();
                peer.setPort(port);
                sender()->addReceiver(peer);
            }
            break;
        case MSG_UP_PRESSED:
            {
                PDEBUG << "up p";
                break;
            }
        case MSG_UP_RELEASED:
            {
                PDEBUG << "up r";
                break;
            }
        case MSG_DOWN_PRESSED:
            {
                PDEBUG << "down p";
                break;
            }
        case MSG_DOWN_RELEASED:
            {
                PDEBUG << "down r";
                break;
            }
        }
    }

private:
    AutoPointer<Timer> m_timer;
    AutoPointer<GameObjectDB> m_dbBalls;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    AutoPointer<RunnerHost> host(new RunnerHost());

    host->exec();
}


