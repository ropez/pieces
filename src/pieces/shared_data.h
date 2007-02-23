
#ifndef PIECES_SHARED_DATA_H
#define PIECES_SHARED_DATA_H

namespace Pieces
{

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

    // Disabled copy
    SharedData(const SharedData&);
    SharedData& operator=(const SharedData&);

    unsigned long m_count;
};

} // namespace Pieces

#endif // PIECES_SHARED_DATA_H
