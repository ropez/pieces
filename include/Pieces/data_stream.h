
#ifndef PIECES_DATA_STREAM_H
#define PIECES_DATA_STREAM_H

#include "Pieces/ByteArray"

namespace pcs
{
class StreamTarget;


/**
 * \class DataStream
 * \brief Binary data stream.
 *
 * The DataStream class is used to stream binary data into a StreamTarget and to
 * read back from it. It contains input and output stream operators for all
 * basic data-types. It's also possible to read and write raw data represented
 * as byte-arrays.
 *
 * This can be used as basic building blocks to create overloaded stream
 * operators for custom classes.
 *
 * \note About string constants.
 * It's legal to stream a string constant to the data-stream
 * (e.g. ds << "Hello"), to read it from an input stream, use std::string.
 *
 * \see StreamTarget, DataBuffer, TCPSocket, ByteArray
 * \author Robin Pedersen
 */
class DataStream
{
public:

    /**
     * Create a data-stream with a null target.
     *
     * Using it will throw an exception. Must call setTarget() in order to use it.
     */
    DataStream();

    /**
     * Create a data-stream connected to a target.
     *
     * Using a read operation will call the target's read() function.
     *
     * If the target's write() function is buffered (TCPSocket). flush() will
     * flush the target. There is also a flush manipulator.
     */
    explicit DataStream(StreamTarget* target);

    /**
     * Destructor.
     *
     * Deletes the target is it's owned by the data-stream.
     */
    ~DataStream();

    /**
     * Returns a pointer to the stream target.
     */
    StreamTarget* target() const;

    /**
     * Replace the stream target with \a t.
     */
    void setTarget(StreamTarget* t);

    /**
     * Manipulator support.
     *
     * Calls foo(*this).
     */
    DataStream& operator<<(DataStream& (*foo)(DataStream&));

    /**
     * Manipulator support.
     *
     * Calls foo(*this).
     */
    DataStream& operator>>(DataStream& (*foo)(DataStream&));

    /** Append the value \a v to the data. */
    DataStream& operator<<(bool v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(char v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(unsigned char v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(short v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(unsigned short v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(int v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(unsigned int v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(long v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(unsigned long v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(float v);

    /** Append the value \a v to the data. */
    DataStream& operator<<(double v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(bool& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(char& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(unsigned char& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(short& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(unsigned short& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(int& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(unsigned int& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(long& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(unsigned long& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(float& v);

    /** Read data from the data stream, and store it into \a v. */
    DataStream& operator>>(double& v);

    /**
     * Append raw data.
     *
     * Write the contents of \a ba unformatted to the target.
     *
     * \warning This is not the same as adding \a ba using the operator <<.
     * It's not possible to read this byte-array using operator>>.
     */
    void writeBytes(const ByteArray& ba);

    /**
     * Read raw data.
     *
     * Read \a size bytes of data, and return as a byte-array.
     */
    ByteArray readBytes(size_t size);

    /**
     * Flush all data written to the stream.
     *
     * Calls target()->flush()
     */
    void flush();

private:
    DISABLE_COPY(DataStream);

    // Target
    StreamTarget* m_target;
};

/**
 * Write a byte-array to the stream.
 *
 * Append the contents of the byte-array \a ba to the output stream \a ds.
 *
 * This is formatted so that reading with operator>> will create a byte-array
 * of the same length as \a ba.
 *
 * \relates DataStream
 */
DataStream& operator<<(DataStream& ds, const ByteArray& ba);

/**
 * Read a byte-array from the stream.
 *
 * Read a byte-array written with operator<< from the input stream, and store
 * it in \a ba. The result will have the same length and contents as the stored
 * array.
 *
 * \relates DataStream
 */
DataStream& operator>>(DataStream& ds, ByteArray& ba);

/**
 * Write a string to the stream.
 *
 * Append the contents of the string \a str to the output stream \a ds.
 *
 * The string can be read back using the operator>>.
 *
 * \relates DataStream
 */
DataStream& operator<<(DataStream& ds, const std::string& str);

/**
 * Write a '\0'-terminated dtring to the stream.
 *
 * The terminator is not stored, but the length of the string is appended to
 * it. This is the same way as std::strings are stored.
 *
 * Only output operator is provided for the primitive string. To read it, use
 * the str::string input operator.
 *
 * This is only provided to make it possible to write string constants, like
 * this:
 * \code
 * ds << "Hello world";
 * // This is equivalent to
 * ds << std::string("Hello world");
 * \endcode
 */
DataStream& operator<<(DataStream& ds, const char* str);

/**
 * Read a string from the stream.
 *
 * Read a string written with operator<< from the input stream, and store it in
 * \a str.
 *
 * \relates DataStream
 */
DataStream& operator>>(DataStream& ds, std::string& str);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, bool v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, char v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, unsigned char v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, short v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, unsigned short v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, int v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, unsigned int v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, long v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, unsigned long v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, float v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, double v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, const ByteArray& v);

/**
 * Encode the value \a v into \a ba.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, const std::string& v);

/**
 * Encode the value \a v into \a ba.
 *
 * This encodes the primitive string in the same format as an std::string.
 * There is no decode function for this type, encode it to an std::string.
 *
 * \relates DataStream
 */
void encode(ByteArray& ba, const char* str);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, bool& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, char& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, unsigned char& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, short& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, unsigned short& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, int& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, unsigned int& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, long& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, unsigned long& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, float& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, double& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, ByteArray& v);

/**
 * Decode contents of \a ba into \a v.
 *
 * \relates DataStream
 */
void decode(const ByteArray& ba, std::string& v);

/**
 * Manipulator that flushes the stream.
 *
 * Calls ds.flush(), and returns ds.
 *
 * Usage:
 * \code
 * DataStream ds();
 * ds << data << flush;
 * \endcode
 *
 * \relates DataStream
 */
DataStream& flush(DataStream& ds);

} // namespace pcs

#endif // PIECES_DATA_STREAM_H
