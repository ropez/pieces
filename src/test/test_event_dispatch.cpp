#include "support.h"
#include <Pieces/EventQueue>
#include <Pieces/TimerEvent>
#include <Pieces/GameEvent>
#include <Pieces/NetworkEvent>
#include <Pieces/MessageReceivedEvent>
#include <Pieces/ConnectedEvent>
#include <Pieces/DisconnectedEvent>
#include <Pieces/InputEvent>
#include <Pieces/GameDataEvent>
#include <Pieces/EventHandler>

using pcs::AutoPointer;
using pcs::Event;
using pcs::EventQueue;
using pcs::EventHandler;
using pcs::TimerEvent;
using pcs::GameEvent;
using pcs::NetworkEvent;
using pcs::MessageReceivedEvent;
using pcs::ConnectedEvent;
using pcs::DisconnectedEvent;
using pcs::InputEvent;
using pcs::GameDataEvent;

namespace
{
enum {
    FOO = 100,
    BAR = 200,
};

AutoPointer<Event> timerEvent(new TimerEvent(FOO));
AutoPointer<Event> gameEvent(new GameEvent(FOO));
AutoPointer<Event> networkEvent(new NetworkEvent(pcs::SocketAddress()));
AutoPointer<Event> messageReceivedEvent(
    new MessageReceivedEvent(pcs::SocketAddress(),
                             pcs::msgpair_t(FOO, pcs::Message())));
AutoPointer<Event> connectedEvent(new ConnectedEvent(pcs::SocketAddress()));
AutoPointer<Event> disconnectedEvent(new DisconnectedEvent(pcs::SocketAddress()));
AutoPointer<Event> inputEvent(new InputEvent(FOO));
AutoPointer<Event> gameDataEvent(new GameDataEvent(0, pcs::FrameData()));

struct DefaultFlag {};
struct TimerFlag {};
struct GameFlag {};
struct NetworkFlag {};
struct MessageReceivedFlag {};
struct ConnectedFlag {};
struct DisconnectedFlag {};
struct InputFlag {};
struct GameDataFlag {};
}

class TestEventHandlerDispatchDefault : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestEventHandlerDispatchDefault);
    CPPUNIT_TEST(testTimerEvent);
    CPPUNIT_TEST(testGameEvent);
    CPPUNIT_TEST(testNetworkEvent);
    CPPUNIT_TEST(testMessageReceivedEvent);
    CPPUNIT_TEST(testConnectedEvent);
    CPPUNIT_TEST(testDisconnected);
    CPPUNIT_TEST(testInputEvent);
    CPPUNIT_TEST_SUITE_END();

    class MockEventHandler : public EventHandler
    {
    protected:
        virtual void handle(Event* event) {
            throw DefaultFlag();
        }
    };

    AutoPointer<EventHandler> h;

public:
    void setUp() {
        h = new MockEventHandler();
    }

    void tearDown() {
        h = 0;
    }

    void testTimerEvent() {
        CPPUNIT_ASSERT_THROW(timerEvent->dispatch(h.get()), DefaultFlag);
    }

    void testGameEvent() {
        CPPUNIT_ASSERT_THROW(gameEvent->dispatch(h.get()), DefaultFlag);
    }

    void testNetworkEvent() {
        CPPUNIT_ASSERT_THROW(networkEvent->dispatch(h.get()), DefaultFlag);
    }

    void testMessageReceivedEvent() {
        CPPUNIT_ASSERT_THROW(messageReceivedEvent->dispatch(h.get()), DefaultFlag);
    }

    void testConnectedEvent() {
        CPPUNIT_ASSERT_THROW(connectedEvent->dispatch(h.get()), DefaultFlag);
    }

    void testDisconnected() {
        CPPUNIT_ASSERT_THROW(disconnectedEvent->dispatch(h.get()), DefaultFlag);
    }

    void testInputEvent() {
        CPPUNIT_ASSERT_THROW(inputEvent->dispatch(h.get()), DefaultFlag);
    }

    void testGameDataEvent() {
        CPPUNIT_ASSERT_THROW(gameDataEvent->dispatch(h.get()), DefaultFlag);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestEventHandlerDispatchDefault);


class TestEventHandlerDispatchCommon : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestEventHandlerDispatchCommon);
    CPPUNIT_TEST(testTimerEvent);
    CPPUNIT_TEST(testGameEvent);
    CPPUNIT_TEST(testNetworkEvent);
    CPPUNIT_TEST(testMessageReceivedEvent);
    CPPUNIT_TEST(testConnectedEvent);
    CPPUNIT_TEST(testDisconnected);
    CPPUNIT_TEST(testInputEvent);
    CPPUNIT_TEST_SUITE_END();

    class MockEventHandler : public EventHandler
    {
    protected:
        virtual void handle(TimerEvent* event) {
            throw TimerFlag();
        }

        virtual void handle(GameEvent* event) {
            throw GameFlag();
        }

        virtual void handle(NetworkEvent* event) {
            throw NetworkFlag();
        }

        virtual void handle(InputEvent* event) {
            throw InputFlag();
        }

        virtual void handle(GameDataEvent* event) {
            throw GameDataFlag();
        }
    };

    AutoPointer<EventHandler> h;

public:
    void setUp() {
        h = new MockEventHandler();
    }

    void tearDown() {
        h = 0;
    }

    void testTimerEvent() {
        CPPUNIT_ASSERT_THROW(timerEvent->dispatch(h.get()), TimerFlag);
    }

    void testGameEvent() {
        CPPUNIT_ASSERT_THROW(gameEvent->dispatch(h.get()), GameFlag);
    }

    void testNetworkEvent() {
        CPPUNIT_ASSERT_THROW(networkEvent->dispatch(h.get()), NetworkFlag);
    }

    void testMessageReceivedEvent() {
        CPPUNIT_ASSERT_THROW(messageReceivedEvent->dispatch(h.get()), NetworkFlag);
    }

    void testConnectedEvent() {
        CPPUNIT_ASSERT_THROW(connectedEvent->dispatch(h.get()), NetworkFlag);
    }

    void testDisconnected() {
        CPPUNIT_ASSERT_THROW(disconnectedEvent->dispatch(h.get()), NetworkFlag);
    }

    void testInputEvent() {
        CPPUNIT_ASSERT_THROW(inputEvent->dispatch(h.get()), InputFlag);
    }

    void testGameDataEvent() {
        CPPUNIT_ASSERT_THROW(gameDataEvent->dispatch(h.get()), GameDataFlag);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestEventHandlerDispatchCommon);

class TestEventHandlerDispatchNetwork : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestEventHandlerDispatchNetwork);
    CPPUNIT_TEST(testMessageReceivedEvent);
    CPPUNIT_TEST(testConnectedEvent);
    CPPUNIT_TEST(testDisconnected);
    CPPUNIT_TEST_SUITE_END();

    class MockEventHandler : public EventHandler
    {
    protected:
        virtual void handle(MessageReceivedEvent* event) {
            throw MessageReceivedFlag();
        }

        virtual void handle(ConnectedEvent* event) {
            throw ConnectedFlag();
        }

        virtual void handle(DisconnectedEvent* event) {
            throw DisconnectedFlag();
        }
    };

    AutoPointer<EventHandler> h;

public:
    void setUp() {
        h = new MockEventHandler();
    }

    void tearDown() {
        h = 0;
    }

    void testMessageReceivedEvent() {
        CPPUNIT_ASSERT_THROW(messageReceivedEvent->dispatch(h.get()), MessageReceivedFlag);
    }

    void testConnectedEvent() {
        CPPUNIT_ASSERT_THROW(connectedEvent->dispatch(h.get()), ConnectedFlag);
    }

    void testDisconnected() {
        CPPUNIT_ASSERT_THROW(disconnectedEvent->dispatch(h.get()), DisconnectedFlag);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestEventHandlerDispatchNetwork);
