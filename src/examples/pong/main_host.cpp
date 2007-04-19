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

#include <list>

/**
 * This host only acts as a message server forwarding events (messages)
 * to all peers, and assigns object ids to characters for each peer that joins
 * the game.
 *
 * The host doesn't use the Character class, and doesn't really know anything
 * about the actual "game".
 */
const pcs::objectid_t idBall = 10000;
const pcs::objectid_t idPlayers = 10100;


class RunnerHost : public pcs::Host
{
private:
    typedef std::list<pcs::ReferencePointer<Player> > PlayerList_t;

public:
    RunnerHost()
        : pcs::Host()
        , m_dbBalls(new pcs::GameObjectDB())
        , m_players()
        , m_numConnectedPeers(0)
    {
        startListening(2222);

        PDEBUG << "Creating ball";
        
        // Initialize ball
        pcs::ReferencePointer<Ball> ball = new Ball(idBall);
        m_dbBalls->insert(idBall, ball.get());

        pcs::ReferencePointer<BallUpdateCallback> ballUpd = new BallUpdateCallback(ball.get());
        ball->setAction(ACTION_UPDATE, ballUpd.get());

        sendCreateObject(idBall, TYPE_BALL);

        // Create and and initialize players
        const int numPlayers = 2;
        for(int i = 0; i < numPlayers; ++i)
        {
        }

        // Create timer
        m_timer = new pcs::Timer(eventLoop());
        m_timer->setRepeating(true);
        m_timer->start(20);
    }

protected:

    virtual void handle(pcs::TimerEvent*)
    {
        pcs::framenum_t frameNum = sender()->getFrameNumber();
        
        // Execute callback for ball(s)
        m_dbBalls->applyAction(ACTION_UPDATE, frameNum);

        // Execute callback for players
        for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
        {
            (*it)->applyAction(ACTION_UPDATE, frameNum);
        }
        

        // Get the new update data for ball(s) and players.
        // and store in frame data.
        pcs::FrameData frameData;
        m_dbBalls->updateFrameData(frameData);
        for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
        {
            (*it)->updateFrameData(frameData);
        }
        
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


    virtual void handle(pcs::MessageReceivedEvent* event)
    {
        pcs::Message message = event->getMessage();

        PDEBUG << event->getSenderAddress();

        switch(message.getMessageType())
        {
        case MSG_GAME_EVENT_JOIN:
            {
                pcs::port_t port = message.get<pcs::port_t>(pcs::PR_PORT);

                pcs::SocketAddress peer = event->getSenderAddress();
                peer.setPort(port);
                sender()->addReceiver(peer);

                const size_t numConnectedPlayers = m_players.size();
                if(numConnectedPlayers < 2)
                {
                    // Generated unique id
                    pcs::objectid_t id = idPlayers + numConnectedPlayers;

                    // Create Player
                    pcs::ReferencePointer<Player> player = new Player(id, 0);

                    // Store senders address in player
                    player->setPeerAddress(event->getSenderAddress());

                    // Add callback
                    player->setAction(ACTION_UPDATE, new PlayerHostCallback(player.get()));

                    // Send Create message to peers.
                    sendCreateObject(id, TYPE_PLAYER);
                    
                    // Add player to players list.
                    m_players.push_back(player);
                }
                else
                {
                    PINFO << "Server full";
                }
            }
            break;
        case MSG_UP_PRESSED:
            {
                pcs::ReferencePointer<Player> player = 0;
                for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
                {
                    if((*it)->getPeerAddress() == event->getSenderAddress())
                    {
                        player = (*it);
                        break;
                    }
                }

                player->setMovingState(Player::STATE_UP);

                break;
            }
        case MSG_UP_RELEASED:
            {
                pcs::ReferencePointer<Player> player = 0;
                for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
                {
                    if((*it)->getPeerAddress() == event->getSenderAddress())
                    {
                        player = (*it);
                        break;
                    }
                }

                player->setMovingState(Player::STATE_STOPPED);

                break;
            }
        case MSG_DOWN_PRESSED:
            {
                pcs::ReferencePointer<Player> player = 0;
                for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
                {
                    if((*it)->getPeerAddress() == event->getSenderAddress())
                    {
                        player = (*it);
                        break;
                    }
                }

                player->setMovingState(Player::STATE_DOWN);

                break;
            }
        case MSG_DOWN_RELEASED:
            {
                pcs::ReferencePointer<Player> player = 0;
                for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
                {
                    if((*it)->getPeerAddress() == event->getSenderAddress())
                    {
                        player = (*it);
                        break;
                    }
                }

                player->setMovingState(Player::STATE_STOPPED);
                break;
            }
        }
    }

private:
    pcs::AutoPointer<pcs::Timer> m_timer;
    pcs::AutoPointer<pcs::GameObjectDB> m_dbBalls;
    PlayerList_t m_players;

    unsigned int m_numConnectedPeers;
};


int main(int argc, char** argv)
{
    pcs::Application application(argc, argv);

    pcs::AutoPointer<RunnerHost> host(new RunnerHost());

    host->exec();
}
