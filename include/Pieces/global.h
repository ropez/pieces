
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
 * standart C library and the standard template library.
 *
 * \section getting_started Getting started
 * Pieces is an application framework designed to assist programmers creating games
 * with network multiplayer functionality. The following sections will give you an
 * introduction to Pieces. How to install, tutorial and explanation of some core
 * features in Pieces.
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
 * Once installed, you can compile and link programs that uses Pieces. These
 * instructions show how to do this with the GNU C++ compiler. If you are using a
 * different compiler, these steps should be quite similar.
 *
 * To compile your code, you must make sure the preprocessor finds the Pieces header
 * files. This would normally work automatically, but if your compiler is not set up
 * to look for include files where you installed Pieces, you have to tell it where
 * to find them with a '-I' option, like this:
 * \code
 * g++ -c -I/usr/local/include -o file.o file.cpp
 * \endcode
 *
 * Once your code files are compiled, you need to link your executable. In this step
 * you need to explicitly include the Pieces libraries. In addition to Pieces itself,
 * you need to link against OpenThreads and the posix threads library. Just like when
 * compiling, you need to specify where to look for the library files if they are not
 * in a location that the linker searches by default:
 * \code
 * g++ -L/usr/local/lib -o myapp myfile.o -lpieces -lOpenThreads -lpthread
 * \endcode
 *
 * That's it. If you have other problems, please consult your compiler documentation.
 *
 * \section introduction Introduction to Pieces
 * 
 * DISCLAIMER:
 * The authors of this section take no responsebility 
 * for the tutorial part of this document.
 * If it is very badly written, please send hate-mail to
 * joakimsi@stud.cs.uit.no 
 * He is, after all, Swedish.
 * 
 * You are now ready to begin using the Pieces framework. 
 * In this section we shall explain the basic features of the framework and how these are interconnected.
 * We shall begin by describing the two mandatory participants in a network game, namely the host and the peer. 
 * Next, we will examine a fictionary game world, and how everything inside it can be described as objects in Pieces.
 * Game world updates naturally follow game world creation, so this will be the 3rd topic we will look into. Since
 * this is where the actual game takes place, it will have several sub topics like how to handle game events and how to 
 * update object data on both the host and peer. In the 5th and last section will explore how the Pieces framework can be used
 * to handle user interaction. 
 * 
 * 
 * \subsection int_host Host
 * All centralized network applications need a host for the peers to connect to. In the pieces framework 
 *  - Event driven
 * The host is event driven.
 * \subsection int_peer Peer
 * - Event driven
 * The peer is event driven.
 * \subsection int_game_world Game world
 * \subsubsection int_game_obj Game objects
 * - Creating objects
 * \subsection int_game_world_updates Game world updates
 * \subsubsection int_event_loops Event loops
 * \subsubsection int_events Events
 * \subsubsection int_event_handlers Event handlers
 * \subsubsection int_update_frame Update frame data
 * \subsubsection int_apply_frame Apply frame data
 * \subsection int_user_int User interaction
 * \subsubsection int_messages Messages
 * 
 * \section examples Examples
 * This section describes some simple examples of how to utilize the Pieces framework in an application. It is assumed
 * that the programmer has compiled Pieces and have set up necessary project settings that will enable an application to link
 * the Pieces library files.
 *
 * The examples describe how two different applications communicate wich eachother, where one acts as host and the other as peer. An alternative approach is to integrate
 * the host and peer into one single application. This approach is not described here, but the idea is the same.
 *
 * \subsection tutorial_setup Setup
 * A pcs::Application must be created first in the main function for every Pieces application. Pieces functionality will not
 * work properly if this is not made.
 *
 * \code
 * // main_host.cpp and main_peer.cpp
 * int main(int argc, char** argv)
 * {
 *     pcs::Application application(argc, argv);
 *     ...
 * \endcode
 *
 * \subsection tutorial_connect Create a connection
 * The host application must have a class that is derived from pcs::Host. In this example it is called ExampleHost. It is in this class that all network events will be handled.
 *
 * \code
 * // example_host.h
 * class ExampleHost : public pcs::Host
 * {
 * public:
 *     ExampleHost();
 *     ...
 * };
 * \endcode
 *
 * Create an instance of the ExampleHost class in the main function after the creation of a pcs::Application. Then call ExampleHost's exec function. This will
 * start the event loop of the Host.
 *
 * \code
 * // main_host.cpp
 * int main(int argc, char** argv)
 * {
 *     pcs::Application application(argc, argv);
 *     pcs::AutoPointer<ExampleHost> host(new ExampleHost());
 *     host->exec();
 * }
 * \endcode
 *
 * In the host's constructor we start to listen on a port, in our case 2222. Incomming connections from peers are now possible on port 2222.
 *
 * \code
 * // example_host.cpp
 * ExampleHost::ExampleHost()
 * : pcs::Host()
 * {
 *     startListening(2222);
 *     ...
 * \endcode
 *
 * To create a Peer that connects to the host you have to create a subclass of pcs::Peer. The subclass is here called ExamplePeer.
 *
 * \code
 * // example_peer.h
 * class ExamplePeer : public pcs::Peer
 * {
 * public:
 *     ExamplePeer();
 *     ...
 * };
 * \endcode
 *
 * The creation of an ExamplePeer is done in the same manner as the creation of the ExampleHost.
 *
 * \code
 * // main_peer.cpp
 * int main(int argc, char** argv)
 * {
 *     pcs::Application application(argc, argv);
 *     pcs::AutoPointer<ExamplePeer> peer(new ExamplePeer());
 *     peer->exec();
 * }
 * \endcode
 *
 * Command line arguments are read in the constructor of the ExamplePeer . This is done with the global pcs::app object.
 * The first argument is the host address and the second one is the peer's listen port. The default values of arguments
 * are set to "localhost" and 3333, respectively.
 *
 * \code
 * // example_peer.cpp
 * ExamplePeer::ExamplePeer()
 * : pcs::Peer()
 * {
 *     std::string host = "localhost";
 *     pcs::port_t listenPort = 3333;
 *
 *     if(pcs::app->argc() > 1)
 *     {
 *         host = pcs::app->arg(1);
 *     }
 *
 *     if(pcs::app->argc() > 2)
 *     {
 *         std::stringstream ss(pcs::app->arg(2));
 *         ss >> listenPort;
 *     }
 *     ...
 * \endcode
 *
 * Now a pcs::SocketAddress is created based on the host address and the host port (in our case 2222). The connectTo function is then trying to create a connection
 * to this pcs::SocketAddress.
 *
 * \code
 *     ...
 *     // Connect to host
 *     pcs::SocketAddress sa(pcs::InetAddress::getHostByName(host), 2222);
 *     connectTo(sa);
 *     ...
 * \endcode
 *
 * The peer is now able to send and receive \link pcs::Message messages \endlink
 * to and from the host. But the peer is not yet able to receive \link
 * pcs::GameDataEvent game data events \endlink from the host. The way to make this possible
 * this is to send a message from the peer to the host, telling the host that
 * this peer wants to listen for \link pcs::GameDataEvent game data events
 * \endlink on a specified port.
 *
 * A pcs::Message is created with a user defined type that represents a join request. The type is simply an
 * integer. In our case it is set to MSG_GAME_EVENT_JOIN. We wish to send the peer's port
 * number in this message, so we add a paramemeter to the message, with the
 * built-in property pcs::PR_PORT and the value 3333.
 *
 * \code
 *     ...
 *     // Send join message (so the host will send us GameDataEvents on port 3333)
 *     pcs::Message message(MSG_GAME_EVENT_JOIN);
 *     message.set<pcs::port_t>(pcs::PR_PORT, listenPort);
 *     sendMessage(message);
 *
 *     // Start to listen for game data events.
 *     receiver()->listen(listenPort);
 * }
 * \endcode
 *
 * When this join request message is received by the host it is your responsibility to handle it. The virtual function pcs::Host::handle(pcs::MessageReceivedEvent* event) has to be implemented
 * in the ExampleHost to handle all types of messages. This function is called by Pieces each time a message is received.
 *
 * The next thing to do is to set up the host so it adds the peer to its list of receivers, and thus enable the peer to retrieve game data events. The host needs to know the address and port of the peer to do this.
 * The peer address is stored in the incoming message event and the port is stored in the message itself.
 *
 * The original message sent from the peer is obtained by calling event->getMessage().
 * First we must check if this really is a join request. This is done by checking the message type by calling the message.getMessageType() function. To get the peer's address, we use event->getSenderAddress().
 * The port of the peer is extracted from the message by message.get<pcs::port_t>(pcs::PR_PORT).
 *
 * Finally, the sender()->addReceiver(pcs::SocketAddress) function adds the peer to the host's receiver list.
 * A pcs::SocketAddress is used as parameter to the addReceiver function, it shall contain the peer's address and port.
 *
 * \code
 * // example_host.cpp
 * void ExampleHost::handle(pcs::MessageReceivedEvent* event)
 * {
 *     pcs::Message message = event->getMessage();
 *
 *     switch(message.getMessageType())
 *     {
 *     case MSG_GAME_EVENT_JOIN:
 *         {
 *             pcs::port_t port = message.get<pcs::port_t>(pcs::PR_PORT);
 *
 *             pcs::SocketAddress peer = event->getSenderAddress();
 *             peer.setPort(port);
 *             sender()->addReceiver(peer);
 * 	    ...
 * \endcode
 *
 * We have now achieved two things, namely the possibility to send messages between the host and peer and the possibility for the peer to receive game data events that are sent from the host. The next section will describe how game data events
 * are sent and received.
 *
 * \subsection tutorial_gde Game Data Events
 *
 * A pcs::GameObject enables us to send and receive game data events. You have to create a class that is derived from pcs::GameObject.
 * In this example we call it ExampleGameObject. The same ExampleGameObject class is used both by the host
 * and the peer. Its purpose is to contain game object specific data, and to specify what of these data should be sent over the network.
 * For example, a bicycle game object could contain position, orientation, velocity, and gear.
 * It could be assumed that the peer only needs to know about the position and the orientation of the bicycle.
 * In this case, only the position and the orientation data had to be sent over the network.
 *
 * The ExampleGameObject will contain two values, x and y, that will be sent to the peer.
 *
 * \code
 * // example_game_object.h
 * class ExampleGameObject : public pcs::GameObject
 * {
 * public:
 *     ExampleGameObject(pcs::objectid_t objectId);
 *
 *     void encode(pcs::DataStream& ds) const;
 *     void decode(pcs::DataStream& ds);
 * private:
 *     double m_x;
 *     double m_y;
 * };
 * \endcode
 *
 * The encode function is used by the host only. It adds the member variables m_x and m_y to a pcs::DataStream. The decode function is used by the peer only. It extracts the x and y value from the data
 * stream and stores them in the members m_x and m_y. For more infomation on this topic, see \ref data_encoding.
 *
 * \code
 * // example_game_object.cpp
 * ExampleGameObject::ExampleGameObject(pcs::objectid_t objectId)
 * : GameObject(objectId)
 * , m_x(0.0)
 * , m_y(0.0)
 * {
 * }
 *
 * void ExampleGameObject::encode(pcs::DataStream& ds) const
 * {
 *     ds << m_x << m_y;
 * }
 *
 * void ExampleGameObject::decode(pcs::DataStream& ds)
 * {
 *     ds >> m_x >> m_y;
 * }
 * \endcode
 * 
 * The next step is to create an ExampleGameObject on both the host and the peer. The host decides when a GameObject should be created. For example, a game object can be
 * created in the constructor of the host, when it receives a message from one of its peers, or when an internal condition is satisfied. The host is always telling the peer when it should create its game objects by sending a message.
 *
 * In this example we will create an ExampleGameObject each time a new peer is connected to the host. Do you remember when the host is notified when a new peer is connecting? That's right, when the host is receiving
 * a message of type MSG_GAME_EVENT_JOIN. It is here we create our ExampleGameObject. To handle multiple game objects we will use a pcs::GameObjectDB. We have to add this database as a member to the ExampleHost, we call it m_objDB.
 *
 * Every game object has to have a unique pcs::objectid_t value. Ideally, a function generating such id:s should be used, but in this example we simply use the id 999. Every game object also has to be categorized with a type. A type
 * is simply an integer. We set it to TYPE_EXAMPLE.
 *
 * To notify all peers about the new game object the sendCreateObject is called with the id and the type as parameters.
 *
 * \code
 * // example_host.cpp
 * void ExampleHost::handle(pcs::MessageReceivedEvent* event)
 * ...
 *     case MSG_GAME_EVENT_JOIN:
 *     ...
 *     pcs::objectid_t uniqueID = 999; // In a real application, a function generating id:s should be used.
 *     pcs::ReferencePointer<ExampleGameObject> ego = new ExampleGameObject(uniqueID);
 *     // The ExampleGameObject is added to the game object database.
 *     m_objDB->insert(uniqueID, ego.get());
 *     // Send Create message to peers.
 *     sendCreateObject(id, TYPE_EXAMPLE);
 *     ...
 * \endcode
 *
 * The sendCreateObject function generates and sends a message of the built-in type pcs::OBJECT_CREATE. The peer also has a virtual function that is called each time a message is received. In this function
 * we need to check the message type, if it is of pcs::OBJECT_CREATE type, then we have to check the object type. The object type is stored inside the message and is obtained asking for the pcs::PR_OBJECT_TYPE property. The id of the object
 * that was set by the host is also contained in the message. In this case we ask for the pcs::objectid_t property.
 *
 * If the object type was TYPE_EXAMPLE, we create a new ExampleGameObject with the id obtained from the message. As with ExampleHost, we also have to add a pcs::GameObjectDB (called m_objDB) as a member of the ExamplePeer
 * and insert our newly created game object into this one.
 *
 * \code
 * // example_peer.cpp
 * void ExamplePeer::handle(pcs::MessageReceivedEvent* event)
 * {
 *     pcs::Message message = event->getMessage();
 *
 *     switch(message.getMessageType())
 *     {
 *     case pcs::OBJECT_CREATE:
 *         {
 *             // Get object type
 *             int objectType = message.get<int>(pcs::PR_OBJECT_TYPE);
 *             // Get object id
 *             pcs::objectid_t objectId = message.get<pcs::objectid_t>(pcs::PR_OBJECT_ID);
 *
 *             switch (objectType)
 *             {
 *             case TYPE_EXAMPLE:
 *                 {
 *                     // Create new game object
 *                     pcs::ReferencePointer<ExampleGameObject> ego = new ExampleGameObject(objectId);
 *                     // Insert the game object into the database
 *                     m_objDB->insert(objectId, ego.get());
 *                 }
 *                 break;
 *             ...
 * \endcode
 * 
 * The host and peer now have one instance of the ExampleGameObject each. The data of the peer's ExampleGameObject will be updated every time the host updates the data of its ExampleGameObject. We are now ready to let the
 * host update the data of its ExampleGameObject.
 * 
 * \subsection example_timer_events Timer Events
 * 
 * The data of our ExampleGameObject will be updated 
 *
 * TODO: Describe how a timer event is handled by the host.
 * TODO: Describe how callbacks are utilized.
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
 * takes responsibility for the object is to return it as an auto-pointer. The
 * returned value can be stored as a local variable in a function, or as a member
 * variable in a class.
 *
 *
 * Example:
 * \code
 * AutoPointer<File> createFile()
 * {
 *     if (error)
 *         return 0;
 *     else
 *         return AutoPointer<File>(new File());
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
 * multiple pointers to the same object. A reference counter stored with the * object is increased for every pointer that is assigned to it, and descreased
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
 * in it's data types.
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
