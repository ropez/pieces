
#ifndef PIECES_SHARED_DATA_H
#define PIECES_SHARED_DATA_H

namespace Pieces
{

class SharedData
{
public:

    /**
     * Default constructor sets reference count to 0.
     */
    SharedData();

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
    // Disabled stack allocation and delete
    ~SharedData();

private:

    // Disabled copy
    SharedData(const SharedData&);
    SharedData& operator=(const SharedData&);

    unsigned int m_count;
};

} // namespace Pieces

#endif // PIECES_SHARED_DATA_H
