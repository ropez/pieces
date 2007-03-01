
#ifndef PIECES_DATA_STREAM_H
#define PIECES_DATA_STREAM_H

#include "Pieces/ByteArray"

namespace Pieces
{


/**
 * \class DataStream
 * \brief Binary data stream.
 *
 * The DataStream class is used to stream binary data into a byte-array and to
 * read back from it. It contains input and output stream operators for all
 * basic data-types. It's also possible to read and write raw data represented
 * as byte-arrays.
 *
 * This can be used as basic building blocks to create overloaded stream
 * operators for custom classes.
 *
 * A write operation always adds to the end of the byte-array, and a read
 * operation starts from the beginning and continues where the previous read
 * operation stopped until the end is reached.
 *
 * A DataStream is typically used as either an input or an output stream, but
 * it's perfectly possible to do both on the same stream. Note however that if
 * you have a loop where you write to and read from the same data stream, it
 * will keep growing forever. The read operations doesn't remove any data from
 * the beginning of the byte-array.
 *
 * An example of how to write data to a data stream:
 * \code
 * DataStream ds;
 * ds << true << 1024 << 3.14159;
 * ByteArray output = ds.data();
 * \endcode
 *
 * An example of how to read the same data:
 * \code
 * DataStream ds(output);
 * bool b;
 * ds >> b;
 * int n;
 * ds >> n;
 * double d;
 * ds >> d;
 * // Also possible to do 'ds >> b >> n >> d' in one line.
 * \endcode
 *
 * \author Robin Pedersen
 */
class DataStream
{
public:

    /**
     * Create a stream starting with an empty byte-array.
     *
     * This is a typical output stream.
     *
     * All write operations will append data at the end of the internal
     * byte-array, which is availible by calling data().
     */
    DataStream();

    /**
     * Create a stream that starts with the contents of \a data.
     *
     * This is a typical input stream.
     *
     * Read operations will start at the beginning of the data, and will
     * continue where the previous read stopped.
     *
     * Write operations will append data to the internal byte-array which is
     * available by calling data(). The byte-array passed as parameter to this
     * constructor can't be changed.
     */
    explicit DataStream(const ByteArray& data);

    /**
     * Returns a copy of the internal byte-array.
     *
     * This array contains everything written using write operations, appended
     * to the byte-array passed to the constructor, if any.
     *
     * It doesn't matter if the data was read or not.
     */
    ByteArray data() const;

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
     * Write the contents of \a ba unformatted to the end of the data.
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
    ByteArray readBytes(int size);

private:

    // Current read location
    int m_readPtr;

    // Internal data
    ByteArray m_data;
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

} // namespace Pieces

#endif // PIECES_DATA_STREAM_H
