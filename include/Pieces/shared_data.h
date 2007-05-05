
#ifndef PIECES_SHARED_DATA_H
#define PIECES_SHARED_DATA_H

#include "Pieces/global"

namespace pcs
{

/**
 * \class SharedData shared_data.h <Pieces/SharedData>
 * \brief Reference counted data.
 *
 * This is a base class that provides thread-safe reference counting. Data
 * classes used with implicit sharing derives from this class.
 *
 * Both the SharadDataPointer and ReferencePointer templates assumes that the
 * type parameter is a subclass of SharedData.
 *
 * \see \ref implicit_sharing
 *
 * \author Robin Pedersen
 */
class SharedData
{
public:

    /**
     * Returns true if the reference counter is more than one.
     */
    bool shared() const;

    /**
     * Increase reference counter by one.
     *
     * Returns true if the reference counter is not zero.
     *
     * This operation is thread-safe.
     */
    bool ref();

    /**
     * Decrease reference counter by one.
     *
     * Returns true if the reference counter is not zero.
     *
     * This operation is thread-safe.
     */
    bool deref();

protected:

    /**
     * Default constructor sets reference count to 0.
     *
     * Protected so that it only can be instantiated through subclasses.
     */
    SharedData();

    /**
     * Protected destructor prevents stack allocation and manually delete.
     *
     * To disable these operations, it's recommended to have protected
     * destructors in all subclasses.
     */
    ~SharedData();

private:

    DISABLE_COPY(SharedData);

    unsigned long m_count;
};

} // namespace pcs

#endif // PIECES_SHARED_DATA_H
