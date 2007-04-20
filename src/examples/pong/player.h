#if !defined PLAYER_H
#define PLAYER_H

#include "Pieces/GameObject"
#include "Pieces/SocketAddress"

class Player : public pcs::GameObject
{
public:
    enum MovingState
    {
        STATE_STOPPED,
        STATE_UP,
        STATE_DOWN
    };

    Player(pcs::objectid_t objectId);

    virtual void encode(pcs::DataStream& ds) const;
    virtual void decode(pcs::DataStream& ds);

    void addRelativeZ(double offset);
    void setPositionZ(double pos);
    void setPositionX(double pos);
    double getPositionZ() const;
    double getPositionX() const;

    // Host specific function. Returns the address of the peer that is
    // associated with this player.
    const pcs::SocketAddress& getPeerAddress();

    // Host specific function. Associates a peer address with this player.
    void setPeerAddress(const pcs::SocketAddress& peerAddress);

    void setMovingState(MovingState state);
    MovingState getMovingState() const;

    void setDownPressed(bool pressed);
    bool isDownPressed() const;

    void setUpPressed(bool pressed);
    bool isUpPressed() const;


private:
    pcs::SocketAddress m_peerAddress; // Host Specific
    MovingState m_movingState;
    double m_posX;
    double m_posZ;

    bool m_downIsPressed;
    bool m_upIsPressed;
};

#endif //PLAYER_H
