
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
 * \mainpage Pieces User Manual
 *
 * \section preface Preface
 * This is the user documentation for the Pieces framework. It should provide
 * the instructions needed to get started programming in Pieces. The reader is
 * expected to know basic C++ programming, and know how to compile, link and
 * run programs on the platform he is using.
 *
 * Cplusplus.com is a very good place to start learning about C++ programming,
 * as well as an excellent reference to the standard library, including the
 * standart C library and the standard tamplate library.
 *
 * \section getting_started Getting started
 * Pieces is an application framework designed to assist programmers creating games
 * with network multiplayer functionality.
 *
 * \section installation Installation
 * This section describes the steps needed to install Pieces, and how to set up
 * your project to use Pieces.
 *
 * \subsection install_linux Using linux
 * These are generic installation instructions under linux.
 *
 * After obtaining the latest version of the Pieces source code, extract the package
 * and `cd' to the directory containing the package's source code, like this:
 * \code
 * $ tar xvzf pieces-<version>.tar.gz
 * $ cd pieces-<version>
 * \endcode
 *
 * Then you need to configure the package for your system, by running
 * the 'configure' script, like this:
 * \code
 * $ ./configure [options]
 * \endcode
 * Running `configure' takes awhile.  While running, it prints some messages
 * telling which features it is checking for.
 *
 * Some systems require unusual options for compilation or linking that
 * the `configure' script does not know about.  You can give `configure'
 * initial values for variables by setting them in the environment.  Using
 * a Bourne-compatible shell, you can do that on the command line like
 * this:
 * \code
 * CC=c89 CFLAGS=-O2 LIBS=-lposix ./configure
 * \endcode
 *
 * Or on systems that have the `env' program, you can do it like this:
 * \code
 * env CPPFLAGS=-I/usr/local/include LDFLAGS=-s ./configure
 * \endcode
 *
 * Once configured, run 'make' to build the pieces binary:
 * \code
 * $ make
 * \endcode
 *
 * Watch the messages written by the compiler. If you see an error message,
 * your system might be missing a package required by Pieces, or it might
 * have been configured incorrectly. If the problem does not go away, please
 * contact the Pieces authors.
 *
 * If 'make' succeeded, run `make install' to install Pieces on your system,
 * you might need root privileges to do this:
 * \code
 * $ make install
 * \endcode
 *
 * You can remove the program binaries and object files from the source code
 * directory by typing `make clean'.  To also remove the files that `configure'
 * created (so you can compile the package for a different kind of computer),
 * type `make distclean'. If you want to uninstall Pieces from your system,
 * type 'make uninstall'.
 *
 * By default, `make install' will install Pieces files in '/usr/local/lib',
 * `/usr/local/include', etc. You can specify an installation prefix other than
 * `/usr/local' by giving `configure' the option `--prefix=PATH'.
 *
 * In addition, if you use an unusual directory layout you can give options like
 * `--libdir=PATH' to specify different values for particular kinds of files. Run
 * `configure --help' for a list of the directories you can set and what kinds of
 * files go in them.
 *
 *
 * \section tutorial Tutorial
 * This section describes some simple examples of how to utilize the Pieces framework in an application.
 *
 * \subsection tutorial_setup Setup
 * A pcs::Application must be created first in the main function for every Pieces application. Pieces functionality will not
 * work properly if this is not made.
 *
 * \code
 * int main(int argc, char** argv)
 * {
 *     pcs::Application application(argc, argv);
 *     ...
 * \endcode
 *
 * The programmer has to
 *
 *
 * ihow a simple game is made using Pieces. The game that will be made is the classic game Pong. It is assumed
 * that the programmer has compiled Pieces and have set up necessary project settings that will able an application to link
 * the Pieces library files.
 *
 * Two applications will be made, one that will serve as a host and the other as a peer. An alternative approach is to integrate
 * the host and peer into one single application. This approach is not described here, but the idea is the same.
 *
 * \subsection tutorial_host The host
 * A pcs::Application must be created first in the main function for every Pieces application. The pcs::Host and pcs::Peer will not
 * work properly if this is not made.
 *
 * \code
 * int main(int argc, char** argv)
 * {
 *     pcs::Application application(argc, argv);
 *
 *     pcs::AutoPointer<PongHost> host(new PongHost());
 *
 *     host->exec();
 * }
 * \endcode
 *
 * Every Pieces host application has to derive from the pcs::Host class. PongHost is a subclass of pcs::Host, it is here that all network
 * events are handled.
 *
 *
 * \subsubsection tutorial_host_pcshost pcs::Host
 *
 *
 *
 *
 *

 * \section smart_pointers Smart pointers
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
 *
 * \section implicit_sharing Implicit sharing
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
 * \subsection custom_shared_classes Using implicit sharing in custom classes
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
 *
 * \section data_encoding Data encoding
 *
 * Pieces uses a binary format for all network traffic. Internally, all user
 * data is represented as generic \link pcs::ByteArray byte-arrays \endlink.
 *
 * There are two ways to encode data; as a continous stream, or as a single
 * object at a time. Pieces has built in support for all basic integer and
 * real number types, as well as strings using std::string and Pieces classes
 * like pcs::PropertyList, pcs::Message and pcs::SocketAddress. All these types
 * can be encoded and decoded in both ways. It is also possible to add support
 * for custom types as described below.
 *
 * \subsection stream Stream encoding and decoding
 * Encoding into and decoding from a continous stream is handled by
 * pcs::DataStream. Writing to a data stream is done using the C++ output stream
 * operator '<<'. Reading is done using the input operator '>>'. Example:
 *
 * \code
 * pcs::DataStream ds;
 * // Writing
 * ds << -100 << 3.14 << "Hello world";
 * // Reading
 * int n; double d; std::string str;
 * ds >> n >> d >> str;
 * \endcode
 *
 * Custom game objects used to transfer data from a host to peers must
 * implement stream encoding and decoding in the functions
 * \link pcs::GameObject::encode encode \endlink and
 * \link pcs::GameObject::decode decode \endlink. In most cases, these functions
 * can be implemented by simply streaming all member variables to or from the
 * data stream object given as an argument, assuming that the type of all the
 * member variables are supported by Pieces.
 *
 * It is possible to extend the streaming encoding and decoding system for
 * use with custom data types (classes), by implementing data stream operators.
 * Here is a simple example, adding stream operators for a hypothetical Person
 * class:
 *
 * \code
 * class Person
 * {
 * public:
 *     std::string name;
 *     std::string address;
 * };
 *
 * // Output stream (encode) operator
 * pcs::DataStream& operator<<(pcs::DataStream& ds, const Person& person)
 * {
 *     ds << person.name << person.address;
 *     return ds;
 * }
 *
 * // Input stream (decode) operator
 * pcs::DataStream& operator>>(pcs::DataStream& ds, const Person& person)
 * {
 *     ds >> person.name >> person.address;
 *     return ds;
 * }
 *
 * // Using the operators:
 * DataStream ds;
 * Person p;
 * ds << p;
 * ds >> p;
 * \endcode
 *
 * \subsection single_object Single object encoding and decoding
 * Encoding and decoding single object from and to byte arrays is handled by
 * global functions called \em encode and \em decode. The pcs namespace
 * contains functions for the predefined types. Example:
 *
 * \code
 * // Encoding
 * double d = 3.14;
 * pcs::ByteArray ba;
 * pcs::encode(ba, d);
 *
 * // Decoding
 * double dd;
 * pcs::decode(ba, dd);
 * \endcode
 *
 * Normally, the user won't need to use the %encode and %decode functions directly,
 * but they are needed by the classes pcs::PropertyList and pcs::Message. In other
 * words, this is now message parameters are encoded. Here is an example of how to
 * encode and decode parameters in a message object:
 *
 * \code
 * Message msg;
 *
 * // Encode a double value
 * msg.set<double>(FIRST_PARAM, 3.14);
 * // Can also do this implicitly, because the compiler knows that 3.14 is a double:
 * msg.set(FIRST_PARAM, 3.14);
 *
 * // Decode a double value
 * double d = msg.get<double>(FIRST_PARAM);
 * // This can't be done implicitly
 * double dd = msg.get(FIRST_PARAM); // Compiler error
 * \endcode
 *
 * It is also possible to add \em encode and \em decode functions for custom types,
 * so that the message system can use them. There are many possible ways to write
 * encode and decode functions for the Person class above. One way is to use the
 * stream operators already defined:
 *
 * \code
 * void encode(pcs::ByteArray& ba, const Person& person)
 * {
 *     pcs::BufferStream bs;
 *     bs << person;
 *     ba = bs.data();
 * }
 *
 * void decode(const pcs::ByteArray& ba, Person& person)
 * {
 *     pcs::BufferStream bs(ba);
 *     bs >> person;
 * }
 * \endcode
 */

#endif // PIECES_GLOBAL_H
