// host.cpp

#include "pong_host.h"

#include "Pieces/FrameData"
#include "Pieces/GameDataSender"

#include "Pieces/Debug"

#include "ball.h"
#include "ball_host_callback.h"
#include "player_host_callback.h"

#include "config.h"

const pcs::objectid_t idBall = 10000;
const pcs::objectid_t idPlayers = 10100;

PongHost::PongHost()
: pcs::Host()
, m_timer(0)
, m_dbBalls(new pcs::GameObjectDB())
, m_players()
, m_gameState()
{
    startListening(2222);

    PDEBUG << "Creating ball";

    // Initialize ball
    pcs::ReferencePointer<Ball> ball = new Ball(idBall);
    m_dbBalls->insert(idBall, ball.get());

    pcs::ReferencePointer<BallUpdateCallback> ballUpd = new BallUpdateCallback(this, ball.get(), &m_gameState, &m_players);

    ball->setAction(ACTION_UPDATE, ballUpd.get());

    sendCreateObject(idBall, TYPE_BALL);

    // Create timer
    m_timer = new pcs::Timer(eventLoop());
    m_timer->setRepeating(true);
    m_timer->start(20);
}

void PongHost::handle(pcs::TimerEvent*)
{
    pcs::framenum_t frameNum = sender()->getFrameNumber();

    // Game state has to be initialized each frame.
    m_gameState.init();

    // Execute callback for ball(s)
    m_dbBalls->applyAction(ACTION_UPDATE, frameNum);

    // Execute callback for players
    for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
    {
        (*it)->applyAction(ACTION_UPDATE, frameNum);
    }



    // Collect and store (in frameData) the data that should be sent for all game objects.
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


void PongHost::handle(pcs::MessageReceivedEvent* event)
{
    pcs::Message message = event->getMessage();

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
                pcs::ReferencePointer<Player> player = new Player(id);

                // Set initial position
                switch(numConnectedPlayers)
                {
                case 0:
                    player->setPositionX(cfg::player1XPos);
                    player->setLocation(Player::LEFT);
                    break;
                case 1:
                    player->setPositionX(cfg::player2XPos);
                    player->setLocation(Player::RIGHT);
                    break;
                }


                // Store senders address in player
                player->setPeerAddress(event->getSenderAddress());

                // Add callback
                player->setAction(ACTION_UPDATE, new PlayerHostCallback(player.get(), &m_gameState));

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
            pcs::ReferencePointer<Player> player = getPlayer(event->getSenderAddress());
            if(player.isValid())
            {
                player->setUpPressed(true);
                player->setMovingState(Player::STATE_UP);
            }
            break;
        }
    case MSG_UP_RELEASED:
        {
            pcs::ReferencePointer<Player> player = getPlayer(event->getSenderAddress());
            if(player.isValid())
            {
                player->setUpPressed(false);
                if(player->isDownPressed())
                {
                    player->setMovingState(Player::STATE_DOWN);
                }
                else
                {
                    player->setMovingState(Player::STATE_STOPPED);
                }
            }
            break;
        }
    case MSG_DOWN_PRESSED:
        {
            pcs::ReferencePointer<Player> player = getPlayer(event->getSenderAddress());
            if(player.isValid())
            {
                player->setDownPressed(true);
                player->setMovingState(Player::STATE_DOWN);
            }
            break;
        }
    case MSG_DOWN_RELEASED:
        {
            pcs::ReferencePointer<Player> player = getPlayer(event->getSenderAddress());
            if(player.isValid())
            {
                player->setDownPressed(false);
                if(player->isUpPressed())
                {
                    player->setMovingState(Player::STATE_UP);
                }
                else
                {
                    player->setMovingState(Player::STATE_STOPPED);
                }
            }
            break;
        }
    }
}

// Returns the correct Player based on socket address. Returns 0 if no
// Player matches the socket address.
pcs::ReferencePointer<Player> PongHost::getPlayer(pcs::SocketAddress sockAddr)
{
    for(PlayerList_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
    {
        if((*it)->getPeerAddress() == sockAddr)
        {
            return (*it);
        }
    }
    return 0;
}

