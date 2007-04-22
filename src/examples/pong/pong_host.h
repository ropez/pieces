// host.cpp

#include "Pieces/Host"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/GameObjectDB"
#include "Pieces/Timer"
#include "Pieces/AutoPointer"

#include "Player.h"
#include "pong_defines.h"

/**
 * This host only acts as a message server forwarding events (messages)
 * to all peers, and assigns object ids to characters for each peer that joins
 * the game.
 *
 * The host doesn't use the Character class, and doesn't really know anything
 * about the actual "game".
 */
class PongHost : public pcs::Host
{
public:
    PongHost();

protected:
    virtual void handle(pcs::TimerEvent*);
    virtual void handle(pcs::MessageReceivedEvent* event);

private:
    // Returns the correct Player based on socket address. Returns 0 if no
    // Player matches the socket address.
    pcs::ReferencePointer<Player> getPlayer(pcs::SocketAddress sockAddr);

    // Member variables
    pcs::AutoPointer<pcs::Timer> m_timer;
    pcs::AutoPointer<pcs::GameObjectDB> m_dbBalls;
    PlayerList_t m_players;
    GameState m_gameState;
};
