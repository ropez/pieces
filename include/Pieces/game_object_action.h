
#ifndef PIECES_GAME_OBJECT_ACTION_H
#define PIECES_GAME_OBJECT_ACTION_H

#include "Pieces/SharedData"


namespace pcs
{


/**
 * \class GameObjectAction game_object_action.h <Pieces/GameObjectAction>
 * \brief Action function interface.
 *
 * This is an abstract interface that can be used to implement action functions
 * that can be applied systematically to game objects. This is a generic callback
 * functionality supported by Pieces that the user can utilize to implement
 * customizable and flexible functionality to his game objects.
 *
 * An example is if a user wants to use the same classes for game objects in
 * the host and the peers, but with some functionality specific for either the
 * host or the peers. He can use a common object class, but specific actions for
 * each process.
 *
 * An implementation will typically need to store a pointer to the game object
 * it is operating on. This is not implemented in this class, because it's more
 * convenient to have a specific pointer type than a generic GameObject
 * pointer.
 *
 * An action function object should not have a reference pointer to the object,
 * because the game object use a reference pointer to the action function, and
 * it would result in a circular reference.
 *
 * \see GameObject, GameObjectDB
 * \author Robin Pedersen
 */
class GameObjectAction : public SharedData
{
public:

    /**
     * Virtual destructor to make sure objects are correctly deleted.
     */
    virtual ~GameObjectAction() {};

    /**
     * Action operator.
     *
     * This operator is called when the action is applied to a game object.
     */
    virtual void operator()(framenum_t frameNum) = 0;
};

} // namespace pcs

#endif // PIECES_GAME_OBJECT_ACTION_H
