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
const objectid_t idPlayer1 = 10001;
const objectid_t idPlayer2 = 10002;


class RunnerHost : public Host
{
public:
    RunnerHost()
        : pcs::Host()
        , m_dbBalls(new GameObjectDB())
        , m_player1(new Player(idPlayer1, -20))
        , m_player2(new Player(idPlayer2, 20))
        , m_numConnectedPeers(0)
    {
        startListening(2222);

        PDEBUG << "Creating ball";
        
        // Initialize ball
        ReferencePointer<Ball> ball = new Ball(idBall);
        m_dbBalls->insert(idBall, ball.get());

        ReferencePointer<BallUpdateCallback> ballUpd = new BallUpdateCallback(ball.get());
        ball->setAction(ACTION_UPDATE, ballUpd.get());

        sendCreateObject(idBall, TYPE_BALL);

        // Intialize players
        m_player1->setAction(ACTION_UPDATE, new PlayerHostCallback(m_player1));
        m_player2->setAction(ACTION_UPDATE, new PlayerHostCallback(m_player2));

        // Create timer
        m_timer = new Timer(eventLoop());
        m_timer->setRepeating(true);
        m_timer->start(20);
    }

protected:

    virtual void handle(TimerEvent*)
    {
        pcs::framenum_t frameNum = sender()->getFrameNumber();
        
        // Execute callbacks.
        m_dbBalls->applyAction(ACTION_UPDATE, frameNum);
        m_player1->applyAction(ACTION_UPDATE, frameNum);
        m_player2->applyAction(ACTION_UPDATE, frameNum);


        // Get the new update data for ball(s) and players.
        // and store in frame data.
        FrameData frameData;
        m_dbBalls->updateFrameData(frameData);
        m_player1->updateFrameData(frameData);
        m_player2->updateFrameData(frameData);


        // Send the frame data
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

                switch(m_numConnectedPeers)
                {
                case 0:
                    sendCreateObject(idPlayer1, TYPE_PLAYER_1);
                    ++m_numConnectedPeers;
                    break;
                case 1:
                    sendCreateObject(idPlayer2, TYPE_PLAYER_2);
                    ++m_numConnectedPeers;
                    break;
                default:
                    PINFO << "Server full";
                    break;
                }
            }
            break;
        case MSG_UP_PRESSED:
            {
                PDEBUG << "up p";
                m_player1->setMovingState(Player::STATE_UP);
                break;
            }
        case MSG_UP_RELEASED:
            {
                PDEBUG << "up r";
                m_player1->setMovingState(Player::STATE_STOPPED);
                break;
            }
        case MSG_DOWN_PRESSED:
            {
                PDEBUG << "down p";
                m_player1->setMovingState(Player::STATE_DOWN);
                break;
            }
        case MSG_DOWN_RELEASED:
            {
                PDEBUG << "down r";
                m_player1->setMovingState(Player::STATE_STOPPED);
                break;
            }
        }
    }

private:
    AutoPointer<Timer> m_timer;
    AutoPointer<GameObjectDB> m_dbBalls;
    Player* m_player1;
    Player* m_player2;
    unsigned int m_numConnectedPeers;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    AutoPointer<RunnerHost> host(new RunnerHost());

    host->exec();
}
