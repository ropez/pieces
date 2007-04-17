#if !defined PLAYER_H
#define PLAYER_H

#include "Pieces/GameObject"

class Player : public pcs::GameObject
{
public:
    Player(pcs::objectid_t objectId, int posX);

    void encode(pcs::DataStream& ds) const;

private:
    const double m_posX;
    double m_posZ;
};

#endif //PLAYER_H
