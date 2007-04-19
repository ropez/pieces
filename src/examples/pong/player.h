#if !defined PLAYER_H
#define PLAYER_H

#include "Pieces/GameObject"

class Player : public pcs::GameObject
{
public:
    enum MovingState
    {
        STATE_STOPPED,
        STATE_UP,
        STATE_DOWN
    };

    Player(pcs::objectid_t objectId, int posX);

    virtual void encode(pcs::DataStream& ds) const;
    virtual void decode(pcs::DataStream& ds);

    void addRelativeZ(double offsetZ);
    void setPositionZ(double posZ);
    double getPositionZ() const;
    double getPositionX() const;

    void setMovingState(MovingState state);
    MovingState getMovingState();

private:
    MovingState m_movingState;
    const double m_posX;
    double m_posZ;
};

#endif //PLAYER_H
