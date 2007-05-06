
#ifndef PIECES_GLOBAL_H
#define PIECES_GLOBAL_H


// Macro to disable copy operations
#define DISABLE_COPY(c) c(const c&); c& operator=(const c&);


/**
 * \namespace pcs
 * \brief Pieces framework namespace.
 *
 * The pcs namespace contains all the classes of the Pieces framework.
 */
namespace pcs
{

/**
 * Bit field flags
 */
typedef unsigned long flags_t;


/**
 * Obeject identifier.
 *
 * Used when creating and removing objects (see GameObject), and to identily
 * game data (see FrameData).
 *
 * \note We could also use Universally unique identifiers (e.g. 550e8400-e29b-41d4-a716-446655440000). They take 16 bytes, I have the code we need. (Robin)
 */
typedef unsigned long objectid_t;

/**
 * Frame number.
 *
 * Used to identify game data (see GameDataSender and GameDataReceiver).
 *
 * \note Using 32-bit frame number is enough for about 118 weeks, with 60 frames per second. Enough?
 */
typedef unsigned long framenum_t;

/**
 * Port number.
 *
 * Network socket port number, see TCPSocket and UDPSocket.
 */
typedef unsigned short port_t;


/**
 * \enum MessageType
 * \brief Predefined message types.
 *
 * These message types are reserved for use by Pieces internally. User defined
 * message types should be values above 1000 for future compatibility.
 *
 * \author Robin Pedersen
 */
enum MessageType
{
    /// Default (uninitialized) message type.
    NO_MESSAGE_TYPE,

    /// Message that tells peers to create an object.
    OBJECT_CREATE,

    /// Message that tells peers to remove an object.
    OBJECT_REMOVE,

    // Not used
    GAMEDATA_CONNECT,
    GAMEDATA_DISCONNECT
};


/**
 * \enum MessageProperty
 * \brief Predefined message property types.
 *
 * These message property types are reserved for use by Pieces internally.
 * User defined properties should be values above 1000 for future compatibility.
 *
 * \author Robin Pedersen
 */
enum MessageProperty
{
    /// Default (uninitialized) property.
    NO_MESSAGE_PROPERTY,

    /// "Text" property.
    PR_TEXT,

    /// Object type property, used with OBJECT_CREATE.
    PR_OBJECT_TYPE,

    /// Object identifier property, used with OBJECT_CREATE and OBJECT_REMOVE.
    PR_OBJECT_ID,

    /// Socket port number, used when setting up data transfer.
    PR_PORT
};

} // namespace pcs


/**
 * \mainpage An introduction to Pieces
 *
 * \section preface Preface
 * This is the user documentation for the Pieces framework.
 *
 * \section getting_started Getting started
 *
 * \section installation Installation
 *
 * \section tutorial Tutorial
 *
 * \section other_pages Other pages in this manual
 * \subpage smart_pointers
 * \subpage implicit_sharing
 */

/**
 * \page smart_pointers Smart pointers
 *
 * In Pieces, a smart pointer is an abstract data type that simulates a pointer
 * while providing additional features, such as automatic garbage collection.
 * These additional features are intended to reduce bugs caused by the use of
 * pointers while retaining efficiency.
 *
 * Smart pointers typically keep track of the objects they point to for the
 * purpose of memory management.
 *
 * Pieces contains three smart pointer types:
 *
 * pcs::AutoPointer provides \em ownership semantics. Only a single auto-pointer
 * can point to a given object at a time. This pointer is said to \em own the
 * object it points to, and deletes it when the pointer is destructed. If an
 * existing auto-pointer is assigned to a new auto-pointer, ownership is
 * \em transferred to the new pointer, and the original pointer becomes a
 * null-pointer. An auto-pointer can be used with any type of object, except
 * arrays. Typical usage of auto-pointer is when you have a function that creates
 * an object, and returns a pointer to it. The only way to make sure the caller
 * takes responsibylity for the object is to return it as an auto-pointer. The
 * returned value can be stored as a local variable in a function, or as a member
 * variable in a class.
 *
 * Example:
 * \code
 * AutoPointer<File> createFile()
 * {
 *     if (error)
 *         return 0;
 *     else
 *         AutoPointer<File>(new File());
 * }
 *
 * void foo()
 * {
 *     AutoPointer<File> file = createFile();
 *     // ...
 *     if (file.isValid())
 *     {
 *         // ...
 *     }
 *
 *    // When the function returns, the object created by createObject is deleted
 *    // because the pointer file is destructed.
 * }
 * \endcode
 *
 * pcs::ReferencePointer provides \em reference \em counting pointer. This is
 * more advanced than auto-pointer, because it makes it possible to have
 * multiple pointers to the same object. A reference counter stored with the
 * object is increased for every pointer that is assigned to it, and descreased
 * when a pointer is not pointing to it anymore. The object is automatically
 * deleted when the reference count reaches zero. A reference pointer can be used
 * in all cases when an auto-pointer can be used, but the object type must be
 * derived from pcs::SharedData. pcs::GameObject is one such class.
 *
 * Example:
 * \code
 * void foo()
 * {
 *     AutoPointer<GameObjectDB> db;
 *     ReferencePointer<GameObject> obj;
 *
 *     // GameObjectDB stores all objects as reference pointers
 *     db = new GameObjectDB();
 *
 *     // Assigning the reference pointer sets counter to 1
 *     obj = new GameObject(id);
 *
 *     // Inserting in the object database increases counter to 2
 *     db->insert(id, obj.get());
 *
 *     // Replacing the pointer decreases the counter to 1
 *     obj = 0;
 *
 *     // When the function returns, AutoPointer deletes db, and the reference
 *     // counter of obj becomes 0, so it is also deleted.
 * }
 * \endcode
 *
 * pcs::SharedDataPointer provides a specialized pointer for use with implicitly
 * shared objects (See \ref implicit_sharing).
 */

/**
 * \page implicit_sharing Implicit sharing
 *
 * Pieces uses a technique called implicit sharing to maximize resource usage
 * and minimize copying of data, while providing simple value-based semantics
 * it's data types.
 *
 * The use of implicit sharing was inspired by the Qt toolkit from Trolltech.
 *
 * A shared class consists of a pointer to a shared data block that contains a
 * reference count and the data.
 *
 * When a shared object is created, it sets the reference count to 1. The reference
 * count is incremented whenever a new object references the shared data, and
 * decremented when the object dereferences the shared data. The shared data is
 * deleted when the reference count becomes zero.
 *
 * When dealing with shared objects, there are two ways of copying an object. We
 * usually speak about deep and shallow copies. A deep copy implies duplicating an
 * object. A shallow copy is a reference copy, i.e. just a pointer to a shared data
 * block. Making a deep copy can be expensive in terms of memory and CPU. Making a
 * shallow copy is very fast, because it only involves setting a pointer and
 * incrementing the reference count.
 *
 * Object assignment (with operator=()) for implicitly shared objects is implemented
 * using shallow copies.
 *
 * The benefit of sharing is that a program does not need to duplicate data
 * unnecessarily, which results in lower memory use and less copying of data. Objects
 * can easily be assigned, sent as function arguments, and returned from functions.
 *
 * Implicit sharing takes place behind the scenes; the programmer does not need to worry
 * about it. Even in multithreaded applications, implicit sharing takes place, as
 * explained in Threads and Implicit Sharing.
 *
 * \section custom_shared_classes Using implicit sharing in custom classes
 *
 * Pieces contains two classes that makes it very easy to implement implicit sharing
 * in user-defined classes: pcs::SharedData and pcs::SharedDataPointer.
 *
 * To make a class implicitly shared, all member variables must be declared inside
 * an internal data class that inherits from pcs::SharedData. The outer class must
 * then contain a single SharedDataPointer to an object of the internal data class.
 *
 * Example:
 * \code
 * class Person
 * {
 * public:
 *
 *     // All constructors must allocate a data object
 *     Person()
 *     : d(new PersonData())
 *     {}
 *
 *     // get and set functions to hide the internal implementation
 *
 *     std::string getName() const
 *     { return d->name; }
 *
 *     void setName(const std::string& name)
 *     { d->name = name; }
 *
 *     std::string getAddress() const
 *     { return d->address; }
 *
 *     void setAddress(const std::string& address)
 *     { d->address = address; }
 *
 * private:
 *     class PersonData : public pcs::SharedData
 *     {
 *     public:
 *         PersonData()
 *         : pcs::SharedData()
 *         {}
 *
 *         // Must have copy constructor to implement deep copy
 *         PersonData(const PersonData& other)
 *         : pcs::SharedData() // Always use default constructor
 *         , name(other.name)
 *         , address(other.address)
 *         {}
 *
 *         std::string name;
 *         std::string address;
 *     }
 *     pcs::SharedDataPointer<PersonData> d;
 * };
 * \endcode
 */

/**
 * \page data_encoding Data encoding
 *
 * Pieces uses a binary format for all network traffic. Internally, all user
 * data is represented as generic \link pcs::ByteArray byte-arrays \endlink.
 *
 * There are two ways to encode data; as a continous stream, or as a single
 * object at a time.
 *
 * \section stream Stream encoding
 * Encoding into and decoding from a continous stream is handled by
 * pcs::DataStream. Pieces has built-in operators for all basic integer and
 * real number types, and strings using std::string.
 *
 * Custom game objects used to transfer data from a host to peers must
 * implement stream encoding and decoding in the functions
 * \link pcs::GameObject::encode encode \endlink and
 * \link pcs::GameObject::decode decode \endlink.
 */

#endif // PIECES_GLOBAL_H
