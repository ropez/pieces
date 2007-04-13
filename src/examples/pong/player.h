#if !defined PLAYER_H
#define PLAYER_H

#include "Pieces/GameObject"

class Player : public Pieces::GameObject
{
public:
    Player(Pieces::objectid_t objectId, int posX);

    void encode(Pieces::DataStream& ds) const;

private:
    const double m_posX;
    double m_posZ;
};

#endif //PLAYER_H
